#include "philo.h"

int	check_full(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->arg->philo_amount)
	{
		if (philo[i].eat_status != FULL)
			return (1);
		i++;
	}
	return (0);
}

void	observer(t_philo *philo)
{
	int		time;
	int		i;

	while (!philo->arg->die)
	{
		i = 0;
		while (i < philo->arg->philo_amount)
		{
			if (philo[i].eat_status != FULL)
			{
				time = get_time() - philo[i].eat_time;
				if (time >= philo[i].arg->time_to_die + 10)
				{
					print_status(DIE, philo);
					philo->arg->die = 1;
				}
				i++;
			}
			else
				if (!check_full(philo))
					return ;
		}
	}
}

void	*simulation(void *philosopher)
{
	t_philo		*philo;
	int			count;

	count = 0;
	philo = philosopher;
	if (!(philo->id % 2))
		ft_usleep(philo->arg->time_to_sleep - 10);
	while (!philo->arg->die)
	{
		eating(philo);
		if (philo->arg->meal_count)
		{
			count++;
			if (count == philo->arg->meal_count)
			{
				print_status(FULL, philo);
				philo->eat_status = FULL;
				return (NULL);
			}
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	start_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->arg->philo_amount)
	{
		if (pthread_create(&philo[i].thread, NULL, simulation, &philo[i]))
			return (ft_strerror("pthread_create error\n", 1));
		i++;
	}
	i = 0;
	while (i < philo->arg->philo_amount)
	{
		if (pthread_detach(philo[i].thread))
			return (ft_strerror("pthread_detach error\n", 1));
		i++;
	}
	return (0);
}

int	start_simulation(t_arg *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	status[2];

	mutexes = mutex_init(arg);
	pthread_mutex_init(&status[0], NULL);
	pthread_mutex_init(&status[1], NULL);
	if (!mutexes)
		return (1);
	philo = philo_init(arg, mutexes, status);
	if (!philo)
		return (1);
	if (start_threads(philo))
		return (1);
	observer(philo);
	return (0);
}

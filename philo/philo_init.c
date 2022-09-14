#include "philo.h"

pthread_mutex_t	*mutex_init(t_arg *arg)
{
	int				i;
	pthread_mutex_t	*mutexes;

	i = 0;
	mutexes = malloc(sizeof(pthread_mutex_t) * arg->philo_amount);
	if (!mutexes)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (NULL);
	}
	while (i < arg->philo_amount)
	{
		if (pthread_mutex_init(&mutexes[i], NULL))
		{
			ft_putstr_fd("mutex initialization error\n", 2);
			return (NULL);
		}
		i++;
	}
	return (mutexes);
}

t_philo	*philo_init(t_arg *arg, pthread_mutex_t *mutexes,
					pthread_mutex_t *status)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * arg->philo_amount);
	if (!philo)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (NULL);
	}
	arg->die = 0;
	while (i < arg->philo_amount)
	{
		philo[i].id = i + 1;
		philo[i].arg = arg;
		philo[i].l_fork = &mutexes[i];
		philo[i].r_fork = &mutexes[(i + 1) % arg->philo_amount];
		philo[i].status = &status[0];
		philo[i].die = &status[1];
		philo[i].start_time = get_time();
		philo[i].eat_time = get_time();
		philo[i].eat_status = 0;
		i++;
	}
	return (philo);
}

#include "philo.h"

void	*observer(void *philosopher)
{
	t_philo	*philo;
	int		time;

	philo = philosopher;
	while (!philo->arg->philo_status)
	{
		time = get_time() - philo->eat_time;
		if (!philo->eat_count && philo->arg->meal_count)
			return (NULL);
		if (time >= philo->arg->time_to_die + 10)
		{
			sem_wait(philo->semaphores->died);
			print_status(DIE, philo);
			philo->arg->philo_status = DIE;
			sem_post(philo->semaphores->died);
			exit(DIE);
		}
	}
	return (NULL);
}

void	*simulation(void *philosopher)
{
	t_philo		*philo;
	pthread_t	observe;
	pid_t		pid;
	int			status;

	philo = philosopher;
	pid = fork();
	if (pid == -1)
		return (NULL);
	philo->pid = &pid;
	if (pid == 0)
	{
		pthread_create(&observe, NULL, observer, philo);
		pthread_detach(observe);
		life_simulator(philo);
	}
	else
		waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == DIE || WEXITSTATUS(status) == FULL)
	{
		philo->arg->philo_status = WEXITSTATUS(status);
		philo->pid = NULL;
	}
	return (NULL);
}

void	philo_status_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo->arg->philo_status)
		{
			while (i < philo->arg->philo_amount)
			{
				if (philo[i].pid != NULL && philo->arg->philo_status == DIE)
					kill(*(philo[i].pid), 2);
				else if (philo[i].pid != NULL
					&& philo->arg->philo_status == FULL)
					waitpid(*(philo[i].pid), 0, 0);
				i++;
			}
			return ;
		}
	}
}

int	start_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->arg->philo_amount)
	{
		if (pthread_create(&philo[i].thread, NULL, simulation, &philo[i]))
		{
			ft_putstr_fd("pthread_create error\n", 2);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo->arg->philo_amount)
	{
		if (pthread_detach(philo[i].thread))
		{
			ft_putstr_fd("pthread_detach error\n", 2);
			return (1);
		}
		i++;
	}
	philo_status_check(philo);
	return (0);
}

int	start_simulation(t_arg *arg)
{
	t_philo			*philo;
	t_semaphores	*semaphores;

	semaphores = semaphores_init(arg);
	if (!semaphores)
		return (1);
	philo = philo_init(arg, semaphores);
	if (!philo)
		return (1);
	if (start_threads(philo))
		return (1);
	close_semaphores(philo);
	return (0);
}

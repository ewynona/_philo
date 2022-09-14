#include "philo.h"

t_semaphores	*semaphores_init(t_arg *arg)
{
	t_semaphores	*semaphores;

	sem_unlink("forks");
	sem_unlink("status");
	sem_unlink("died");
	sem_unlink("garcon");
	semaphores = malloc(sizeof(t_semaphores));
	if (!semaphores)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (NULL);
	}
	semaphores->forks = sem_open("forks", O_CREAT, 00644, arg->philo_amount);
	semaphores->status = sem_open("status", O_CREAT, 00644, 1);
	semaphores->died = sem_open("died", O_CREAT, 00644, 1);
	semaphores->garcon = sem_open("garcon", O_CREAT, 00644, 1);
	return (semaphores);
}

t_philo	*philo_init(t_arg *arg, t_semaphores *semaphores)
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
	arg->philo_status = 0;
	while (i < arg->philo_amount)
	{
		philo[i].id = i + 1;
		philo[i].eat_count = arg->meal_count;
		philo[i].arg = arg;
		philo[i].semaphores = semaphores;
		philo[i].start_time = get_time();
		philo[i].eat_time = get_time();
		i++;
	}
	return (philo);
}

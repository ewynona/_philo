#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	print_status(FORK, philo);
	print_status(EAT, philo);
	philo->eat_time = get_time();
	ft_usleep(philo->arg->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping(t_philo *philo)
{
	print_status(SLEEP, philo);
	ft_usleep(philo->arg->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(THINK, philo);
}

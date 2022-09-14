#include "philo.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->semaphores->garcon);
	sem_wait(philo->semaphores->forks);
	sem_wait(philo->semaphores->forks);
	sem_post(philo->semaphores->garcon);
	print_status(FORK, philo);
	print_status(EAT, philo);
	philo->eat_time = get_time();
	ft_usleep(philo->arg->time_to_eat);
	sem_post(philo->semaphores->forks);
	sem_post(philo->semaphores->forks);
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

void	life_simulator(t_philo *philo)
{
	while (1)
	{
		eating(philo);
		if (philo->arg->meal_count)
		{
			philo->eat_count--;
			if (!philo->eat_count)
			{
				print_status(FULL, philo);
				exit (FULL);
			}
		}
		sleeping(philo);
		thinking(philo);
	}
}

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	ft_put_status(int time, char *str, t_philo *philo)
{
	if (philo->arg->philo_status)
		exit (DIE);
	ft_putnbr_fd(time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(str, 1);
}

void	print_status(int status, t_philo *philo)
{
	int	time;

	time = get_time() - philo->start_time;
	sem_wait(philo->semaphores->status);
	if (status == FORK)
		ft_put_status(time, " has taken a fork\n", philo);
	else if (status == EAT)
		ft_put_status(time, " is eating\n", philo);
	else if (status == SLEEP)
		ft_put_status(time, " is sleeping\n", philo);
	else if (status == THINK)
		ft_put_status(time, " is thinking\n", philo);
	else if (status == DIE)
		ft_put_status(time, " is died\n", philo);
	else if (status == FULL)
		ft_put_status(time, " is full\n", philo);
	if (status != DIE)
		sem_post(philo->semaphores->status);
}

void	ft_usleep(int ms)
{
	long	time;

	time = get_time() + ms;
	while (get_time() <= time)
		usleep(10);
}

void	close_semaphores(t_philo *philo)
{
	sem_unlink("died");
	sem_unlink("forks");
	sem_unlink("garcon");
	sem_unlink("status");
	sem_close(philo->semaphores->died);
	sem_close(philo->semaphores->forks);
	sem_close(philo->semaphores->garcon);
	sem_close(philo->semaphores->status);
}

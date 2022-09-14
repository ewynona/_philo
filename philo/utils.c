#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2", fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else
	{
		if (n >= 10)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

void	ft_put_status(int time, char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->status);
	if (philo->arg->die)
	{
		pthread_mutex_unlock(philo->status);
		return ;
	}
	ft_putnbr_fd(time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(philo->status);
}

void	print_status(int status, t_philo *philo)
{
	int	time;

	time = get_time() - philo->start_time;
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
}

void	ft_usleep(int ms)
{
	long	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(100);
}

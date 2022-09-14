#include "philo.h"

int	ft_atoi(const char *str)
{
	char	*s;
	int		i;
	int		sign;
	int		total;

	sign = 1;
	total = 0;
	i = 0;
	s = (char *)str;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		total = total * 10 + (s[i] - '0');
		i++;
	}
	return (total * sign);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_strerror(char *str, int errno)
{
	ft_putstr_fd(str, 2);
	return (errno);
}

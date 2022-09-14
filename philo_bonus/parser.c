#include "philo.h"

static int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_arg	*parser(char **av)
{
	t_arg	*arg;

	if (check_arg(av) || ft_atoi(av[1]) < 1)
	{
		ft_putstr_fd("invalid argument\n", 2);
		return (NULL);
	}
	arg = malloc(sizeof(t_arg));
	if (!arg)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (NULL);
	}
	arg->philo_amount = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		arg->meal_count = ft_atoi(av[5]);
	else
		arg->meal_count = 0;
	return (arg);
}

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

int	parser(char **av, t_arg **arg)
{
	t_arg	*tmp;

	if (check_arg(av))
		return (ft_strerror("invalid argument\n", 0));
	tmp = malloc(sizeof(t_arg));
	if (!tmp)
		return (ft_strerror("malloc error1\n", 1));
	tmp->philo_amount = ft_atoi(av[1]);
	if (tmp->philo_amount < 1)
		return (ft_strerror("invalid argument\n", 1));
	tmp->time_to_die = ft_atoi(av[2]);
	tmp->time_to_eat = ft_atoi(av[3]);
	tmp->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		tmp->meal_count = ft_atoi(av[5]);
	else
		tmp->meal_count = 0;
	*arg = tmp;
	return (0);
}

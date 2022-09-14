#include "philo.h"

int	main(int ac, char **av)
{
	t_arg	*arg;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("wrong number of arguments\n", 2);
		return (1);
	}
	arg = parser(av);
	if (arg == NULL)
		return (1);
	start_simulation(arg);
	return (0);
}

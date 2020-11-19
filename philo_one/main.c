#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_vars vars;
	int i;

	if ((argc == 5) || (argc == 6))
	{
		if (init_args_n_do_cycles(&vars, argv))
		{
			// free_vars(&vars);
			return (-1);
		}
	}
	else
	{
		ft_put_error("Number of args (options) is not 5 or 6");
		return (-1);
	}
	// free_vars(&vars);
	return (0);
}
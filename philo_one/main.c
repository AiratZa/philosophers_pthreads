#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_vars vars;
	int i;

	if ((argc == 5) || (argc == 6))
	{
		if (init_args(&vars, argv))
		{
			free_vars(&vars);
			return (-1);
		}
		pthread_mutex_lock(&((vars.mtxs).philo_dead_mtx));
		pthread_mutex_unlock(&((vars.mtxs).philo_dead_mtx));
	}
	else
	{
		ft_put_error("Number of args (options) is not 5 or 6");
		return (-1);
	}
	// free_vars(&vars);
	return (0);
}
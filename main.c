#include "philo_one.h"

void	ft_put_error(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(CLR_RESET, 2);
}

int	main(int argc, char **argv)
{
	t_vars vars;
	int i;

	if ((argc == 5) || (argc == 6))
	{
		if (init_args(&vars, argv))
			return (-1);
		pthread_mutex_lock(&((vars.mtxs).philo_dead_mtx));
		pthread_mutex_unlock(&((vars.mtxs).philo_dead_mtx));
	}
	else
	{
		ft_put_error("Number of args (options) is not 5 or 6");
		return (-1);
	}
	return (0);
}
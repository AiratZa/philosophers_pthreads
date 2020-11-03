#include "philo_one.h"

void	ft_put_error(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(CLR_RESET, 2);
}

/*
TODO
https://cdn.intra.42.fr/pdf/pdf/13315/en.subject.pdf

*  The simulation stops when a philosopher dies

*  number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher

*/

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
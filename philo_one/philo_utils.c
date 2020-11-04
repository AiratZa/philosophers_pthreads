#include "philo_one.h"

long long int	ft_get_timestamp_ms(void)
{
	long long int	ret;
	struct timeval now;
	gettimeofday(&now, NULL);
	ret = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (ret);
}

/*
** usleep makes sleep for microsecs(milllisecs / 1000)
*/

void	sleep_milisecs(int count)
{
	usleep(1000 * count);
}

void	ft_put_error(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(CLR_RESET, 2);
}

void	init_vars(t_vars *vars)
{
	(vars->mtxs).forks_mtxs = NULL;
	vars->philos = NULL;
	vars->infos = NULL;

}

void	free_vars(t_vars *vars)
{
	int i;

	if ((vars->mtxs).forks_mtxs)
		free((vars->mtxs).forks_mtxs);
	if (vars->philos)
		free(vars->philos);
	if (vars->infos)
	{
		while (i < vars->nbr_of_philos && (vars->philos)[i].rght_fork)
		{
			free((vars->philos)[i].rght_fork);
			i++;
		}
		free(vars->infos);
	}
	return ;
}

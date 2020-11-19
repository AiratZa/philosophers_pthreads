#include "philo_one.h"

t_thrd_info *create_sctructs_for_thread_info(t_vars *vars)
{
	int				i;

	i = 0;
	if (!(vars->infos = (t_thrd_info *)malloc(sizeof(t_thrd_info) *\
											 vars->nbr_of_philos)))
		return (NULL);
	while (i < vars->nbr_of_philos)
	{
		((vars->infos)[i]).id = i + 1;
		((vars->infos)[i]).vars = vars;
		i++;
	}
	return (vars->infos);
}

void	set_init_args(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->nbr_of_philos)
	{
		(vars->philos)[i].id = i + 1;
		(vars->philos)[i].eatiing_count = 0;
		(vars->philos)[i].lst_meal = 0;
		pthread_mutex_init(&((vars->philos)[i].eat_mtx), NULL);
		pthread_mutex_lock(&((vars->philos)[i].eat_mtx));
		i++;
	}
}

t_philo	*create_philos_structs(t_vars *vars)
{
	int	i;

	i = 0;
	if (!(vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->nbr_of_philos)))
		return (NULL);
	set_init_args(vars);
	return (vars->philos);
}

int	create_philos(t_vars *vars)
{
	int	i;

	i = 0;
	if (!(vars->philos = create_philos_structs(vars)))
		return (-1);
	if (!(vars->infos = create_sctructs_for_thread_info(vars)))
		return (-1);
	return (0);
}

int init_mtxs(t_vars *vars)
{
	int i;
	
	i = 0;
	if (!((vars->mtxs).forks_mtxs = (pthread_mutex_t *)malloc(\
				sizeof(pthread_mutex_t) * vars->nbr_of_philos)))
		return (-1);
	while (i < (vars->nbr_of_philos))
	{
		pthread_mutex_init(&((vars->mtxs).forks_mtxs[i]), NULL);
		i++;
	}
	pthread_mutex_init(&((vars->mtxs).philo_dead_mtx), NULL);
	pthread_mutex_init(&((vars->mtxs).write_log_mtx), NULL);
	pthread_mutex_init(&((vars->mtxs).timestamp_mtx), NULL);
	// pthread_mutex_lock(&((vars->mtxs).timestamp_mtx));
	return (0);
}

int init_args_n_do_cycles(t_vars *vars, char **argv)
{
	vars->philos = NULL;
	if (parse_n_check_args(vars, argv))
		return (-1);
	if (init_mtxs(vars))
		return (-1);
	if (create_philos(vars))
		return (-1);
	vars->is_someone_dead = 0;
	int i;
	i = 0;
    vars->start_time = ft_get_timestamp_ms();

	while (i < vars->nbr_of_philos)
	{
		if (pthread_create(&(((vars->philos)[i]).thread), NULL, \
						life_cycle, (void *)(&((vars->infos)[i]))))
			return (-1);
		i++;
	}
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		pthread_join(((vars->philos)[i]).thread, NULL);
		i++;
	}
	return (0);
}

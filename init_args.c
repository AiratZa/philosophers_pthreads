#include "philo_one.h"

t_thrd_info *create_sctructs_for_thread_info(t_vars *vars)
{
	int				i;

	i = 0;
	if (!(vars->infos = (t_thrd_info *)malloc(sizeof(t_thrd_info) * vars->nbr_of_philos)))
		return (NULL);
	while (i < vars->nbr_of_philos)
	{
		((vars->infos)[i]).id = i + 1;
		((vars->infos)[i]).vars = vars;
		i++;
	}
	return (vars->infos);
}

t_philo	*create_philos_structs(t_vars *vars)
{
	int	i;

	i = 0;
	if (!(vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->nbr_of_philos)))
		return (NULL);
	while (i < vars->nbr_of_philos)
	{
		(vars->philos)[i].lft_fork = NULL; 
		(vars->philos)[i].rght_fork = malloc(sizeof(int));
		*((vars->philos)[i].rght_fork) = 1;
		i++;
	}
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		(vars->philos)[i].id = i + 1;
		(vars->philos)[i].first = ((i == 0) ? 1 : 0); 
		(vars->philos)[i].last = ((i == (vars->nbr_of_philos -1)) ? 1 : 0); 
		if (i == 0)
			(vars->philos)[i].lft_fork = (vars->philos)[vars->nbr_of_philos - 1].rght_fork;
		else
			(vars->philos)[i].lft_fork = (vars->philos)[i - 1].rght_fork; 
		(vars->philos)[i].status = 0;
		(vars->philos)[i].fork_count = 0;
		(vars->philos)[i].lft_id = ((i == 0) ? (vars->nbr_of_philos - 1) : (i - 1));
		(vars->philos)[i].rght_id = i;
		i++;
	}
	return (vars->philos);
}

int	create_philos(t_vars *vars)
{
	int	i;
	vars->philos = create_philos_structs(vars);
	vars->infos = create_sctructs_for_thread_info(vars);

	i = 0;
	while (i < vars->nbr_of_philos)
	{
		pthread_create(&(((vars->philos)[i]).thread), NULL, \
						life_cycle, (void *)(&((vars->infos)[i])));
		pthread_detach(((vars->philos)[i]).thread);
		sleep_milisecs(1);
		i++;
	}
	return (0);
}

int init_mtxs(t_vars *vars)
{
	int i;
	
	i = 0;
	(vars->mtxs).forks_mtxs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * vars->nbr_of_philos);
	while (i < (vars->nbr_of_philos))
	{
		pthread_mutex_init(&((vars->mtxs).forks_mtxs[i]), NULL);
		i++;
	}
	pthread_mutex_init(&((vars->mtxs).philo_dead_mtx), NULL);
	pthread_mutex_lock(&((vars->mtxs).philo_dead_mtx));
	pthread_mutex_init(&((vars->mtxs).write_log_mtx), NULL);
	return (0);
}

int init_args(t_vars *vars, char **argv)
{
	vars->philos = NULL;

	if (convert_to_int_n_check_min_value(argv, 1, vars))
		return (-1);
	if (convert_to_int_n_check_min_value(argv, 2, vars))
		return (-1);
	if (convert_to_int_n_check_min_value(argv, 3, vars))
		return (-1);
	if (convert_to_int_n_check_min_value(argv, 4, vars))
		return (-1);
	if (argv[5])
	{
		if (convert_to_int_n_check_min_value(argv, 5, vars))
			return (-1);
	}
	else
		vars->philos_must_eat_times_nbr = 0;
	init_mtxs(vars);
	create_philos(vars);
	return (0);
}

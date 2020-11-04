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

int	init_philos_forks(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->nbr_of_philos)
	{
		(vars->philos)[i].lft_fork = NULL; 
		(vars->philos)[i].rght_fork = NULL;
		i++;
	}
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		if (!((vars->philos)[i].rght_fork = malloc(sizeof(int))))
			return (-1);
		*((vars->philos)[i].rght_fork) = 1;
		i++;
	}
	return (0);
}

void	set_init_args(t_vars *vars)
{
	int i;

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
		(vars->philos)[i].eatiing_count = 0;
		(vars->philos)[i].fork_count = 0;
		(vars->philos)[i].lft_id = ((i == 0) ? (vars->nbr_of_philos - 1) : (i - 1));
		(vars->philos)[i].rght_id = i;
		(vars->philos)[i].lst_meal = 0;
		(vars->philos)[i].eatiing_count = 0;
		pthread_mutex_init(&((vars->philos)[i].philo_mtx), NULL);
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
	if (init_philos_forks(vars))
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
	if (pthread_mutex_lock(&((vars->mtxs).philo_dead_mtx)))
		return (-1);
	pthread_mutex_init(&((vars->mtxs).write_log_mtx), NULL);
	return (0);
}

int init_args(t_vars *vars, char **argv)
{
	vars->philos = NULL;
	// vars->block_logs = 0;
	if (parse_n_check_args(vars, argv))
		return (-1);
	if (init_mtxs(vars))
		return (-1);
	if (create_philos(vars))
		return (-1);
	if (init_monitoring(vars))
		return (-1);
	
	int i;
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		if (pthread_create(&(((vars->philos)[i]).thread), NULL, \
						life_cycle, (void *)(&((vars->infos)[i]))))
			return (-1);
		if (pthread_detach(((vars->philos)[i]).thread))
			return (-1);
		usleep(500);
		i++;
	}
	return (0);
}

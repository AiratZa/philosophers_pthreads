#include "philo_one.h"

void	drop_forks(t_vars *vars, int id);

void    ft_eat(t_vars *vars, int id)
{
    pthread_mutex_lock(&((vars->mtxs).timestamp_mtx));
	(vars->philos)[id - 1].lst_meal = ft_get_timestamp_ms();
    pthread_mutex_unlock(&((vars->mtxs).timestamp_mtx));
    ((vars->philos)[id - 1]).max_hunger = (vars->philos)[id - 1].lst_meal + vars->time_to_die;
    write_log(vars, 2, id);
    (vars->philos)[id - 1].eating_status = 1;
    if (vars->is_someone_dead)
    {
        drop_forks(vars, id);
        return ;
    }
	sleep_exact_ms(vars->time_to_eat);
    (vars->philos)[id - 1].eating_status = 0;
    (vars->philos)[id - 1].eatiing_count++;
}

void	drop_forks(t_vars *vars, int id)
{
    int right_fork_index;

	right_fork_index = id % vars->nbr_of_philos;
    if (id % 2)
    {
        pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[id - 1]));
        pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[right_fork_index]));
    }
    else
    {
        pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[right_fork_index]));
        pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[id - 1]));
    }
}

void    ft_sleep(t_vars *vars, int id)
{
    t_philo philo;

    philo = (vars->philos)[id - 1];
    drop_forks(vars, id);
    write_log(vars, 3, id);
    if (vars->is_someone_dead)
        return ;
    sleep_exact_ms(vars->time_to_sleep);
}

void    ft_think(t_vars *vars, int id)
{
    write_log(vars, 4, id);
	return ;
}

void	take_forks(t_vars *vars, int id)
{
    int right_fork_index;

	right_fork_index = id % vars->nbr_of_philos;
    if (id % 2)
    {
        if (vars->is_someone_dead)
            return ;
        pthread_mutex_lock(&((vars->mtxs).forks_mtxs[id - 1]));
        if (vars->is_someone_dead)
        {
            pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[id - 1]));
            return ;
        }
        write_log(vars, 1, id);
        pthread_mutex_lock(&((vars->mtxs).forks_mtxs[right_fork_index]));
        if (vars->is_someone_dead)
        {
            drop_forks(vars, id);
            return ;
        }
        write_log(vars, 1, id);
    }
    else
    {
        if (vars->is_someone_dead)
            return ;
        pthread_mutex_lock(&((vars->mtxs).forks_mtxs[right_fork_index]));
        if (vars->is_someone_dead)
        {
            pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[right_fork_index]));
            return ;
        }
        write_log(vars, 1, id);
        pthread_mutex_lock(&((vars->mtxs).forks_mtxs[id - 1]));
        if (vars->is_someone_dead)
        {
            drop_forks(vars, id);
            return ;
        }
        write_log(vars, 1, id);
    }
}

void	*hungry_monitoring(void *info_void)
{
	t_thrd_info *info;
    t_vars *vars;    
	int	id;

	info = (t_thrd_info *)info_void;
	id = info->id;
    vars = info->vars;
	while (1)
	{
        if (vars->is_someone_dead)
            return (NULL);
	    pthread_mutex_lock(&((vars->mtxs).timestamp_mtx));
		if (ft_get_timestamp_ms() > ((vars->philos)[id - 1]).max_hunger)
		{
	        pthread_mutex_unlock(&((vars->mtxs).timestamp_mtx));
            pthread_mutex_lock(&((vars->mtxs).philo_dead_mtx));
            if (vars->is_someone_dead)
            {
		        pthread_mutex_unlock(&((vars->mtxs).philo_dead_mtx));
                return (NULL);
            }
			write_log(vars, -1, id);
            vars->is_someone_dead++;
            pthread_mutex_unlock(&((vars->mtxs).philo_dead_mtx));
			return (NULL);
		}
        pthread_mutex_unlock(&((vars->mtxs).timestamp_mtx));
		usleep(10);
	}
	return (NULL);
}

int	activate_health_monitoring(t_vars *vars, int id, void *info_void)
{
	pthread_create(&((vars->philos)[id - 1].hungry_monitor), NULL, \
				hungry_monitoring, info_void);
	pthread_detach((vars->philos)[id - 1].hungry_monitor);
	return (0);
}


void    *life_cycle(void *info_void)
{
	t_thrd_info *info;
    t_vars *vars;    
	int	id;

	info = (t_thrd_info *)info_void;
	id = info->id;
    vars = info->vars;
    ((vars->philos)[id - 1]).lst_meal = ft_get_timestamp_ms();
    ((vars->philos)[id - 1]).max_hunger = (vars->philos)[id - 1].lst_meal + vars->time_to_die;
    activate_health_monitoring(vars, id, info_void);
    if (vars->philos_must_eat_times_nbr)
		activate_eating_count_monitoring(vars);
    while (1)
	{
        if (vars->is_someone_dead)
            break ;
	    take_forks(vars, id);
        if (vars->is_someone_dead)
        {
            drop_forks(vars, id);
            break ;
        }
        ft_eat(vars, id);
        if (vars->is_someone_dead)
        {
            drop_forks(vars, id);
            break ;
        }
        ft_sleep(vars, id);
        if (vars->is_someone_dead)
            break ;
        ft_think(vars, id);
	}
    // printf("\n\nID %d\n\n", id);
	return (NULL);
}

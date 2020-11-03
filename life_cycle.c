#include "philo_one.h"

void    eating(t_vars *vars, int id)
{
	(vars->philos)[id - 1].lst_meal = ft_get_timestamp_ms();
    write_log(vars, 2, id);
	sleep_milisecs(vars->time_to_eat);
	return ;
}

void    sleeping(t_vars *vars, int id)
{
    t_philo philo;

    philo = (vars->philos)[id - 1];
    philo.fork_count = 0;
    pthread_mutex_lock(&((vars->mtxs).forks_mtxs[philo.lft_id]));
    pthread_mutex_lock(&((vars->mtxs).forks_mtxs[philo.rght_id]));
    *(philo.lft_fork) = 1;
    *(philo.rght_fork) = 1;
    write_log(vars, 3, id);
    pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[philo.lft_id]));
    pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[philo.rght_id]));
	sleep_milisecs(vars->time_to_sleep);
}

void    thinking(t_vars *vars, int id)
{
    write_log(vars, 4, id);
	return ;
}


void	taking_forks(t_vars *vars, int id)
{
    t_philo philo;

    philo = (vars->philos)[id - 1];
    while (1)
    {
        if (*(philo.lft_fork))
        {
            pthread_mutex_lock(&((vars->mtxs).forks_mtxs[philo.lft_id]));
            (*(philo.lft_fork)) = 0;	
            pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[philo.lft_id]));
            philo.fork_count++;
            write_log(vars, 1, id);
        }
        else if (*(philo.rght_fork))
        {
            pthread_mutex_lock(&((vars->mtxs).forks_mtxs[philo.rght_id]));
            (*(philo.rght_fork)) = 0;	
            pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[philo.rght_id]));
            philo.fork_count++;
            write_log(vars, 1, id);
        }
        if (philo.fork_count == 2)
            return ;
    }
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
	while (1)
	{
	    taking_forks(vars, id);
        eating(vars, id);
        sleeping(vars, id);
        thinking(vars, id);
	}
	return (NULL);
}

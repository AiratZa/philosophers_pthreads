#include "philo_one.h"

void    eating(t_vars *vars, int id)
{
    pthread_mutex_lock(&((vars->philos)[id - 1].philo_mtx));
	(vars->philos)[id - 1].lst_meal = ft_get_timestamp_ms();
    ((vars->philos)[id - 1]).max_hunger = (vars->philos)[id - 1].lst_meal + vars->time_to_die;
    write_log(vars, 2, id);
    (vars->philos)[id - 1].eating_status = 1;
	sleep_milisecs(vars->time_to_eat);
    (vars->philos)[id - 1].eating_status = 0;
    (vars->philos)[id - 1].eatiing_count++;
    pthread_mutex_unlock(&((vars->philos)[id - 1].philo_mtx));
    pthread_mutex_unlock(&((vars->philos)[id - 1].eat_mtx));
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

void    set_taken_fork(t_vars *vars, int id, t_philo *philo)
{
    if (*(philo->lft_fork))
    {
        pthread_mutex_lock(&((vars->mtxs).forks_mtxs[philo->lft_id]));
        (*(philo->lft_fork)) = 0;	
        pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[philo->lft_id]));
        philo->fork_count++;
        write_log(vars, 1, id);
    }
    else if (*(philo->rght_fork))
    {
        pthread_mutex_lock(&((vars->mtxs).forks_mtxs[philo->rght_id]));
        (*(philo->rght_fork)) = 0;	
        pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[philo->rght_id]));
        philo->fork_count++;
        write_log(vars, 1, id);
    }
}

void	taking_forks(t_vars *vars, int id)
{
    t_philo philo;

    philo = (vars->philos)[id - 1];
    while (1)
    {
        set_taken_fork(vars, id, &philo);
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
    ((vars->philos)[id - 1]).max_hunger = (vars->philos)[id - 1].lst_meal + vars->time_to_die;
    activate_monitoring(vars, id, info_void);
	while (1)
	{
	    taking_forks(vars, id);
        eating(vars, id);
        sleeping(vars, id);
        thinking(vars, id);
	}
	return (NULL);
}

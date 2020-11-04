#include "philo_one.h"

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
        pthread_mutex_lock(&((vars->philos)[id - 1].philo_mtx));
		if ((vars->philos)[id - 1].lst_meal && !((vars->philos)[id - 1].eating_status))//
		{
			if (ft_get_timestamp_ms() > ((vars->philos)[id - 1]).max_hunger)
			{
				write_log(vars, -1, id);
				// vars->block_logs = 1;
				pthread_mutex_unlock(&((vars->philos)[id - 1].philo_mtx));
				pthread_mutex_unlock(&((vars->mtxs).philo_dead_mtx));
				return (NULL);
			}
		}
        pthread_mutex_unlock(&((vars->philos)[id - 1].philo_mtx));
        sleep_milisecs(1);
	}
	return (NULL);
}

int	activate_monitoring(t_vars *vars, int id, void *info_void)
{
	pthread_create(&((vars->philos)[id - 1].hungry_monitor), NULL, \
				hungry_monitoring, info_void);
	pthread_detach((vars->philos)[id - 1].hungry_monitor);
	return (0);
}

void	*eating_count_monitoring(void *vars_void)
{
	t_vars *vars;
    int     count;
    int     i;

    count = 0;
	vars = (t_vars *)vars_void;
	while (count < vars->philos_must_eat_times_nbr)
	{
        i = 0;
        while (i < vars->nbr_of_philos)
        {
		    pthread_mutex_lock(&((vars->philos)[i].eat_mtx));
            i++;
        }
        count++;
	}
	// vars->block_logs = 1;
	pthread_mutex_lock(&((vars->mtxs).write_log_mtx));
	pthread_mutex_unlock(&((vars->mtxs).philo_dead_mtx));
	return (NULL);
}

int	activate_eating_count_monitoring(t_vars *vars)
{
	pthread_create(&(vars->eating_count_monitoring), NULL, \
			eating_count_monitoring, (void *)(vars));
	pthread_detach(vars->eating_count_monitoring);
	return (0);
}

int init_monitoring(t_vars *vars)
{
    if (vars->philos_must_eat_times_nbr)
		activate_eating_count_monitoring(vars);
    return (0);
}

#include "philo_one.h"


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


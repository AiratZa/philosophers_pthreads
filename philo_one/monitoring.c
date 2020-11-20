/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:34 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/20 05:40:19 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** if all philosophers eat AT LEAST ’number_of_times_each_philosopher_must_eat’
** the simulation will stop
** The philosophers must NEVER be starving.
*/
void	*hungry_monitoring(void *philo_struct)
{
	t_philo *philo;
    t_vars *vars;    
	int	id;

	philo = (t_philo *)philo_struct;
	id = philo->id;
    vars = philo->vars;
	while (1)
	{
        if (vars->is_someone_dead)
            return (NULL);
	    pthread_mutex_lock(&((vars->mtxs).protect_when_eat_mtx));
		if (ft_get_timestamp_ms() > ((vars->philos)[id - 1]).max_hunger)
		{
	        pthread_mutex_unlock(&((vars->mtxs).protect_when_eat_mtx));
            pthread_mutex_lock(&((vars->mtxs).philo_dead_mtx));
            if (vars->is_someone_dead)
            {
		        pthread_mutex_unlock(&((vars->mtxs).philo_dead_mtx));
                return (NULL);
            }
			write_log(vars, DIE_LOG, id);
            vars->is_someone_dead++;
            pthread_mutex_unlock(&((vars->mtxs).philo_dead_mtx));
			return (NULL);
		}
        pthread_mutex_unlock(&((vars->mtxs).protect_when_eat_mtx));
		usleep(10);
	}
	return (NULL);
}

int	activate_health_monitoring(t_vars *vars, int id, void *philo_struct)
{
	pthread_create(&((vars->philos)[id - 1].hungry_monitor), NULL, \
				hungry_monitoring, philo_struct);
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
	if (vars->is_someone_dead)
		return (NULL);
	pthread_mutex_lock(&((vars->mtxs).philo_dead_mtx));
	if (vars->is_someone_dead)
	{
		pthread_mutex_unlock(&((vars->mtxs).philo_dead_mtx));
		return (NULL);
	}
	vars->is_someone_dead++;
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


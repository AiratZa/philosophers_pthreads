/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:34 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 17:09:35 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** if all philosophers eat AT LEAST ’number_of_times_each_philosopher_must_eat’
** the simulation will stop
** The philosophers must NEVER be starving.
*/

void	*hungry_monitoring_reacted(t_vars *vars, int id)
{
	sem_post((vars->sems).protect_when_eat_sem);
	write_log(vars, DIE_LOG, id);
	return (NULL);
}

void	*hungry_monitoring(void *philo_struct)
{
	t_philo	*philo;
	t_vars	*vars;
	int		id;

	philo = (t_philo *)philo_struct;
	id = philo->id;
	vars = philo->vars;
	while (1)
	{
		sem_wait((vars->sems).protect_when_eat_sem);
		if (ft_get_timestamp_ms() > ((vars->philos)[id - 1]).max_hunger)
			return (hungry_monitoring_reacted(vars, id));
		sem_post((vars->sems).protect_when_eat_sem);
		usleep(10);
	}
	return (NULL);
}

int		activate_health_monitoring(t_vars *vars, int id, void *philo_struct)
{
	if (pthread_create(&((vars->philos)[id - 1].hungry_monitor), NULL, \
				hungry_monitoring, philo_struct))
		return (-1);
	if (pthread_detach((vars->philos)[id - 1].hungry_monitor))
		return (-1);
	return (0);
}

void	*eating_count_monitoring(void *vars_void)
{
	t_vars	*vars;
	int		i;

	i = 0;
	vars = (t_vars *)vars_void;
	while (i < vars->nbr_of_philos)
		sem_wait((vars->philos)[i++].ate_enough);
	sem_wait((vars->sems).write_log_sem);
	sem_post((vars->sems).philo_dead_sem);
	return (NULL);
}

int		activate_eating_count_monitoring(t_vars *vars)
{
	if (pthread_create(&(vars->eating_count_monitoring), NULL, \
			eating_count_monitoring, (void *)(vars)))
		return (-1);
	if (pthread_detach(vars->eating_count_monitoring))
		return (-1);
	return (0);
}

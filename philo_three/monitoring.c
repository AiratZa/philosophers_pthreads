/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:34 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/21 21:47:45 by gdrake           ###   ########.fr       */
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
	sem_wait((vars->sems).philo_dead_sem);
	if (vars->is_someone_dead)
	{
		sem_post((vars->sems).philo_dead_sem);
		return (NULL);
	}
	write_log(vars, DIE_LOG, id);
	vars->is_someone_dead++;
	sem_post((vars->sems).philo_dead_sem);
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
		if (vars->is_someone_dead)
			return (NULL);
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
	pthread_create(&((vars->philos)[id - 1].hungry_monitor), NULL, \
				hungry_monitoring, philo_struct);
	pthread_detach((vars->philos)[id - 1].hungry_monitor);
	return (0);
}

void	*life_cycle(void *philo_struct)
{
	t_philo	*philo;
	t_vars	*vars;
	int		id;

	philo = (t_philo *)philo_struct;
	id = philo->id;
	vars = philo->vars;
	int count;
	count = 0;
	while (count < vars->philos_must_eat_times_nbr)
		sem_wait((vars->philos)[i++].eat_sem);
	return (NULL);
}

void	*eating_count_monitoring(void *vars_void)
{
	t_vars	*vars;
	int		count;
	int		i;

	count = 0;
	vars = (t_vars *)vars_void;
	while (1)
	{
		while (i < vars->nbr_of_philos)
		{
			if ([i]eat_count == vars->philos_must_eat_times_nbr)
			{
				if (i == (vars->nbr_of_philos - 1))
					break ;
				i++;
			}
		}
		if (pthread_create(&(((vars->philos)[i]).check_thread), NULL, \
				check_cycle, (void *)(&((vars->philos)[i]))))
		return (-1);
		i++;
	}
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		if (pthread_join(((vars->philos)[i]).check_thread, NULL))
			return (-1);
		i++;
	}
	if (vars->is_someone_dead)
		return (NULL);
	sem_wait((vars->sems).philo_dead_sem);
	if (vars->is_someone_dead)
	{
		sem_post((vars->sems).philo_dead_sem);
		return (NULL);
	}
	vars->is_someone_dead++;
	sem_post((vars->sems).philo_dead_sem);
	return (NULL);
}

int		activate_eating_count_monitoring(t_vars *vars)
{
	pthread_create(&(vars->eating_count_monitoring), NULL, \
			eating_count_monitoring, (void *)(vars));
	pthread_detach(vars->eating_count_monitoring);
	return (0);
}

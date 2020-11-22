/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:41 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/21 19:40:17 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_eat(t_vars *vars, int id)
{
	pthread_mutex_lock(&((vars->mtxs).protect_when_eat_mtx));
	(vars->philos)[id - 1].lst_meal = ft_get_timestamp_ms();
	((vars->philos)[id - 1]).max_hunger = (vars->philos)[id - 1].lst_meal + \
											vars->time_to_die;
	pthread_mutex_unlock(&((vars->mtxs).protect_when_eat_mtx));
	write_log(vars, EAT_LOG, id);
	sleep_exact_ms(vars, vars->time_to_eat);
	pthread_mutex_unlock(&((vars->philos)[id - 1].eat_mtx));
}

void	ft_sleep(t_vars *vars, int id)
{
	drop_forks(vars, id);
	write_log(vars, SLEEP_LOG, id);
	if (vars->is_someone_dead)
		return ;
	sleep_exact_ms(vars, vars->time_to_sleep);
}

void	life_cycle_inside(t_vars *vars, int id)
{
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
		write_log(vars, THINK_LOG, id);
	}
}

void	*life_cycle(void *philo_struct)
{
	t_philo	*philo;
	t_vars	*vars;
	int		id;

	philo = (t_philo *)philo_struct;
	id = philo->id;
	vars = philo->vars;
	philo->lst_meal = ft_get_timestamp_ms();
	philo->max_hunger = philo->lst_meal + vars->time_to_die;
	activate_health_monitoring(vars, id, philo_struct);
	life_cycle_inside(vars, id);
	return (NULL);
}

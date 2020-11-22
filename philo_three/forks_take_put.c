/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_take_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:38:00 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/21 21:40:13 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	take_forks_inside(t_vars *vars, int id)
{
	sem_wait((vars->sems).waiter);
	if (vars->is_someone_dead)
		return ;
	sem_wait((vars->sems).forks_sem);
	if (vars->is_someone_dead)
	{
		sem_post((vars->sems).forks_sem);
		sem_post((vars->sems).waiter);
		return ;
	}
	write_log(vars, TAKE_FORK_LOG, id);
	sem_wait((vars->sems).forks_sem);
	if (vars->is_someone_dead)
	{
		drop_forks(vars);
		sem_post((vars->sems).waiter);
		return ;
	}
	write_log(vars, TAKE_FORK_LOG, id);
	sem_post((vars->sems).waiter);
}

void	take_forks(t_vars *vars, int id)
{
	if (vars->nbr_of_philos == 1)
	{
		write_log(vars, TAKE_FORK_LOG, id);
		while (!(vars->is_someone_dead))
			;
		return ;
	}
	take_forks_inside(vars, id);
}

void	drop_forks(t_vars *vars)
{
	sem_post((vars->sems).forks_sem);
	sem_post((vars->sems).forks_sem);
}

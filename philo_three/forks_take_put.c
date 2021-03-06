/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_take_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:38:00 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 16:39:58 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	take_forks(t_vars *vars, int id)
{
	sem_wait((vars->sems).waiter);
	sem_wait((vars->sems).forks_sem);
	write_log(vars, TAKE_FORK_LOG, id);
	sem_wait((vars->sems).forks_sem);
	write_log(vars, TAKE_FORK_LOG, id);
	sem_post((vars->sems).waiter);
}

void	drop_forks(t_vars *vars)
{
	sem_post((vars->sems).forks_sem);
	sem_post((vars->sems).forks_sem);
}

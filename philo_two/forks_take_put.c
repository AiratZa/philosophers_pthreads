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

void	take_forks(t_vars *vars, int id)
{
	int right_fork_index;

	right_fork_index = id % vars->nbr_of_philos;
	if (vars->nbr_of_philos == 1)
	{
		write_log(vars, TAKE_FORK_LOG, id);
		while (!(vars->is_someone_dead))
			;
		return ;
	}
	sem_wait((vars->sems).max_visitors_sem);
	if (vars->is_someone_dead)
		return ;
	write_log(vars, TAKE_FORK_LOG, id);
	write_log(vars, TAKE_FORK_LOG, id);
}

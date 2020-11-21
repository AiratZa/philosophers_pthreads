/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_take_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:38:00 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/21 16:27:19 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_forks_first_own(t_vars *vars, int id, int right_fork_index)
{
	if (vars->is_someone_dead)
		return ;
	pthread_mutex_lock(&((vars->mtxs).forks_mtxs[id - 1]));
	if (vars->is_someone_dead)
	{
		pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[id - 1]));
		return ;
	}
	write_log(vars, TAKE_FORK_LOG, id);
	pthread_mutex_lock(&((vars->mtxs).forks_mtxs[right_fork_index]));
	if (vars->is_someone_dead)
	{
		drop_forks(vars, id);
		return ;
	}
	write_log(vars, TAKE_FORK_LOG, id);
}

void	take_forks_first_neighbor(t_vars *vars, int id, int right_fork_index)
{
	if (vars->is_someone_dead)
		return ;
	pthread_mutex_lock(&((vars->mtxs).forks_mtxs[right_fork_index]));
	if (vars->is_someone_dead)
	{
		pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[right_fork_index]));
		return ;
	}
	write_log(vars, TAKE_FORK_LOG, id);
	pthread_mutex_lock(&((vars->mtxs).forks_mtxs[id - 1]));
	if (vars->is_someone_dead)
	{
		drop_forks(vars, id);
		return ;
	}
	write_log(vars, TAKE_FORK_LOG, id);
}

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
	if (id % 2)
		take_forks_first_own(vars, id, right_fork_index);
	else
		take_forks_first_neighbor(vars, id, right_fork_index);
}

void	drop_forks(t_vars *vars, int id)
{
	int right_fork_index;

	right_fork_index = id % vars->nbr_of_philos;
	if (id % 2)
	{
		pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[id - 1]));
		pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[right_fork_index]));
	}
	else
	{
		pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[right_fork_index]));
		pthread_mutex_unlock(&((vars->mtxs).forks_mtxs[id - 1]));
	}
}

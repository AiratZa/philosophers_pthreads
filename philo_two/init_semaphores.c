/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:58:24 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 18:12:58 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

sem_t	*ft_sem_open_protected(const char *sem_name, unsigned int sem_value)
{
	sem_t *sem;

	sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, sem_value);
	if (sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			if (sem_unlink(sem_name))
				return (NULL);
			return (ft_sem_open_protected(sem_name, sem_value));
		}
		return (NULL);
	}
	return (sem);
}

int		ft_init_semaphores(t_vars *vars)
{
	if (!((vars->sems).forks_sem = ft_sem_open_protected("FT_FORKS", \
											vars->nbr_of_philos)))
		return (-1);
	if (!((vars->sems).waiter = ft_sem_open_protected("FT_WAITER", 1)))
		return (-1);
	if (!((vars->sems).philo_dead_sem = ft_sem_open_protected("FT_PHDEAD", 1)))
		return (-1);
	if (!((vars->sems).write_log_sem = ft_sem_open_protected("FT_WR_LOG", 1)))
		return (-1);
	if (!((vars->sems).protect_when_eat_sem = \
						ft_sem_open_protected("FT_PROTECT_WHEN_EAT", 1)))
		return (-1);
	return (0);
}

void	init_vals_for_sems(t_vars *vars)
{
	(vars->sems).forks_sem = NULL;
	(vars->sems).waiter = NULL;
	(vars->sems).write_log_sem = NULL;
	(vars->sems).philo_dead_sem = NULL;
	(vars->sems).protect_when_eat_sem = NULL;
}

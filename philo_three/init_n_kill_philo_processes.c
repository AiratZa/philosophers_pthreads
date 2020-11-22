/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_kill_philo_processes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:04:28 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 17:06:59 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	kill_philo_processes(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->nbr_of_philos)
	{
		kill((vars->philos)[i].fork_proccess, SIGKILL);
		i++;
	}
}

int		ft_init_philos_processes(t_vars *vars)
{
	int		i;
	pid_t	pid;

	i = 0;
	vars->start_time = ft_get_timestamp_ms();
	while (i < vars->nbr_of_philos)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		else if (pid == 0)
		{
			life_cycle((void *)(&((vars->philos)[i])));
			exit(0);
		}
		else
			(vars->philos)[i].fork_proccess = pid;
		i++;
	}
	return (0);
}

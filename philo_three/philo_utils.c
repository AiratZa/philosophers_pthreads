/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:36 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 17:13:42 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long long int	ft_get_timestamp_ms(void)
{
	long long int	ret;
	struct timeval	now;

	gettimeofday(&now, NULL);
	ret = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (ret);
}

/*
** usleep makes sleep for microsecs(milllisecs / 1000)
*/

int				sleep_exact_ms(int ms_count)
{
	long long int				start;
	long long int				current;
	long long int				remains;

	remains = 0;
	start = ft_get_timestamp_ms();
	while (remains < ms_count)
	{
		current = ft_get_timestamp_ms();
		remains = current - start;
		usleep(10);
	}
	return (0);
}

void			ft_put_error(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(CLR_RESET, 2);
}

void			free_vars(t_vars *vars)
{
	int i;

	i = 0;
	if (vars->philos)
	{
		while (i < vars->nbr_of_philos)
		{
			if ((vars->philos)[i].ate_enough)
				sem_close((vars->philos)[i].ate_enough);
			if ((vars->philos)[i].fork_proccess)
				kill((vars->philos)[i].fork_proccess, SIGKILL);
			i++;
		}
		free(vars->philos);
	}
	if ((vars->sems).forks_sem)
		sem_close((vars->sems).forks_sem);
	if ((vars->sems).waiter)
		sem_close((vars->sems).waiter);
	if ((vars->sems).write_log_sem)
		sem_close((vars->sems).write_log_sem);
	if ((vars->sems).philo_dead_sem)
		sem_close((vars->sems).philo_dead_sem);
	if ((vars->sems).protect_when_eat_sem)
		sem_close((vars->sems).protect_when_eat_sem);
}

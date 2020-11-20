/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:36 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/20 05:58:29 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long long int	ft_get_timestamp_ms()
{
	long long int	ret;
	struct timeval now;
	gettimeofday(&now, NULL);
	ret = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (ret);
}

/*
** usleep makes sleep for microsecs(milllisecs / 1000)
*/

void		sleep_exact_ms(t_vars *vars, int ms_count)
{
	long long int				start;
	long long int				current;
	long long int				remains;

	remains = 0;
	start = ft_get_timestamp_ms();
	while (remains < ms_count)
	{
		if (vars->is_someone_dead)
			break ;
		current = ft_get_timestamp_ms();
		remains = current - start;
		usleep(10);
	}
}

void	ft_put_error(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(CLR_RESET, 2);
}

void	free_vars(t_vars *vars)
{
	int i;

	if ((vars->mtxs).forks_mtxs)
		free((vars->mtxs).forks_mtxs);
	if (vars->philos)
		free(vars->philos);
	return ;
}

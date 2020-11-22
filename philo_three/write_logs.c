/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:39 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 12:43:02 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static char	*get_color(const int log_type)
{
	if (log_type == TAKE_FORK_LOG)
		return (BLUE);
	else if (log_type == EAT_LOG)
		return (MAGENTA);
	else if (log_type == SLEEP_LOG)
		return (CYAN);
	else if (log_type == THINK_LOG)
		return (YELLOW);
	return (RED);
}

static char	*ft_get_action_log(const int log_type)
{
	if (log_type == TAKE_FORK_LOG)
		return ("has taken a fork");
	else if (log_type == EAT_LOG)
		return ("is eating");
	else if (log_type == SLEEP_LOG)
		return ("is sleeping");
	else if (log_type == THINK_LOG)
		return ("is thinking");
	return ("died");
}

void		write_log(t_vars *vars, const int log_type, int id)
{
	char			*color;
	long long int	timestamp;

	color = get_color(log_type);
	sem_wait((vars->sems).write_log_sem);
	ft_putstr_fd(color, 1);
	timestamp = ft_get_timestamp_ms() - vars->start_time;
	ft_putnbr_fd(timestamp, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(id, 1);
	ft_putchar_fd(' ', 1);
	ft_putendl_fd(ft_get_action_log(log_type), 1);
	ft_putstr_fd(CLR_RESET, 1);
	if (log_type == DIE_LOG)
	{
		sem_post((vars->sems).philo_dead_sem);
		return ;
	}
	sem_post((vars->sems).write_log_sem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:39 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/20 05:03:19 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static char    *get_color(const char *log_type)
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

void    write_log(t_vars *vars, const char *log_type, int id)
{
    char *color;
    char *action;
    long long int timestamp;

    if (vars->is_someone_dead == 0)
    {
        color = get_color(log_type);
        pthread_mutex_lock(&((vars->mtxs).write_log_mtx));
        if (vars->is_someone_dead)
        {
            pthread_mutex_unlock(&((vars->mtxs).write_log_mtx));
            return ;
        }
        ft_putstr_fd(color, 1);
        timestamp = ft_get_timestamp_ms() - vars->start_time;
        ft_putnbr_fd(timestamp, 1);
        ft_putchar_fd(' ', 1);
        ft_putnbr_fd(id, 1);
        ft_putchar_fd(' ', 1);
        ft_putendl_fd(log_type, 1); 
        ft_putstr_fd(CLR_RESET, 1);
        pthread_mutex_unlock(&((vars->mtxs).write_log_mtx));
    }
}
#include "philo_one.h"

/*
**  1 = has taken a fork
**  2 = is eating
**  3 = is sleeping
**  4 = is thinking
** -1 =  died
*/

static char    *get_color(int type)
{
    if (type == 1)
        return (BLUE);
    else if (type == 2)
        return (MAGENTA);
    else if (type == 3)
        return (YELLOW);
    else if (type == 4)
        return (CYAN);
    return (RED);
}

static char    *get_action(int type)
{
    if (type == 1)
        return (TAKE_FORK_LOG);
    else if (type == 2)
        return (EAT_LOG);
    else if (type == 3)
        return (SLEEP_LOG);
    else if (type == 4)
        return (THINK_LOG);
    return (DIE_LOG);
}

void    write_log(t_vars *vars, int type, int id)
{
    char *color;
    char *action;
    long long int timestamp;

    timestamp = ft_get_timestamp_ms() - vars->start_time;
    if (vars->is_someone_dead == 0)
    {
        color = get_color(type);
        action = get_action(type);
        pthread_mutex_lock(&((vars->mtxs).write_log_mtx));
        if (vars->is_someone_dead)
        {
            pthread_mutex_unlock(&((vars->mtxs).write_log_mtx));
            return ;
        }
        ft_putstr_fd(color, 1);
        ft_putnbr_fd(timestamp, 1);
        ft_putchar_fd(' ', 1);
        ft_putnbr_fd(id, 1);
        ft_putchar_fd(' ', 1);
        ft_putendl_fd(action, 1);
        ft_putstr_fd(CLR_RESET, 1);
        pthread_mutex_unlock(&((vars->mtxs).write_log_mtx));
    }
}
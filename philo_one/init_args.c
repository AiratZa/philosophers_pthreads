/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:53:11 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/20 05:15:24 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	create_philos(t_vars *vars)
{
	int i;
	const int must_eat = vars->philos_must_eat_times_nbr;

	i = 0;
	if (!(vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->nbr_of_philos)))
		return (-1);
	while (i < vars->nbr_of_philos)
	{
		(vars->philos)[i].id = i + 1;
		(vars->philos)[i].eatiing_count = (must_eat)? must_eat : 1;
		(vars->philos)[i].lst_meal = 0;
		pthread_mutex_init(&((vars->philos)[i].eat_mtx), NULL);
		pthread_mutex_lock(&((vars->philos)[i].eat_mtx));
		(vars->philos)[i].vars = vars;
		i++;
	}	return (0);
}

int init_mtxs(t_vars *vars)
{
	int i;
	
	i = 0;
	if (!((vars->mtxs).forks_mtxs = (pthread_mutex_t *)malloc(\
				sizeof(pthread_mutex_t) * vars->nbr_of_philos)))
		return (-1);
	while (i < (vars->nbr_of_philos))
	{
		pthread_mutex_init(&((vars->mtxs).forks_mtxs[i]), NULL);
		i++;
	}
	pthread_mutex_init(&((vars->mtxs).philo_dead_mtx), NULL);
	pthread_mutex_init(&((vars->mtxs).write_log_mtx), NULL);
	pthread_mutex_init(&((vars->mtxs).protect_when_eat_mtx), NULL);
	return (0);
}


int init_args_n_do_cycles(t_vars *vars, char **argv)
{
	vars->philos = NULL;
	if (parse_n_check_args(vars, argv))
		return (-1);
	if (init_mtxs(vars))
		return (-1);
	if (create_philos(vars))
		return (-1);
	if (vars->philos_must_eat_times_nbr)
	{
		activate_eating_count_monitoring(vars);
	}
	vars->is_someone_dead = 0;
	int i;
	i = 0;
    vars->start_time = ft_get_timestamp_ms();
	while (i < vars->nbr_of_philos)
	{
		if (pthread_create(&(((vars->philos)[i]).thread), NULL, \
						life_cycle, (void *)(&((vars->philos)[i]))))
			return (-1);
		i++;
	}
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		pthread_join(((vars->philos)[i]).thread, NULL);
		i++;
	}
	if (!(vars->is_someone_dead))
		vars->is_someone_dead = 0;
	return (0);
}

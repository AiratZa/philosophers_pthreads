/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:53:11 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/21 20:04:37 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

sem_t *ft_sem_open_protected(const char *sem_name, unsigned int sem_value)
{
	sem_t *sem;

	sem = sem_open (sem_name, O_CREAT | O_EXCL, 0644, sem_value);
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

int		create_philos(t_vars *vars)
{
	int i;

	i = 0;
	if (!(vars->philos = (t_philo *)malloc(sizeof(t_philo) * \
													vars->nbr_of_philos)))
		return (-1);
	while (i < vars->nbr_of_philos)
	{
		(vars->philos)[i].id = i + 1;
		(vars->philos)[i].lst_meal = 0;
		if (!((vars->philos)[i].eat_sem = ft_sem_open_protected("FT_EAT_STATUS", 1)))
			return (-1);
		if (sem_wait((vars->philos)[i].eat_sem))
			return (-1);
		(vars->philos)[i].vars = vars;
		i++;
	}
	return (0);
}

int		ft_init_semaphores(t_vars *vars)
{

	if (!((vars->sems).max_visitors_sem = ft_sem_open_protected("FT_MAX_VISITORS", vars->nbr_of_philos - 1)))
		return (-1);
	if (!((vars->sems).philo_dead_sem = ft_sem_open_protected("FT_PHILO_DEAD", 1)))
		return (-1);
	if (!((vars->sems).write_log_sem = ft_sem_open_protected("FT_WRITE_LOG", 1)))
		return (-1);
	if (!((vars->sems).protect_when_eat_sem = ft_sem_open_protected("FT_PROTECT_WHEN_EAT", 1)))
		return (-1);
	return (0);
}

int		init_args(t_vars *vars, char **argv)
{
	if (parse_n_check_args(vars, argv))
		return (-1);
	if (ft_init_semaphores(vars))
		return (-1);
	if (create_philos(vars))
		return (-1);
	if (vars->philos_must_eat_times_nbr)
	{
		if (activate_eating_count_monitoring(vars))
			return (-1);
	}
	vars->is_someone_dead = 0;
	vars->start_time = ft_get_timestamp_ms();
	return (0);
}



int		init_args_n_do_cycles(t_vars *vars, char **argv)
{
	int i;

	i = 0;
	if (init_args(vars, argv))
		return (-1);
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
		if (pthread_join(((vars->philos)[i]).thread, NULL))
			return (-1);
		i++;
	}
	// destroy_mutexes(vars);
	return (0);
}

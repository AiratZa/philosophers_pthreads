/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:53:11 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 17:12:53 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_init_values(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->nbr_of_philos)
	{
		(vars->philos)[i].ate_enough = NULL;
		(vars->philos)[i].fork_proccess = 0;
		i++;
	}
}

int		create_philos(t_vars *vars)
{
	int		i;
	char	*name;

	name = NULL;
	i = 0;
	if (!(vars->philos = (t_philo *)malloc(sizeof(t_philo) * \
													vars->nbr_of_philos)))
		return (-1);
	philo_init_values(vars);
	while (i < vars->nbr_of_philos)
	{
		(vars->philos)[i].id = i + 1;
		(vars->philos)[i].lst_meal = 0;
		if (!(name = ft_itoa_re(i)))
			return (-1);
		if (!((vars->philos)[i].ate_enough = ft_sem_open_protected(name, 1)))
			return (-1);
		free(name);
		if (sem_wait((vars->philos)[i].ate_enough))
			return (-1);
		(vars->philos)[i].vars = vars;
		i++;
	}
	return (0);
}

int		init_args(t_vars *vars, char **argv)
{
	init_vals_for_sems(vars);
	if (parse_n_check_args(vars, argv))
		return (return_value_handler(-3));
	if (ft_init_semaphores(vars))
		return (return_value_handler(-4));
	if (create_philos(vars))
		return (return_value_handler(-5));
	if (vars->philos_must_eat_times_nbr)
	{
		if (activate_eating_count_monitoring(vars))
			return (return_value_handler(-6));
	}
	return (0);
}

int		init_args_n_do_cycles(t_vars *vars, char **argv)
{
	if (init_args(vars, argv))
		return (-1);
	sem_wait((vars->sems).philo_dead_sem);
	if (ft_init_philos_processes(vars))
		return (return_value_handler(-2));
	sem_wait((vars->sems).philo_dead_sem);
	kill_philo_processes(vars);
	return (0);
}

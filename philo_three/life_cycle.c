/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:41 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 17:34:04 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_eat(t_vars *vars, int id)
{
	sem_wait((vars->sems).protect_when_eat_sem);
	(vars->philos)[id - 1].lst_meal = ft_get_timestamp_ms();
	((vars->philos)[id - 1]).max_hunger = (vars->philos)[id - 1].lst_meal + \
											vars->time_to_die;
	write_log(vars, EAT_LOG, id);
	sem_post((vars->sems).protect_when_eat_sem);
	sleep_exact_ms(vars->time_to_eat);
	if (vars->philos_must_eat_times_nbr)
	{
		((vars->philos)[id - 1]).eat_count++;
		if (((vars->philos)[id - 1]).eat_count == \
										vars->philos_must_eat_times_nbr)
			sem_post(((vars->philos)[id - 1]).ate_enough);
	}
}

void	ft_sleep(t_vars *vars, int id)
{
	drop_forks(vars);
	write_log(vars, SLEEP_LOG, id);
	sleep_exact_ms(vars->time_to_sleep);
}

void	life_cycle_inside(t_vars *vars, int id)
{
	while (1)
	{
		take_forks(vars, id);
		ft_eat(vars, id);
		ft_sleep(vars, id);
		write_log(vars, THINK_LOG, id);
	}
}

void	*life_cycle(void *philo_struct)
{
	t_philo	*philo;
	t_vars	*vars;
	int		id;

	philo = (t_philo *)philo_struct;
	id = philo->id;
	vars = philo->vars;
	philo->eat_count = 0;
	philo->lst_meal = vars->start_time;
	philo->max_hunger = philo->lst_meal + vars->time_to_die;
	if (activate_health_monitoring(vars, id, philo_struct))
		return_value_handler(-7);
	life_cycle_inside(vars, id);
	return (NULL);
}

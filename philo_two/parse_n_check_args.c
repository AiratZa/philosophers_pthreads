/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_n_check_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:29 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/21 18:37:55 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	set_config_value_by_id(int id, int value, t_vars *vars)
{
	if (id == 1)
		vars->nbr_of_philos = value;
	else if (id == 2)
		vars->time_to_die = value;
	else if (id == 3)
		vars->time_to_eat = value;
	else if (id == 4)
		vars->time_to_sleep = value;
	else if (id == 5)
		vars->philos_must_eat_times_nbr = value;
}

int		convert_to_int_n_check_min_val(char **argv, int arg_nbr, t_vars *vars)
{
	int	value;

	value = ft_atoi_re(argv[arg_nbr]);
	if (value < 0)
	{
		ft_put_error("Provided args cannot be equal/lower than zero.\
OR found not numbers");
		return (-1);
	}
	set_config_value_by_id(arg_nbr, value, vars);
	return (0);
}

int		parse_n_check_args(t_vars *vars, char **argv)
{
	vars->philos_must_eat_times_nbr = 0;
	if (convert_to_int_n_check_min_val(argv, 1, vars))
		return (-1);
	if (convert_to_int_n_check_min_val(argv, 2, vars))
		return (-1);
	if (convert_to_int_n_check_min_val(argv, 3, vars))
		return (-1);
	if (convert_to_int_n_check_min_val(argv, 4, vars))
		return (-1);
	if (argv[5])
	{
		if (convert_to_int_n_check_min_val(argv, 5, vars))
			return (-1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:32 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 19:00:04 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	return_value_handler(int ret)
{
	if (ret == -2)
		ft_put_error("You've requested nbr of procs that PC couldnt create");
	else if (ret == -3)
		ft_put_error("Error occured when parse and check args values");
	else if (ret == -4)
		ft_put_error("Error occured when init main semaphores");
	else if (ret == -5)
		ft_put_error("Error occured when initialize philos and their sems");
	else if (ret == -6)
		ft_put_error("Error occured when activate eat count monitoring");
	else if (ret == -7)
		ft_put_error("Error occured when activate eat health monitoring");
	else
		ft_put_error("Happens something bad...");
	return (-1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		ret;

	vars.philos = NULL;
	if ((argc == 5) || (argc == 6))
	{
		if ((ret = init_args_n_do_cycles(&vars, argv)))
		{
			free_vars(&vars);
			return (-1);
		}
	}
	else
	{
		ft_put_error("Number of args (options) is not 5 or 6");
		return (-1);
	}
	free_vars(&vars);
	return (0);
}

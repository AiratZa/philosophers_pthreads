/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:32 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/20 05:56:54 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_vars vars;
	int i;
	char *test;

	if ((argc == 5) || (argc == 6))
	{
		if (init_args_n_do_cycles(&vars, argv))
		{
			ft_put_error("Happens something bad...");
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
	// while (1)
	// 	;
	return (0);
}
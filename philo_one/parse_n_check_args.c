#include "philo_one.h"

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

void	show_min_value_error(int arg_nbr)
{
	if (arg_nbr == 1)
        ft_put_error("Number_of_philosophers must be at least two");
	else
		ft_put_error("Time value/repeat nbr cannot be lower than zero");
}

int	convert_to_int_n_check_min_value(char **argv, int arg_nbr, t_vars *vars)
{
	int	value;
	int	min_val;

	min_val = (arg_nbr == 1) ? 2 : 0;
	value = ft_atoi(argv[arg_nbr]);
	if (value < min_val)
	{
		show_min_value_error(arg_nbr);
		return (-1);
	}
	set_config_value_by_id(arg_nbr, value, vars);
	return (0);
}

int	parse_n_check_args(t_vars *vars, char **argv)
{
	vars->philos_must_eat_times_nbr = 0;
	if (convert_to_int_n_check_min_value(argv, 1, vars))
		return (-1);
	if (convert_to_int_n_check_min_value(argv, 2, vars))
		return (-1);
	if (convert_to_int_n_check_min_value(argv, 3, vars))
		return (-1);
	if (convert_to_int_n_check_min_value(argv, 4, vars))
		return (-1);
	if (argv[5])
	{
		if (convert_to_int_n_check_min_value(argv, 5, vars))
			return (-1);
	}
	return (0);
}

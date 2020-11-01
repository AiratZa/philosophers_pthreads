#include "philo_one.h"

typedef struct s_config
{
	int	nbr_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	with_external_param;
	int	philos_must_eat_times_nbr;
}				t_config;


/*
** STATUS DETAILS
**  0 = simulation's just started
**  1 = has taken a fork
**  2 = is eating
**  3 = is sleeping
**  4 = is thinking
** -1 =  died
*/

typedef struct s_philo
{
	int	id;
	int	lft_fork;
	int	rght_fork;
	int	first;
	int	last;
	int	status;
}				t_philo;

void	set_value_to_conf_by_id(int id, int value, t_config *conf)
{
	if (id == 1)
		conf->nbr_of_philos = value;
	else if (id == 2)
		conf->time_to_die = value;
	else if (id == 3)
		conf->time_to_eat = value;
	else if (id == 4)
		conf->time_to_sleep = value;
	else if (id == 5)
	{
		conf->with_external_param = 1;
		conf->philos_must_eat_times_nbr = value;
	}
}

void	show_min_value_error(int arg_nbr)
{
	if (arg_nbr == 1)
		ft_putendl_fd("Number_of_philosophers must be at least one", 2);
	else
		ft_putendl_fd("Time value/repeat nbr cannot be lower than zero", 2);
}

int	convert_to_int_n_check_min_value(char **argv, int arg_nbr, t_config *conf)
{
	int	value;
	int	min_val;

	min_val = (arg_nbr == 1) ? 1 : 0;
	value = ft_atoi(argv[arg_nbr]);
	if (value < min_val)
	{
		show_min_value_error(arg_nbr);
		return (-1);
	}
	set_value_to_conf_by_id(arg_nbr, value, conf);
	return (0);
}

int	create_philos(t_config *conf)
{
	t_philo *philos;
	int	i;

	i = 1;
	if (!(philos = (t_philo *)malloc(sizeof(t_philo) * (conf->nbr_of_philos + 1))))
		return (-1);
	while (i <= conf->nbr_of_philos)
	{
		philos[i].id = i;
		philos[i].first = ((i == 1) ? 1 : 0); 
		philos[i].last = ((i == conf->nbr_of_philos) ? 1 : 0); 
		philos[i].lft_fork = ((i == 1) ? 1 : 0); 
		philos[i].rght_fork = ((i == conf->nbr_of_philos) ? 0 : 1); 
		philos[i].status = 0;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_config conf;
	if ((argc == 5) || (argc == 6))
	{
		if (convert_to_int_n_check_min_value(argv, 1, &conf))
			return (-1);
		if (convert_to_int_n_check_min_value(argv, 2, &conf))
			return (-1);
		if (convert_to_int_n_check_min_value(argv, 3, &conf))
			return (-1);
		if (convert_to_int_n_check_min_value(argv, 4, &conf))
			return (-1);
		if (argv[5])
		{
			if (convert_to_int_n_check_min_value(argv, 5, &conf))
				return (-1);
		}
		else
			conf.with_external_param = 0;

		int i = 0;
		while (i < 25)
		{
			struct timeval current_time;
			gettimeofday(&current_time, NULL);
			printf("seconds : %ld\nmicro seconds : %ld\n",
				current_time.tv_sec, current_time.tv_usec);
			i++;
		}
		create_philos(&conf);
	}
	else
	{
		printf("error!\n");
	}
	return (0);
}
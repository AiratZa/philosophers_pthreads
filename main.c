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
	int	fork_count;
	int	lft_fork;
	int	rght_fork;
	int	first;
	int	last;
	int	status;
	pthread_t thread;

}				t_philo;


typedef struct s_main
{
	t_config conf;
	t_philo **philos;
}				t_main;

typedef struct s_thrd_info
{
	int	id;
	t_main *vars;
}				t_thrd_info;

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

int	eating(t_philo **philos, int id, t_config *conf)
{
	gettimeofday(&current_time, NULL);
	ft_putnbr_fd((int)current_time.tv_usec, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(id, 1);
	ft_putchar_fd(' ', 1);
	ft_putendl_fd(EAT_LOG, 1);
	return (0);
}

int	sleeping(t_philo **philos, int id, t_config *conf)
{
	int pos;

	pos = id - 1;
	if (philos[pos]->first)
	{
		philos[pos]->fork_count = 0;
		philos[pos]->lft_fork = 1;
		philos[pos]->rght_fork = 1;
	}
	else if (philos[pos]->last)
	{
		philos[pos]->fork_count = 0;
		philos[0]->lft_fork = 1;
		philos[pos - 1]->rght_fork = 1;
	}
	gettimeofday(&current_time, NULL);
	ft_putnbr_fd((int)current_time.tv_usec, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(id, 1);
	ft_putchar_fd(' ', 1);
	ft_putendl_fd(SLEEP_LOG, 1);
	return (0);
}

int	thinking(t_philo **philos, int id, t_config *conf)
{
	gettimeofday(&current_time, NULL);
	ft_putnbr_fd((int)current_time.tv_usec, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(id, 1);
	ft_putchar_fd(' ', 1);
	ft_putendl_fd(THINK_LOG, 1);
	return (0);
}


int	taking_forks(t_philo **philos, int id, t_config *conf)
{
	int pos;

	pos = id - 1;
	if (philos[pos]->first)
	{
		while(1)
		{
			if (philos[pos]->lft_fork || philos[pos]->rght_fork)
			{
				if (philos[pos]->lft_fork)
				{
					philos[pos]->lft_fork = 0;	
					philos[pos]->fork_count++;
				}
				else
				{
					philos[pos]->rght_fork = 0;	
					philos[pos]->fork_count++;
				}
				gettimeofday(&current_time, NULL);
				ft_putstr_fd(ft_itoa((int)current_time.tv_usec), 1);
				ft_putchar_fd(' ', 1);
				ft_putnbr_fd(id, 1);
				ft_putchar_fd(' ', 1);
				ft_putendl_fd(TAKE_FORK_LOG, 1);
				if (philos[pos]->fork_count == 2)
					return (0);
			}
		}
	}
	else if (philos[pos]->last)
	{
		while(1)
		{
			if (philos[0]->lft_fork || philos[pos - 1]->rght_fork)
			{
				if (philos[0]->lft_fork)
				{
					philos[0]->lft_fork = 0;	
					philos[pos]->fork_count++;
				}
				else
				{
					philos[pos - 1]->rght_fork = 0;	
					philos[pos]->fork_count++;
				}
				gettimeofday(&current_time, NULL);
				ft_putstr_fd(ft_itoa((int)current_time.tv_usec), 1);
				ft_putchar_fd(' ', 1);
				ft_putnbr_fd(id, 1);
				ft_putchar_fd(' ', 1);
				ft_putendl_fd(TAKE_FORK_LOG, 1);
				if (philos[pos]->fork_count == 2)
					return (0);
			}
		}
	}
	else
	{
		return (1);
	}

	return (0);
}


void *life_cycle(void *info_void)
{
	t_thrd_info *info;
	t_philo **philos;
	t_config conf;
	int	id;
	int	ret;

	info = (t_thrd_info *)info_void;
	id = info->id;
	conf = info->vars->conf;
	philos = info->vars->philos;
	// printf("IM HERE ID == %d\n", id);
	while (1)
	{
			if ((ret = taking_forks(philos, id, &conf)) == 0)
			{
				if ((ret = eating(philos, id, &conf) == 0))
				{
					if ((ret = sleeping(philos, id, &conf) == 0))
					{
						if ((ret = thinking(philos, id, &conf) != 0))
							printf("he is died\n");
					}
				}
			}
			else
			{
				printf("error fork\n");
				break ;
			}
			sleep(1);
	}
	return (NULL);
}

int	create_philos(t_main *vars)
{
	int	i;

	i = 0;
	if (!(vars->philos = (t_philo **)malloc(sizeof(t_philo*) * ((vars->conf).nbr_of_philos + 1))))
		return (-1);
	while (i < (vars->conf).nbr_of_philos)
	{
		(vars->philos)[i] = (t_philo *)malloc(sizeof(t_philo));
		i++;
	}
	t_thrd_info **infos;
	if (!(infos = (t_thrd_info **)malloc(sizeof(t_thrd_info*) * ((vars->conf).nbr_of_philos + 1))))
		return (-1);
	i = 0;
	while (i < (vars->conf).nbr_of_philos)
	{
		infos[i] = (t_thrd_info *)malloc(sizeof(t_thrd_info));
		i++;
	}

	i = 0;
	while (i < (vars->conf).nbr_of_philos)
	{
		t_philo *philo;

		philo = (vars->philos)[i];
		philo->id = i + 1;
		philo->first = ((i == 0) ? 1 : 0); 
		philo->last = ((i == ((vars->conf).nbr_of_philos -1)) ? 1 : 0); 
		philo->lft_fork = ((i == 0) ? 1 : 0); 
		philo->rght_fork = ((i == ((vars->conf).nbr_of_philos - 1)) ? 0 : 1); 
		philo->status = 0;
		philo->fork_count = 0;
		infos[i]->id = i + 1;
		infos[i]->vars = vars;
		i++;
	}
	(vars->philos)[i] = NULL;

	i = 0;
	while (i < (vars->conf).nbr_of_philos)
	{
		pthread_create(&((vars->philos)[i]->thread), NULL, life_cycle, (void *)(infos[i]));//(void *)(&(philos[i]->id))
		// printf("hey %d\n", i);
		i++;
	}
	// printf("mann\n");
	infos[i] = NULL;
	
	return (0);
}


int	main(int argc, char **argv)
{
	t_main vars;
	vars.philos = NULL;
	// t_config conf;

	if ((argc == 5) || (argc == 6))
	{
		if (convert_to_int_n_check_min_value(argv, 1, &(vars.conf)))
			return (-1);
		if (convert_to_int_n_check_min_value(argv, 2, &(vars.conf)))
			return (-1);
		if (convert_to_int_n_check_min_value(argv, 3, &(vars.conf)))
			return (-1);
		if (convert_to_int_n_check_min_value(argv, 4, &(vars.conf)))
			return (-1);
		if (argv[5])
		{
			if (convert_to_int_n_check_min_value(argv, 5, &(vars.conf)))
				return (-1);
		}
		else
			(vars.conf).with_external_param = 0;

		// int i = 0;
		// while (i < 25)
		// {
		// 	struct timeval current_time;
		// 	gettimeofday(&current_time, NULL);
		// 	printf("seconds : %ld\nmicro seconds : %ld\n",
		// 		current_time.tv_sec, current_time.tv_usec);
		// 	i++;
		// }
		create_philos(&vars);
		int i;

		i = 0;
		while (i < (vars.conf).nbr_of_philos)
		{
			pthread_join((vars.philos)[i]->thread, NULL);
			i++;
		}
	}
	else
	{
		printf("error!\n");
	}
		return (0);
}
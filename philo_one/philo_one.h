/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:47 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 18:36:59 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define TAKE_FORK_LOG 1
# define EAT_LOG 2
# define SLEEP_LOG 3
# define THINK_LOG 4
# define DIE_LOG -1
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define CLR_RESET	"\x1b[0m"

typedef struct			s_philo
{
	int					id;
	long long int		lst_meal;
	long long int		max_hunger;
	pthread_mutex_t		ate_enough_mtx;
	pthread_t			thread;
	pthread_t			hungry_monitor;
	struct s_vars		*vars;
	int					eat_count;
}						t_philo;

typedef struct			s_mtxs
{
	pthread_mutex_t		*forks_mtxs;
	pthread_mutex_t		write_log_mtx;
	pthread_mutex_t		philo_dead_mtx;
	pthread_mutex_t		protect_when_eat_mtx;
}						t_mtxs;

typedef struct			s_vars
{
	t_philo				*philos;
	t_mtxs				mtxs;
	int					nbr_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					philos_must_eat_times_nbr;
	long long int		start_time;
	int					is_someone_dead;
	pthread_t			eating_count_monitoring;
}						t_vars;

/*
** Core funcs
*/

int						init_args_n_do_cycles(t_vars *vars, char **argv);

int						convert_to_int_n_check_min_value(char **argv, \
										int arg_nbr, t_vars *vars);

void					*life_cycle(void *info_void);

/*
** Philo utils
*/

long long int			ft_get_timestamp_ms(void);

int						sleep_exact_ms(t_vars *vars, int ms_count);

void					ft_put_error(char *str);

void					write_log(t_vars *vars, const int log_type, int id);

int						parse_n_check_args(t_vars *vars, char **argv);

void					free_vars(t_vars *vars);

void					take_forks(t_vars *vars, int id);

void					drop_forks(t_vars *vars, int id);

int						activate_health_monitoring(t_vars *vars, int id, \
						void *philo_struct);

int						activate_eating_count_monitoring(t_vars *vars);

/*
** Libft utils
*/

int						ft_atoi_re(const char *nptr);

void					ft_putchar_fd(char c, int fd);

void					ft_putstr_fd(const char *s, int fd);

void					ft_putendl_fd(const char *s, int fd);

void					ft_putnbr_fd(long long int n, int fd);

#endif

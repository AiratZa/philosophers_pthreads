/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:46:47 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 17:09:48 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
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
	sem_t				*ate_enough;
	pid_t				fork_proccess;
	pthread_t			hungry_monitor;
	pthread_t			check_enough_ate;
	struct s_vars		*vars;
	int					eat_count;
}						t_philo;

typedef struct			s_sems
{
	sem_t *forks_sem;
	sem_t *waiter;
	sem_t *write_log_sem;
	sem_t *philo_dead_sem;
	sem_t *protect_when_eat_sem;
}						t_sems;

typedef struct			s_vars
{
	t_philo				*philos;
	t_sems				sems;
	int					nbr_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					philos_must_eat_times_nbr;
	long long int		start_time;
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

int						sleep_exact_ms(int ms_count);

void					ft_put_error(char *str);

void					write_log(t_vars *vars, const int log_type, int id);

int						parse_n_check_args(t_vars *vars, char **argv);

void					free_vars(t_vars *vars);

void					take_forks(t_vars *vars, int id);

int						activate_health_monitoring(t_vars *vars, int id, \
						void *philo_struct);

int						activate_eating_count_monitoring(t_vars *vars);

void					init_vals_for_sems(t_vars *vars);

sem_t					*ft_sem_open_protected(const char *sem_name, \
										unsigned int sem_value);

int						ft_init_semaphores(t_vars *vars);

int						ft_init_philos_processes(t_vars *vars);

void					kill_philo_processes(t_vars *vars);

/*
** Libft utils
*/

int						ft_atoi_re(const char *nptr);

void					ft_putchar_fd(char c, int fd);

void					ft_putstr_fd(const char *s, int fd);

void					ft_putendl_fd(const char *s, int fd);

void					ft_putnbr_fd(long long int n, int fd);

void					drop_forks(t_vars *vars);

char					*ft_itoa_re(int n);

int						return_value_handler(int ret);

#endif

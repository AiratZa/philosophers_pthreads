#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define TAKE_FORK_LOG "has taken a fork"
# define EAT_LOG "is eating"
# define THINK_LOG "is thinking"
# define SLEEP_LOG "is sleeping"
# define DIE_LOG "died"
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define CLR_RESET   "\x1b[0m"

#include <stdio.h>//

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
	int			id;
	int			fork_count;
	int			*lft_fork;
	int			*rght_fork;
	int			first;
	int			last;
	int			status;
	int			lst_meal;
	int			lft_id;
	int			rght_id;
	pthread_t	thread;

}				t_philo;

typedef struct s_mtxs
{
	pthread_mutex_t      *forks_mtxs;
	pthread_mutex_t      write_log_mtx;
	pthread_mutex_t      philo_dead_mtx;
}             t_mtxs;

struct s_thrd_info;

typedef struct s_vars
{
	struct s_thrd_info   *infos;
	t_philo              *philos;
	t_mtxs               mtxs;
	int	              nbr_of_philos;
	int	              time_to_die;
	int	              time_to_eat;
	int	              time_to_sleep;
	int	              with_external_param;
	int	              philos_must_eat_times_nbr;
}				t_vars;

typedef struct       s_thrd_info
{
	int	id;
	t_vars *vars;
}	              t_thrd_info;


/*
** Core funcs
*/

int			init_args(t_vars *vars, char **argv);

int			convert_to_int_n_check_min_value(char **argv, \
								int arg_nbr, t_vars *vars);

void		*life_cycle(void *info_void);


/*
** Philo utils
*/

int			ft_get_timestamp_ms(void);

void		sleep_milisecs(int count);

void		ft_put_error(char *str);

void		write_log(t_vars *vars, int type, int id);

/*
** Libft utils
*/

int			ft_atoi(const char *nptr);

void		ft_putchar_fd(char c, int fd);

void		ft_putstr_fd(char *s, int fd);

void		ft_putendl_fd(char *s, int fd);

void		ft_putnbr_fd(int n, int fd);

#endif

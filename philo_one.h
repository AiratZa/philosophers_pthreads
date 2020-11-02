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

#include <stdio.h>//

struct timeval current_time;


int		ft_atoi(const char *nptr);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

char			*ft_itoa(int n);

void		ft_putnbr_fd(int n, int fd);

void	ft_putchar_fd(char c, int fd);

/*



       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

       Compile and link with -pthread.

*/
/*

int usleep(useconds_t usec); 
 
ОПИСАНИЕ
Функция usleep() приостанавливает выполнение процесса на usec микросекунд. Остановка может продлиться несколько больше из-за системной активности или из-за того, что для осуществления вызова требуется определенное время.  
ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ

Функция ничего не возвращает (BSD). Или возвращается 0 при номальном завершении работы и -1 при ошибках (SUSv



int gettimeofday(struct timeval *tv, struct timezone *tz);
*/


#endif

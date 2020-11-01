#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define TAKE_FORK_LOG "has taken a fork"
# define EAT_LOG "is eating"
# define SLEEP_LOG "is sleeping"
# define THINK_LOG "thinking"
# define DIE_LOG "died"
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

#include <stdio.h>//

int			ft_atoi(const char *nptr);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);


/*

int usleep(useconds_t usec); 
 
ОПИСАНИЕ
Функция usleep() приостанавливает выполнение процесса на usec микросекунд. Остановка может продлиться несколько больше из-за системной активности или из-за того, что для осуществления вызова требуется определенное время.  
ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ

Функция ничего не возвращает (BSD). Или возвращается 0 при номальном завершении работы и -1 при ошибках (SUSv



int gettimeofday(struct timeval *tv, struct timezone *tz);
*/


#endif

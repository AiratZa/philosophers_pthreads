#include "philo_one.h"

int	ft_get_timestamp_ms(void)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return ((int)(now.tv_usec * 1000));
}

/*
** usleep makes sleep for microsecs(milllisecs / 1000)
*/

void	sleep_milisecs(int count)
{
	usleep(1000 * count);
}

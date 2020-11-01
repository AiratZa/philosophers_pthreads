#include "philo_one.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||\
			c == '\r' || c == '\f' || c == '\v');
}

int			ft_atoi(const char *nptr)
{
	long	nb;
	long	tmp;
	int		i;
	int		minus;

	nb = 0;
	i = 0;
	minus = 0;
	while (ft_isspace((int)nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		minus = 1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		tmp = nb;
		nb = nb * 10 + (nptr[i++] - '0');
		if (nb < tmp)
			return ((minus) ? 0 : -1);
	}
	return ((minus) ? (int)(-nb) : (int)(nb));
}

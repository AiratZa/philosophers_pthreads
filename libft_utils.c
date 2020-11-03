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

static size_t	ft_d_count(int n)
{
	size_t		d_count;

	d_count = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		d_count++;
		n /= 10;
	}
	return (d_count);
}

static char		*min_int_handler(int n)
{
	size_t	i;
	char	*nbr;

	i = 10;
	nbr = (char *)malloc(12 * sizeof(char));
	if (nbr == NULL)
		return (NULL);
	nbr[11] = '\0';
	n++;
	n *= -1;
	nbr[0] = '-';
	while (i > 0)
	{
		nbr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	nbr[10] = '8';
	return (nbr);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

void		ft_putnbr_fd(int n, int fd)
{
	char	nbr[10];
	int		i;

	i = 0;
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			n = (n % 1000000000);
		}
		n *= -1;
	}
	while (n != 0)
	{
		nbr[i] = ((n % 10) + '0');
		n = n / 10;
		i++;
	}
	while (--i >= 0)
		ft_putchar_fd(nbr[i], fd);
}

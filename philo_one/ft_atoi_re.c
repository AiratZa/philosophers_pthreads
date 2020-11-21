/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_re.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:15:07 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/21 17:05:30 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||\
			c == '\r' || c == '\f' || c == '\v');
}

int	check_last_char_n_return(char last_char, int minus, long nb)
{
	if (last_char != '\0')
		return (-1);
	return ((minus) ? (int)(-nb) : (int)(nb));
}

int	ft_atoi_re(const char *nptr)
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
	return (check_last_char_n_return(nptr[i], minus, nb));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_re.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:59:28 by gdrake            #+#    #+#             */
/*   Updated: 2020/11/22 17:07:07 by gdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

char			*ft_itoa_re(int n)
{
	char	*nbr;
	size_t	d_count;

	d_count = ft_d_count(n);
	nbr = (char *)malloc((d_count + 1) * sizeof(char));
	if (nbr == NULL)
		return (NULL);
	nbr[d_count] = '\0';
	while (d_count > 0)
	{
		nbr[(d_count--) - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (nbr);
}

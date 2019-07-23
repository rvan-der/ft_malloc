/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 18:55:07 by rvan-der          #+#    #+#             */
/*   Updated: 2018/10/05 15:42:24 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		find_range(intmax_t n)
{
	int			range;

	range = (n <= 0 ? 1 : 0);
	n = (n < 0 ? -n : n);
	while (n != 0)
	{
		range++;
		n = n / 10;
	}
	return (range);
}

char			*ft_itoa(int n)
{
	int			i;
	int			range;
	intmax_t	nbr;
	char		*str;

	nbr = (intmax_t)n;
	range = find_range(nbr);
	if ((str = (char*)malloc(sizeof(char) * (range + 1))) == NULL)
		return (NULL);
	i = range - 1;
	if (nbr <= 0)
		str[0] = (n < 0 ? '-' : '0');
	nbr = (nbr < 0 ? -nbr : nbr);
	while (nbr != 0)
	{
		str[i--] = '0' + (nbr % 10);
		nbr = nbr / 10;
	}
	str[range] = '\0';
	return (str);
}

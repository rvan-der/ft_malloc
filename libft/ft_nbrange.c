/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrange.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:50:50 by rvan-der          #+#    #+#             */
/*   Updated: 2018/10/30 17:41:39 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_nbrange(long nb, int base)
{
	int		res;

	if (base < 0)
		base = -base;
	res = (!nb ? 1 : 0);
	if (nb == LONG_MIN)
		nb++;
	if (nb < 0)
		nb = -nb;
	while (nb)
	{
		res++;
		nb /= base;
	}
	return (res);
}

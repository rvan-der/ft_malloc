/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:10:43 by rvan-der          #+#    #+#             */
/*   Updated: 2018/10/10 16:29:14 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double			ft_power(long double n, int power)
{
	long double		res;
	int				p;

	res = 1;
	p = (power < 0 ? -power : power) + 1;
	while (--p)
		res *= n;
	return (power < 0 ? 1 / res : res);
}

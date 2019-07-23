/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:15:59 by rvan-der          #+#    #+#             */
/*   Updated: 2018/10/05 14:18:48 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long			ft_strtol(const char *restrict str, char **restrict endptr, \
							int base)
{
	intmax_t	result;

	errno = 0;
	result = ft_strtoimax(str, endptr, base);
	if (errno == EINVAL)
		return (0);
	if (result > LONG_MAX || (errno == ERANGE && result == LONG_MAX))
		return ((long)LONG_MAX);
	if (result < LONG_MIN || (errno == ERANGE && result == LONG_MIN))
		return ((long)LONG_MIN);
	return ((long)result);
}

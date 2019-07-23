/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:36:26 by rvan-der          #+#    #+#             */
/*   Updated: 2018/10/05 14:18:52 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long		ft_strtoll(const char *restrict str, char **restrict endptr, \
							int base)
{
	intmax_t	result;

	errno = 0;
	result = ft_strtoimax(str, endptr, base);
	if (errno == EINVAL)
		return (0);
	if (result > LLONG_MAX || (errno == ERANGE && result == LLONG_MAX))
		return ((long long)LLONG_MAX);
	if (result < LLONG_MIN || (errno == ERANGE && result == LLONG_MIN))
		return ((long long)LLONG_MIN);
	return ((long long)result);
}

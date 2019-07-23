/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:33:46 by rvan-der          #+#    #+#             */
/*   Updated: 2018/10/04 18:12:25 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		*ft_strnchr(const char *s, int c, int n)
{
	int			i;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i] && i < n)
		if (s[i] == (char)c)
			return ((char*)s + i);
	if (!c && !s[i])
		return ((char*)s + i);
	return (NULL);
}

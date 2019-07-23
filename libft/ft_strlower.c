/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 17:36:22 by rvan-der          #+#    #+#             */
/*   Updated: 2018/10/04 18:11:53 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strlower(const char *str)
{
	char	*ret;
	int		i;

	if (!str || !(ret = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		if (str[i] > 64 && str[i] < 91)
			ret[i] += 32;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

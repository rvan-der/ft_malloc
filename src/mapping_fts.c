/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_fts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:50:46 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 13:39:55 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	g_data;

void				*claim_mem(size_t size)
{
	void			*ret;

	ret = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ret == MAP_FAILED)
		return (NULL);
	return (ret);
}

size_t				correct_size(size_t size, size_t chunk)
{
	if (!(size % chunk))
		return (size);
	return ((size / chunk + 1) * chunk);
}	

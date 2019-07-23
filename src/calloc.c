/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:45:59 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 18:39:38 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	*g_data;

void					*calloc(size_t count, size_t size)
{
	void				*ret;

	size = (size ? size : 1);
	if (!count || !(ret = malloc(size * count)))
		return (NULL);
	if (size * count <= MAX_LENGTH * g_data->t_tab.chunk_sz)
		size = correct_size(size * count, g_data->t_tab.chunk_sz);
	else if (size * count <= MAX_LENGTH * g_data->s_tab.chunk_sz)
		size = correct_size(size * count, g_data->s_tab.chunk_sz);
	else
		size = correct_size(size * count, (size_t)(g_data->page_sz));
	ft_bzero(ret, size);
	return (ret);
}
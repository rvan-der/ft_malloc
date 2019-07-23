/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_tab_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:15:33 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 13:39:43 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	*g_data;

int						grow_pool_tab(t_pool_tab *ptab)
{
	void				*newtab;
	size_t				newsize;

	newsize = correct_size(ptab->len * ptab->data_sz * 2,\
							(size_t)(g_data->page_sz));
	if (!(newtab = claim_mem(newsize)))
		return (0);
	ft_memcpy(newtab, ptab->tab, ptab->len * ptab->data_sz);
	munmap(ptab->tab, ptab->size);
	ptab->tab = newtab;
	ptab->size = newsize;
	ptab->len = newsize / ptab->data_sz;
	return (1);
}

int						shrink_pool_tab(t_pool_tab *ptab)
{
	void				*newtab;
	size_t				newsize;
	int					i;
	int					counter;

	newsize = correct_size(ptab->count * ptab->data_sz,\
							(size_t)(g_data->page_sz));
	if (newsize == ptab->size)
		return (1);
	if (!(newtab = claim_mem(newsize)))
		return (0);
	i = -1;
	counter = -1;
	while ((size_t)(++i) < ptab->len)
		if (POOLMEM(ptab->tab + i * ptab->data_sz))
			ft_memcpy(newtab + (++counter) * ptab->data_sz, \
						ptab->tab + i * ptab->data_sz, ptab->data_sz);
	munmap(ptab->tab, ptab->size);
	ptab->tab = newtab;
	ptab->size = newsize;
	ptab->len = newsize / ptab->data_sz;
	return (1);
}

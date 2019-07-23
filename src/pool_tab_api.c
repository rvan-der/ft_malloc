/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_tab_api.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:54:07 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 13:39:47 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	*g_data;

int						init_pool_tab(t_pool_tab *ptab, size_t len)
{
	size_t				size;

	len = (len ? len : 1);
	size = correct_size(len * ptab->data_sz, (size_t)(g_data->page_sz));
	if (!(ptab->tab = claim_mem(size)))
	{
		ptab->len = 0;
		return (0);
	}
	ptab->size = size;
	ptab->len = size / ptab->data_sz;
	ptab->count = 0;
	ft_bzero(ptab->tab, size);
	return (1);
}

void					clear_pool_tab(t_pool_tab *ptab)
{
	int					i;

	if (!ptab->tab)
		return ;
	if (ptab->count)
	{
		i = -1;
		while ((size_t)(++i) < ptab->len)
			if (POOLMEM(ptab->tab + i * ptab->data_sz))
				delete_pool(ptab, ptab->tab + i * ptab->data_sz);
	}
	munmap(ptab->tab, ptab->size);
	ptab->tab = NULL;
	ptab->size = 0;
	ptab->len = 0;
	ptab->count = 0;
}

void					*new_pool(t_pool_tab *ptab, size_t l_mem)
{
	void				*new;
	int					i;

	if (!ptab->tab)
		return (NULL);
	new = ptab->tab;
	i = -1;
	while ((size_t)(++i) < ptab->len && POOLMEM(new))
		new += ptab->data_sz;
	if ((size_t)i == ptab->len || !(POOLMEM(new) = \
		claim_mem(ptab->cat == large ? l_mem : ptab->mem_sz)))
		return (NULL);
	if (ptab->cat != large)
	{
		((t_tspool*)new)->len = ptab->mem_sz / ptab->chunk_sz;
		((t_tspool*)new)->largest = MAX_LENGTH;
		((t_tspool*)new)->chunks[0] = (unsigned char)(START + MAX_LENGTH);
	}
	ptab->count += 1;
	return (new);
}

void					delete_pool(t_pool_tab *ptab, void *pool)
{
	if (!ptab->tab || !pool)
		return ;
	munmap(POOLMEM(pool), \
		(ptab->cat == large ? ((t_lpool*)pool)->size : ptab->mem_sz));
	ft_bzero(pool, ptab->data_sz);
	ptab->count -= 1;
}

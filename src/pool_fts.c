/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:44:00 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 13:39:51 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	*g_data;

int						find_ptr_index(t_pool_tab *ptab, t_tspool *pool,\
										void *ptr)
{
	t_tspool			*tspool;

	if (ptab->cat == large)
		return (0);
	tspool = (t_tspool*)pool;
	if ((size_t)(ptr - tspool->memory) % ptab->chunk_sz)
		return (-1);
	return ((size_t)(ptr - tspool->memory) / ptab->chunk_sz);
}

void					*find_pool(void *ptr, t_pool_tab **ptab)
{
	int					i;
	int					j;
	void				*pool;

	i = -1;
	while (++i < 2 && (*ptab = (void*)g_data + i * sizeof(t_pool_tab)))
	{
		j = -1;
		while ((*ptab)->tab && (size_t)(++j) < (*ptab)->len)
		{
			pool = (*ptab)->tab + j * (*ptab)->data_sz;
			if (POOLMEM(pool) && POOLMEM(pool) <= ptr && \
				ptr < POOLMEM(pool) + (*ptab)->mem_sz)
				return (pool);
		}
	}
	*ptab = &(g_data->l_tab);
	i = -1;
	while ((*ptab)->tab && (size_t)(++i) < (*ptab)->len)
		if (POOLMEM((*ptab)->tab + i * (*ptab)->data_sz) == ptr)
			return ((*ptab)->tab + i * (*ptab)->data_sz);
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:57:43 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 19:10:24 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	*g_data;

void					delete_data(void)
{
	if (!g_data)
		return;
	if (g_data->t_tab.tab)
		clear_pool_tab(&(g_data->t_tab));
	if (g_data->s_tab.tab)
		clear_pool_tab(&(g_data->s_tab));
	if (g_data->l_tab.tab)
		clear_pool_tab(&(g_data->l_tab));
	munmap(g_data, g_data->page_sz);
	g_data = NULL;
}

int						free_tiny_small(t_tspool *pool, int index)
{
	int					len;
	int					i;

	if (!(pool->chunks[index] & START) || !(pool->chunks[index] & OCP))
		return (0);
	len = pool->chunks[index] & LENGTH;
	i = -1;
	while (++i < len)
		pool->chunks[index + i] = 0;
	pool->count -= len;
	if (!(pool->chunks[index + len] & OCP))
		pool->chunks[index + len] = 0;
	while (index > 0 && !(pool->chunks[index - 1] & OCP) && ++len)
		index--;
	while (len < MAX_LENGTH && (size_t)(index + len) < pool->len \
			&& !(pool->chunks[index + len] & OCP))
		len++;
	len = (len > MAX_LENGTH ? MAX_LENGTH : len);
	pool->chunks[index] = START + len;
	pool->largest = (pool->largest < (unsigned int)len ? (unsigned int)len :\
					pool->largest);
	return (1);
}

void					free(void *ptr)
{
	t_pool_tab			*ptab;
	void				*pool;
	int					index;

	malloc_data_unlock();
	ptab = NULL;
	write(1, " free: 0x", 9);
	ft_putnbr_base((int)ptr, "0123456789ABCDEF");
	if (!ptr)
		return ;
	if (!g_data || !(pool = find_pool(ptr, &ptab)))
	{
		write(1, "abort1", 6);
		malloc_abort(EINVAL, "free");
	}
	if (ptab->cat != large && ((index = find_ptr_index(ptab, (t_tspool*)pool,\
			ptr)) < 0 || !free_tiny_small((t_tspool*)pool, index)))
	{
		write(1, "abort2", 6);
		malloc_abort(EINVAL, "free");
	}
	if (ptab->cat == large || !((t_tspool*)pool)->count)
	{
		delete_pool(ptab, pool);
		if (!ptab->count)
			clear_pool_tab(ptab);
		else if (ptab->len > 1 && ptab->count <= ptab->len / 2)
			shrink_pool_tab(ptab);
	}
	if (!g_data->t_tab.tab && !g_data->s_tab.tab && !g_data->l_tab.tab)
		delete_data();
	malloc_data_lock();
}

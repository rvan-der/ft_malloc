/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_ts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:56:25 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 14:49:23 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	*g_data;

t_tspool				*select_pool(size_t len, t_pool_tab *ptab)
{
	void				*ret;
	size_t				i;

	if (!ptab->tab && !init_pool_tab(ptab, 1))
		return (NULL);
	i = 0;
	while (i < ptab->len && (ret = ptab->tab + i * ptab->data_sz) && \
			!(POOLMEM(ret) && ((t_tspool*)ret)->largest >= len))
		i++;
	if (i < ptab->len)
		return ((t_tspool*)ret);
	if (ptab->count == ptab->len && !grow_pool_tab(ptab))
		return (NULL);
	return ((t_tspool*)new_pool(ptab, 0));
}

int						find_space(size_t len, t_tspool *pool)
{
	size_t				i;

	i = 0;
	while (i <= pool->len - len)
	{
		if (pool->chunks[i] & START)
		{
			if (!(pool->chunks[i] & OCP) && (pool->chunks[i] & LENGTH) >= len)
				return ((int)i);
			i += pool->chunks[i] & LENGTH;
		}
		else
			i++;
	}
	return (-1);
}

void					update_largest(t_tspool *pool)
{
	int					i;

	pool->largest = 0;
	i = 0;
	while ((size_t)i < pool->len && pool->largest < MAX_LENGTH)
	{
		if (pool->chunks[i] & START)
		{
			if (!(pool->chunks[i] & OCP) && 
					(pool->chunks[i] & LENGTH) > pool->largest)
				pool->largest = pool->chunks[i] & LENGTH;
			i += pool->chunks[i] & LENGTH;
		}
		else
			i++;
	}
}

void					set_chunks(size_t len, t_tspool* pool, size_t index)
{
	size_t				i;

	pool->chunks[index] = START + OCP + len;
	i = 0;
	while (++i < len)
		pool->chunks[index + i] = OCP;
	if (index + len < pool->len && !(pool->chunks[index + len] & OCP))
	{
		i = 1;
		while (index + len + i < pool->len && i < MAX_LENGTH\
				&& !(pool->chunks[index + len + i] & OCP))
			i++;
		pool->chunks[index + len] = START + i;
	}
	pool->count += len;
}

void					*alloc_ts(size_t size, t_pool_tab *ptab)
{
	t_tspool			*pool;
	int					index;

	if (!(pool = select_pool(size / ptab->chunk_sz, ptab)))
	{
		errno = ENOMEM;
		return (NULL);
	}
	if ((index = find_space(size / ptab->chunk_sz, pool)) < 0)
	{
		errno = ENOMEM;
		return (NULL);
	}
	set_chunks(size / ptab->chunk_sz, pool, (size_t)index);
	update_largest(pool);
	return (pool->memory + index * ptab->chunk_sz);
}
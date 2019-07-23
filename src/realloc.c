/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:14:21 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 13:39:26 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	*g_data;

void					*redo_alloc(size_t alloc_size, size_t new_size,\
									void *ptr)
{
	void				*ret;
	int					i;

	if (!(ret = malloc(new_size)))
		return (NULL);
	i = -1;
	while ((size_t)(++i) < alloc_size && (size_t)i < new_size)
		((unsigned char*)ret)[i] = ((unsigned char*)ptr)[i];
	free(ptr);
	return (ret);
}

int						expand_alloc(t_tspool *pool, int index, int new_len)
{
	int					free_len;
	int					alloc_len;
	int					i;

	alloc_len = pool->chunks[index] & LENGTH;
	if ((size_t)index + new_len > pool->len ||\
			pool->chunks[index + alloc_len] & OCP ||\
			(pool->chunks[index + alloc_len] & LENGTH) < new_len - alloc_len)
		return (0);
	pool->chunks[index] = (OCP | START) + new_len;
	i = alloc_len - 1;
	while (++i < new_len)
		pool->chunks[index + i] = OCP;
	free_len = 0;
	while (free_len < MAX_LENGTH && (size_t)index + new_len + free_len <\
			pool->len && !(pool->chunks[index + new_len + free_len] & OCP))
		free_len++;
	if (free_len)
		pool->chunks[index + new_len] = START + free_len;
	return (1);
}

void					shrink_alloc(t_tspool *pool, int index, int new_len)
{
	int					free_len;
	int					alloc_len;
	int					i;

	alloc_len = pool->chunks[index] & LENGTH;
	free_len = 0;
	if ((size_t)index + alloc_len < pool->len &&\
			!(pool->chunks[index + alloc_len] & OCP))
		free_len = pool->chunks[index + alloc_len] & LENGTH;
	pool->chunks[index] = (OCP | START) + new_len;
	i = new_len;
	while (++i < alloc_len)
		pool->chunks[index + i] = 0;
	free_len += alloc_len - new_len;
	if (free_len > MAX_LENGTH)
		free_len = MAX_LENGTH;
	pool->chunks[index + new_len] = START + free_len;
	pool->chunks[index + alloc_len] = 0;
}

int						resize_alloc(t_pool_tab *ptab, t_tspool *pool,\
										int index, size_t size)
{
	size = correct_size(size, ptab->chunk_sz);
	if ((ptab->cat == tiny && size > MAX_LENGTH * g_data->t_tab.chunk_sz) ||\
			(ptab->cat == small && (size <= MAX_LENGTH * g_data->t_tab.chunk_sz\
			|| size > MAX_LENGTH * g_data->s_tab.chunk_sz)))
		return (0);
	if (size / ptab->chunk_sz < (pool->chunks[index] & LENGTH))
		shrink_alloc(pool, index, size / ptab->chunk_sz);
	else if (!expand_alloc(pool, index, size / ptab->chunk_sz))
		return (0);
	return (1);
}

void					*realloc(void *ptr, size_t size)
{
	t_pool_tab			*ptab;
	void				*pool;
	void				*ret;
	size_t				alloc_size;
	int					index;

	if (!(ret = ptr))
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (malloc(size));
	}
	malloc_data_unlock();
	if (!g_data || !(pool = find_pool(ptr, &ptab)))
		return (malloc_abort(EINVAL, "realloc"));
	if ((index = find_ptr_index(ptab, pool, ptr)) < 0)
		return (malloc_abort(EINVAL, "realloc"));
	alloc_size = (ptab->cat != large ? (((t_tspool*)pool)->chunks[index] &\
				LENGTH) * ptab->chunk_sz : ((t_lpool*)pool)->size);
	if (ptab->cat == large || !resize_alloc(ptab, (t_tspool*)pool, index, size))
		ret = redo_alloc(alloc_size, size, ptr);
	malloc_data_lock();
	return (ret);
}
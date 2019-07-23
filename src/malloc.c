/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 18:22:49 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 19:01:14 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

t_malloc_data		*g_data = NULL;

void				*malloc_abort(int error, char *fct_name)
{
	char			*sterr;

	delete_data();
	sterr = strerror(error);
	write(2, fct_name, ft_strlen(fct_name));
	write(2, ": ", 2);
	write(2, sterr, ft_strlen(sterr));
	write(2, "\n", 1);
	abort();
	return (NULL);
}

void				*alloc_l(size_t size)
{
	void			*pool;

	if ((!g_data->l_tab.tab && !init_pool_tab(&(g_data->l_tab), 1)) || \
			(g_data->l_tab.count == g_data->l_tab.len && \
			!grow_pool_tab(&(g_data->l_tab))))
		return (NULL);
	if (!(pool = new_pool(&(g_data->l_tab), size)))
		return (NULL);
	((t_lpool*)(pool))->size = size;
	return (POOLMEM(pool));
}

int					init_data(size_t pagesize)
{
	if (!(g_data = (t_malloc_data*)claim_mem(pagesize)))
		return (0);
	ft_bzero((void*)g_data, correct_size(sizeof(t_malloc_data),\
											(size_t)pagesize));
	g_data->page_sz = pagesize;
	g_data->t_tab.cat = tiny;
	g_data->t_tab.chunk_sz = pagesize / 256;
	g_data->t_tab.mem_sz = correct_size(100 * MAX_LENGTH * \
							g_data->t_tab.chunk_sz, (size_t)pagesize);
	g_data->t_tab.data_sz = sizeof(t_tspool) + \
							g_data->t_tab.mem_sz / g_data->t_tab.chunk_sz;
	g_data->s_tab.cat = small;
	g_data->s_tab.chunk_sz = pagesize / 32;
	g_data->s_tab.mem_sz = correct_size(100 * MAX_LENGTH * \
							g_data->s_tab.chunk_sz, (size_t)pagesize);
	g_data->s_tab.data_sz = sizeof(t_tspool) + \
							g_data->s_tab.mem_sz / g_data->s_tab.chunk_sz;
	g_data->l_tab.cat = large;
	g_data->l_tab.chunk_sz = pagesize;
	g_data->l_tab.data_sz = sizeof(t_lpool);
	return (1);
}

void				*malloc(size_t size)
{
	void			*ret;

	malloc_data_unlock();
	write(1, "plop", 4);
	if (!g_data && !init_data(getpagesize()))
	{
		errno = ENOMEM;
		return (NULL);
	}
	size = (size ? size : 1);
	if (size <= MAX_LENGTH * g_data->t_tab.chunk_sz)
		ret = alloc_ts(correct_size(size, g_data->t_tab.chunk_sz), \
				&(g_data->t_tab));
	else if (size <= MAX_LENGTH * g_data->s_tab.chunk_sz)
		ret = alloc_ts(correct_size(size, g_data->s_tab.chunk_sz), \
				&(g_data->s_tab));
	else
		ret = alloc_l(correct_size(size, (size_t)(g_data->page_sz)));
	write(1, "0x", 2);
	ft_putnbr_base((int)ret, "0123456789ABCDEF");
	malloc_data_lock();
	return (ret);
}

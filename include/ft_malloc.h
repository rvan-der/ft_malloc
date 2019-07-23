/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 19:18:53 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 18:49:41 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MALLOC_H_
# define _MALLOC_H_

# include <libft.h>
# include <sys/types.h>
# include <sys/mman.h>

# define OCP 0x80
# define START 0x40
# define LENGTH 0x3f
# define MAX_LENGTH 32

# define POOLMEM(ptr) (*((void**)(ptr)))
# define CHUNK(pool, i) (((t_tspool*)(pool))->chunks[i])

typedef enum			e_category
{
	tiny,
	small,
	large
}						t_category;

typedef struct			s_pool_tab
{
	void				*tab;
	size_t				size;
	size_t				len;
	size_t				count;
	size_t				chunk_sz;
	size_t				mem_sz;
	size_t				data_sz;
	t_category			cat;
}						t_pool_tab;

typedef struct 			s_tspool
{
	void				*memory;
	size_t				len;
	unsigned int		count;
	unsigned int		largest;
	unsigned char		chunks[];
}						t_tspool;

/*
** Note:
** 'len' and 'largest' in t_tspool are in number of chunks
** For clarification on the usage of chunk array as flexible
** array member, go to:
** https://en.wikipedia.org/wiki/Flexible_array_member
*/

typedef struct			s_lpool
{
	void				*memory;
	size_t				size;
}						t_lpool;

typedef struct 			s_malloc_data
{
	t_pool_tab			t_tab;
	t_pool_tab			s_tab;
	t_pool_tab			l_tab;
	int					page_sz;
}						t_malloc_data;

void		hexdump(void *addr, int len);

/*
** malloc.c
*/
void					*malloc(size_t size);
void					*malloc_abort(int error, char *fct_name);
int						init_data(size_t pagesize);

/*
** free.c
*/
void					free(void *ptr);
void					delete_data(void);

/*
** realloc.c
*/
void					*realloc(void *ptr, size_t size);

/*
** alloc_ts.c
*/
void					*alloc_ts(size_t size, t_pool_tab *ptab);

/*
** mapping_fts.c
*/
void					*claim_mem(size_t size);
size_t					correct_size(size_t size, size_t chunk);

/*
** pool_fts.c
*/
int						find_ptr_index(t_pool_tab *ptab, t_tspool *pool,\
										void *ptr);
void					*find_pool(void *ptr, t_pool_tab **ptab);

/*
** pool_tab_api.c
*/
int						init_pool_tab(t_pool_tab *ptab, size_t len);
void					clear_pool_tab(t_pool_tab *ptab);
void					*new_pool(t_pool_tab *ptab, size_t l_mem);
void					delete_pool(t_pool_tab *ptab, void *pool);

/*
** pool_tab_operations.c
*/
int						grow_pool_tab(t_pool_tab *ptab);
int						shrink_pool_tab(t_pool_tab * ptab);

/*
** data_lock.c
*/
void					malloc_data_lock(void);
void					malloc_data_unlock(void);

/*
** calloc.c
*/
void					*calloc(size_t count, size_t size);

#endif

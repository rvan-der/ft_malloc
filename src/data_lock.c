/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_lock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:05:28 by rvan-der          #+#    #+#             */
/*   Updated: 2019/07/23 13:39:34 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

extern t_malloc_data	*g_data;

void					malloc_data_lock(void)
{
	if (!g_data)
		return ;
	mprotect(g_data, g_data->page_sz, PROT_READ);
}

void					malloc_data_unlock(void)
{
	if (!g_data)
		return ;
	mprotect(g_data, g_data->page_sz, PROT_READ | PROT_WRITE | PROT_EXEC);
}
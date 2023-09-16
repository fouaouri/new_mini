/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_curr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:18:14 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/16 23:40:28 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_alloc	*head(void)
{
	static t_alloc	alloc;

	if (alloc.ptr == NULL)
	{
		alloc.len = 10;
		alloc.ptr = malloc(alloc.len * sizeof(uintptr_t));
	}
	return (&alloc);
}

int	get_pos(void)
{
	t_alloc	*alloc;
	int		pos;

	pos = 0;
	alloc = head();
	while (pos < alloc->pos)
	{
		if (alloc->ptr[pos] == 0)
			break ;
		pos++;
	}
	return (pos);
}

void	*my_malloc(size_t size)
{
	t_alloc			*alloc;
	void			*new;
	uintptr_t		*ptr;
	int				pos;

	new = malloc(size);
	new = ft_memset(new, 0, size);
	pos = get_pos();
	alloc = head();
	alloc->ptr[pos] = (uintptr_t) new;
	if (pos == alloc->pos)
		alloc->pos++;
	if (alloc->pos + 2 >= alloc->len)
	{
		ptr = malloc(alloc->len * 2 * sizeof(uintptr_t));
		ft_memcpy(ptr, alloc->ptr, alloc->len * sizeof(uintptr_t));
		free(alloc->ptr);
		alloc->ptr = ptr;
		alloc->len *= 2;
	}
	return (new);
}

void	my_free_all(void)
{
	t_alloc	*curr;
	int		i;

	curr = head();
	i = 0;
	while (i < curr->pos)
	{
		free((void *)curr->ptr[i]);
		curr->ptr[i] = 0;
		i++;
	}
}

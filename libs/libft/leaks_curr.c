/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_curr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:18:14 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/11 18:53:20 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_alloc	*head(void)
{
	static t_alloc	curr;

	if (curr.ptr == NULL)
	{
		curr.len = 10;
		curr.ptr = malloc(curr.len * sizeof(long));
	}
	return (&curr);
}

int	get_pos(void)
{
	t_alloc	*curr;
	int		pos;

	pos = 0;
	curr = head();
	while (pos < curr->pos)
	{
		if (curr->ptr[pos] == 0)
			break ;
		pos++;
	}
	return (pos);
}

void	*my_malloc(size_t size)
{
	t_alloc		*curr;
	void		*new;
	long		*ptr;
	int			pos;

	new = malloc(size);
	new = ft_memset(new, 0, size);
	pos = get_pos();
	curr = head();
	curr->ptr[pos] = (long) new;
	if (pos == curr->pos)
		curr->pos++;
	if (curr->pos + 2 >= curr->len)
	{
		ptr = malloc(curr->len * 2 * sizeof(long));
		ft_memcpy(ptr, curr->ptr, curr->len * sizeof(long));
		free(curr->ptr);
		curr->ptr = ptr;
		curr->len *= 2;
	}
	return (new);
}

// void	my_free_all(void)
// {
// 	t_alloc	*curr;
// 	int		i;

// 	curr = head();
// 	i = 0;
// 	while (i < curr->pos)
// 	{
// 		free((void *)curr->ptr[i]);
// 		curr->ptr[i] = 0;
// 		i++;
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:05:42 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/13 19:56:12 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*t_mem;

	t_mem = NULL;
	if (size && nmemb >= SIZE_MAX / size)
		return (NULL);
	t_mem = my_malloc(size * nmemb);
	if (t_mem == NULL)
		return (t_mem);
	ft_bzero(t_mem, (size * nmemb));
	return (t_mem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:40:57 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/07 22:25:18 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(s);
	ret = malloc(len + 1);
	if (!ret)
		return (ret);
	if (ret)
	{
		while (*s)
		{
			*ret = *s;
			ret++;
			s++;
		}
		*ret = '\0';
	}
	return (ret - len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:44:29 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/07 22:25:36 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;

	ret = NULL;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	s_len = ft_strlen(s + start);
	if (!s)
		return (ft_strdup(""));
	else if (len <= s_len)
		s_len = len;
	ret = malloc(s_len + 1);
	if (!ret)
		return (ret);
	ft_strlcpy(ret, (s + start), s_len + 1);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:32:36 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/03 14:55:18 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_substr(char *s, int start, int len)
// {
// 	int				i;
// 	char			*sus;
// 	unsigned char	*str;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	if (start >= ft_strlen(s))
// 		return (ft_strdup("\0"));
// 	if (len > ft_strlen(s) - start)
// 		len = ft_strlen(s) - start;
// 	str = (unsigned char *)s;
// 	sus = (char *)malloc(len +1);
// 	if (!sus)
// 		return (NULL);
// 	while (i < len && str[i])
// 	{
// 		sus[i++] = str[start++];
// 	}
// 	sus[i] = '\0';
// 	return (sus);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	i = 0;
// 	str1 = (unsigned char *)s1;
// 	str2 = (unsigned char *)s2;
// 	while ((str1[i] || str2[i]) && i < n)
// 	{
// 		if (str1[i] != str2[i])
// 			return (str1[i] - str2[i]);
// 		i++;
// 	}
// 	return (0);
// }

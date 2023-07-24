/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:24:44 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/24 01:37:59 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		l;
	char	*lorst;

	if (!s2)
		return (NULL);
	i = 0;
	j = 0;
	l = ft_strlen(s1) + ft_strlen(s2);
	lorst = malloc(l + 1);
	if (!lorst)
		return (NULL);
	while (s1 && s1[i])
	{
		lorst[i] = s1[i];
		i++;
	}
	while (s2[j])
		lorst[i++] = s2[j++];
	lorst[i] = '\0';
	return ( lorst);
}

char	*ft_strjoin_char(char *s1, char c)
{
	int		i;
	// int		j;
	int		l;
	char	*lorst;

	if (!c)
		return (NULL);
	i = 0;
	// j = 0;
	l = ft_strlen(s1) + 1;
	lorst = malloc(l + 1);
	if (!lorst)
		return (NULL);
	while (s1 && s1[i])
	{
		lorst[i] = s1[i];
		i++;
	}
	lorst[i] = c;
	lorst[i + 1] = '\0';
	return (free(s1), lorst);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = (char *)malloc((ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	while (i < (ft_strlen(s1)))
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	ft_bzero(void *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)(s + i)) = 0;
		i++;
	}
}

void	*ft_calloc(int count, int size)
{
	int	*p;

	p = 0;
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero (p, count * size);
	return (p);
}

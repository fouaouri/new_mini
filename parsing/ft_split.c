/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:07:26 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/06 22:21:23 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_counter(char *s, char sep)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == sep && s[i])
			i++;
		if (s[i] != sep && s[i] != '\0')
		{
			counter++;
		}
		while (s[i] != sep && s[i])
			i++;
	}
	return (counter);
}

static int	ft_len_world(char *s, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == sep)
		i++;
	while (s[i] != sep && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

static char	*ft_str_allocation(char *s, char sep)
{
	int		i;
	int		j;
	int		len;
	char	*word;

	i = 0;
	j = 0;
	len = ft_len_world(s, sep);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (s[i] == sep)
		i++;
	while (s[i] && s[i] != sep)
	{
		word[j] = s[i];
		j++;
		i++;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_free(char **spliter)
{
	int	i;

	i = 0;
	while (spliter[i])
	{
		free(spliter[i]);
		i++;
	}
	free (spliter);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**spliter;

	if (!s)
		return (NULL);
	spliter = malloc(sizeof(char *) * (ft_counter((char *)s, c) + 1));
	if (!spliter)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			spliter[j] = ft_str_allocation((char *)(s), c);
			if (!spliter[j++])
				return (ft_free(spliter));
		}
		while (*s != c && *s)
			s++;
	}
	spliter[j] = 0;
	return (spliter);
}

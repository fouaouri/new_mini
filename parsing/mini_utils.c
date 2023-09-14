/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:24:44 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/14 16:17:20 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char *s1, char c)
{
	int		i;
	int		l;
	char	*lorst;

	if (!c)
		return (NULL);
	i = 0;
	l = ft_strlen(s1) + 1;
	lorst = my_malloc(l + 1);
	if (!lorst)
		return (NULL);
	while (s1 && s1[i])
	{
		lorst[i] = s1[i];
		i++;
	}
	lorst[i] = c;
	lorst[i + 1] = '\0';
	return (lorst);
}

int	index_pipe(t_read *readline)
{
	int	i;

	i = 0;
	while (readline->arr1[i])
	{
		if (ft_strcmp(readline->arr1[i], ">") == 0
			&& ft_strcmp(readline->arr1[i + 1], "|") == 0)
			return (-1);
		else if (ft_strcmp(readline->arr1[i], "|") == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	null_function(t_file *sep, t_variables *var)
{
	sep->file_name[var->j] = NULL;
	sep->type[var->j] = NULL;
	sep->commandes[var->k] = NULL;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	find_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

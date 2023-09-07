/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:24:44 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/07 17:28:22 by fouaouri         ###   ########.fr       */
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

int	index_pipe(t_read *readline)
{
	int	i;

	i = 0;
	while (readline->arr1[i])
	{
		if (ft_strcmp(readline->arr1[i], "|") == 0)
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

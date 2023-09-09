/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:31:57 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/07 17:36:19 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_clean(char *str, char *str1, int i, int k)
{
	i++;
	while (str[i] != '\'')
	{
		str1[k++] = str[i];
		i++;
	}
	i++;
}

void	help_clean_1(char *str, char *str1, int i, int k)
{
	i++;
	while (str[i] != '\"')
	{
		str1[k++] = str[i];
		i++;
	}
	i++;
}

int	count_s_quotes(t_read *readline)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (readline->input[i])
	{
		if (readline->input[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	count_dquotes(t_read *readline)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (readline->input[i])
	{
		if (readline->input[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	redi_check(char *str)
{
	if ((ft_strcmp(str, "<") == 0
			|| ft_strcmp(str, ">") == 0
			|| ft_strcmp(str, "<<") == 0
			|| ft_strcmp(str, ">>") == 0))
		return (1);
	return (0);
}

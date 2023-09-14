/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:39:51 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/14 19:53:32 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == str[i + 1])
			i++;
		else
		{
			counter++;
			i++;
		}
	}
	return (counter);
}

int	counter_sep(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] && str[i] != '3')
	{
		if (str[i] != '0')
			i++;
		else
		{
			while (str[i] == '0')
				i++;
			counter++;
		}
	}
	return (counter);
}

int	count_words(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] != '0')
		{
			counter++;
		}
		i++;
	}
	return (counter);
}

int	count_files(t_read *readline)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (readline->arr1[i] && ft_strcmp(readline->arr1[i], "|") != 0)
	{
		if (ft_strcmp(readline->arr1[i], "<\0") == 0
			|| ft_strcmp(readline->arr1[i], ">\0") == 0
			|| ft_strcmp(readline->arr1[i], "<<\0") == 0
			|| ft_strcmp(readline->arr1[i], ">>\0") == 0)
			count++;
		i++;
	}
	return (count);
}

int	count_commande(t_read *readline)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (readline->arr1[i] && ft_strcmp(readline->arr1[i], "|") != 0)
	{
		if (ft_strlen(readline->input) == 1)
		{
			count += 1;
			break ;
		}
		else if (readline->arr1[i + 1]
			&& (ft_strcmp(readline->arr1[i], "<") == 0
				|| ft_strcmp(readline->arr1[i], ">") == 0
				|| ft_strcmp(readline->arr1[i], "<<\0") == 0
				|| ft_strcmp(readline->arr1[i], ">>\0") == 0))
			i += 2;
		else
		{
			count += 1;
			i += 1;
		}
	}
	return (count);
}

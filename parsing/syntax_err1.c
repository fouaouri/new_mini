/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:09:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/09 22:28:57 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redi(t_read *readline)
{
	int	i;

	i = 0;
	while (readline->input[i] == '<')
		i++;
	if (i > 2)
		return (-1);
	i = 0;
	while (readline->input[i] == '>')
		i++;
	if (i > 2)
		return (-1);
	i = 0;
	while (readline->input[i] == '&')
		i++;
	if (i > 1)
		return (-1);
	return (0);
}

int	check_ands(t_read *readline)
{
	int	i;
	int	len1;

	len1 = ft_strlen(readline->input);
	if (readline->input[len1] == '&' || readline->input[0] == '&')
	{
		return (-1);
		return (-1);
	}
	if (len1 >= 0)
	{
		i = 0;
		while (readline->input[i] && readline->input[i] == '&')
			i++;
		if (i > 1)
			return (-1);
		i = 0;
		while (readline->input[i] && readline->input[len1] == '&')
			i++;
		if (i > 2)
			return (-1);
	}
	return (0);
}

int	check_d_quotes(t_read *readline)
{
	int	i;
	int	count;
	int	count1;

	i = 0;
	count = 0;
	count1 = 0;
	while (readline->input[i])
	{
		if (readline->input[i] == '\"' || readline->input[i] == '\'')
			count += 1;
		i++;
	}
	i = 0;
	while (readline->input[i])
	{
		if (readline->input[i] == '\'')
			count1 += 1;
		i++;
	}
	if (count % 2 != 0 || count1 % 2 != 0)
		return (-1);
	return (0);
}

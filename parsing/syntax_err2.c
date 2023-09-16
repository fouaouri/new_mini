/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:09:27 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/16 21:13:03 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_redi(t_read *readline)
{
	int	i;

	i = 0;
	while (readline->input[i] && readline->input[i + 1])
	{
		if (readline->input[i] == '>' && readline->input[i + 1] == '<')
		{
			return (-1);
			break ;
		}
		else
			i++;
	}
	return (0);
}

int	while_redi1(t_read *readline)
{
	int	i;

	i = 0;
	while (readline->input[i] && readline->input[i + 1])
	{
		if (readline->input[i] == '>' && readline->input[i + 1] == ' '
			&& readline->input[i + 2] == '>')
		{
			return (-1);
			break ;
		}
		else if (readline->input[i] == '<' && readline->input[i + 1] == ' '
			&& readline->input[i + 2] == '<')
		{
			return (-1);
			break ;
		}
		else
			i++;
	}
	return (0);
}

int	check_redirections(t_read *readline)
{
	int	len;

	len = ft_strlen(readline->input) - 1;
	if (len < 0)
		len = 0;
	if ((readline->input && readline->input[len] == '<')
		|| readline->input[len] == '>')
		return (-1);
	len = while_redi1(readline);
	len = while_redi(readline);
	if (len == -1)
		return (-1);
	return (0);
}

int	check_last_char(char c)
{
	int	err;

	err = 0;
	if (c == '|')
		err = -1;
	else if (c == '&')
		err = -1;
	else if (c == '(' || c == ')')
		err = -1;
	return (err);
}

int	there_is_quotes(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				return (1);
			i++;
		}	
	}
	return (0);
}

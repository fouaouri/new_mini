/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:09:27 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/10 18:42:55 by fouaouri         ###   ########.fr       */
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

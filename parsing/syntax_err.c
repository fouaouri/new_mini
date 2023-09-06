/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:41:10 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/05 18:57:37 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syn(t_read *readline, int i)
{
	if ((readline->input[i] == '>' && readline->input[i + 1] == ' '
			&& readline->input[i + 2] == '|') || (readline->input[i] == '<'
			&& readline->input[i + 1] == '|') || (readline->input[i] == '<'
			&& readline->input[i + 1] == ' '
			&& readline->input[i + 2] == '|'))
		return (1);
	return (0);
}

int	norm_syn(t_read *readline, t_variables *var)
{
	int	err;

	err = 0;
	if (readline->string[var->i++] == '\'')
	{
		while (readline->string[var->i] != '\'')
			var->i++;
	}
	else if (readline->string[var->i++] == '\"')
	{
		while (readline->string[var->i] != '\"')
			var->i++;
	}
	else if (readline->input[var->i] == '|' && readline->input[var->i + 1] == ' ' && readline->input[var->i + 2] == '|')
	{
		// while (readline->string[var->i] == '|')
		// {
			
		// 	var->count++;
		// 	var->i++;
		// }
		// if (var->count > 2)
		err = errors(readline);
	}
	// else if (readline->input[var->i]
	// 	&& check_syn(readline, var->i) == 1)
	// 	err = errors(readline);
	if (err == -1)
		return (-1);
	return (0);
}
// ft_strlen(readline->input) > 1 &&
int	while_pipes(t_read *readline)
{
	t_variables	var;
	int			len;

	var.i = 0;
	len = ft_strlen(readline->string);
	while (var.i < len)
	{
		if (norm_syn(readline, &var) == -1)
			return (-1);
		var.i++;
	}
	return (0);
}

int	check_pipes(t_read *readline)
{
	int	len;
	int	err;

	err = 0;
	len = counter_arr(readline->put_zero) - 1;
	if (len < 0)
		len = 0;
	if (ft_strcmp(readline->arr[0], "|") == 0)
		err = errors(readline);
	else if (ft_strcmp(readline->arr[len], "|") == 0)
		err = errors(readline);
	else if (ft_strcmp(readline->arr[0], "&") == 0)
		err = errors(readline);
	else if (ft_strcmp(readline->arr[0], ")") == 0)
		err = errors(readline);
	err = while_pipes(readline);
	if (err == -1)
		return (-1);
	return (0);
}

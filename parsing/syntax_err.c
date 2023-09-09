/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:41:10 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/07 17:35:44 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_syn(t_read *readline, t_variables *var)
{
	if (var->i <= (int)ft_strlen(readline->string)
		&& readline->string[var->i] != '\0')
	{
		if (readline->string[var->i] == '\'')
		{
			var->i++;
			while (readline->string[var->i] != '\0'
				&& readline->string[var->i] != '\'')
				var->i++;
		}
		else if (readline->string[var->i] == '\"')
		{
			var->i++;
			while (readline->string[var->i] != '\0'
				&& readline->string[var->i] != '\"')
				var->i++;
		}
	}
}

int	pipe_err(t_read *readline, t_variables *var)
{
	if ((readline->input[var->i] == '|' && readline->input[var->i + 1] == ' '
			&& readline->input[var->i + 2] == '|')
		|| (readline->input[var->i] == '|'
			&& readline->input[var->i + 1] == '|'))
		return (-1);
	return (0);
}

int	pipe_err1(t_read *readline, t_variables *var)
{
	if ((readline->input[var->i] == '>' && readline->input[var->i + 1] == ' '
			&& readline->input[var->i + 2] == '|')
		|| (readline->input[var->i] == '<'
			&& readline->input[var->i + 1] == '|')
		|| (readline->input[var->i] == '<'
			&& readline->input[var->i + 1] == ' '
			&& readline->input[var->i + 2] == '|'))
		return (-1);
	return (0);
}

int	while_pipes(t_read *readline)
{
	t_variables	var;

	var.i = 0;
	var.len = ft_strlen(readline->input);
	while (var.i < var.len)
	{
		if (pipe_err(readline, &var) == -1)
			return (-1);
		if (pipe_err1(readline, &var) == -1)
			return (-1);
		norm_syn(readline, &var);
		var.i++;
	}
	return (0);
}

int	check_pipes(t_read *readline)
{
	int	len;
	int	sep;
	int	err;

	err = 0;
	sep = 0;
	len = counter_arr(readline->put_zero) - 1;
	sep = while_pipes(readline);
	if (len < 0)
		len = 0;
	if (ft_strcmp(readline->arr[0], "|") == 0)
		err = -1;
	else if (ft_strcmp(readline->arr[len], "|") == 0)
		err = -1;
	else if (ft_strcmp(readline->arr[0], "&") == 0)
		err = -1;
	else if (ft_strcmp(readline->arr[0], ")") == 0)
		err = -1;
	if (err == -1 || sep == -1)
	{
		errors();
		return (-1);
	}
	return (0);
}

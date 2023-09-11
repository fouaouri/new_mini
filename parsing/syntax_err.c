/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:41:10 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/11 18:12:23 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_syn(t_read *readline, t_variables *var)
{
	if (var->i <= (int)ft_strlen(readline->input)
		&& readline->input[var->i] != '\0')
	{
		if (readline->input[var->i] == '\'')
		{
			var->i++;
			while (readline->input[var->i] != '\0'
				&& readline->input[var->i] != '\'')
				var->i++;
		}
		else if (readline->input[var->i] == '\"')
		{
			var->i++;
			while (readline->input[var->i] != '\0'
				&& readline->input[var->i] != '\"')
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
			&& readline->input[var->i + 2] == '|')
		|| (readline->input[var->i] == '>' && readline->input[var->i + 1] == '>'
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
	int	sep;
	int	err;
	int	i;

	err = 0;
	i = 0;
	sep = while_pipes(readline);
	while (readline->input[i] && (readline->input[i] == ' '
			|| readline->input[i] == '\t'))
		i++;
	if (check_last_char(readline->input[i]) == -1)
		err = -1;
	i = 0;
	while (readline->input[i])
		i++;
	i -= 1;
	while (i > 0 && (readline->input[i] == ' '
			|| readline->input[i] == '\t'))
		i--;
	if (check_last_char(readline->input[i]) == -1)
		err = -1;
	if (err == -1 || sep == -1)
		return (-1);
	return (0);
}

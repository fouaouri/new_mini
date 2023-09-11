/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:09:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/10 23:47:47 by fouaouri         ###   ########.fr       */
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

void	var_d(t_read *readline, t_variables *var)
{
	var->dc = 1;
	var->i += 1;
	while (readline->input[var->i] && readline->input[var->i] != '\"')
		var->i++;
	if (readline->input[var->i] == '\"')
		var->dc = 0;
}

void	var_s(t_read *readline, t_variables *var)
{
	var->sc = 1;
	var->i += 1;
	while (readline->input[var->i] && readline->input[var->i] != '\'')
		var->i++;
	if (readline->input[var->i] == '\'')
		var->sc = 0;
}

int	check_d_quotes(t_read *readline, t_variables var)
{
	var.i = 0;
	var.len = ft_strlen(readline->input);
	var.dc = 0;
	var.sc = 0;
	while (var.i < var.len)
	{
		if (readline->input[var.i] == '\"')
			var_d(readline, &var);
		else if (readline->input[var.i] == '\'')
			var_s(readline, &var);
		var.i++;
	}
	if (var.sc == 1 || var.dc == 1)
		return (-1);
	return (0);
}

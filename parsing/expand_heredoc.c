/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:44:30 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/16 22:56:51 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_single(t_read *readline, t_variables *var)
{
	var->k = 0;
	while (readline->input[var->i]
		&& readline->input[var->i] != '$')
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i++]);
}

void	else_single(t_read *readline, t_variables *var)
{
	if (readline->input[var->i - 1] == '$' && readline->input[var->i] == '+')
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i - 1]);
	else if (readline->input[var->i - 1] == '$'
		&& readline->input[var->i] == '?')
	{
		var->exit0 = ft_itoa(g_data.exit_status);
		readline->exp = ft_strjoin(readline->exp, var->exit0);
		var->i += 1;
		while (readline->input[var->i] && readline->input[var->i] != '\''
			&& check_special_char(readline->input[var->i]) == 1)
			readline->exp = ft_strjoin_char(readline->exp,
					readline->input[var->i++]);
	}
	var->k = 1;
}

void	while_single(t_read *readline, t_variables *var)
{
	while (readline->input[var->i]
		&& check_special_char(readline->input[var->i]) == 0)
	{
		var->count = 0;
		if (readline->input[var->i] != '$')
			readline->exp = ft_strjoin_char(readline->exp,
					readline->input[var->i++]);
		else
		{
			while (readline->input[var->i] == '$')
			{
				var->count++;
				var->i++;
			}
			if (var->count % 2 == 0)
				if_single(readline, var);
			else
				else_single(readline, var);
		}
	}
}

void	expand_single(t_read *readline, t_variables *var, t_env *l_env)
{
	if (var->s_d == 0)
		var->s_d = 1;
	else if (var->s_d == 1)
		var->s_d = 0;
	if (readline->input[var->i] && readline->input[var->i] == '\'')
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i++]);
	if (readline->input[var->i] != '\'')
	{
		while_single(readline, var);
		if (readline->input[var->i - 1] == '$')
		{
			skip_f_numbre(readline->input[var->i], &var);
			while (readline->input[var->i]
				&& check_special_char(readline->input[var->i]) == 1
				&& readline->input[var->i] != '\'')
			{
				readline->new_input = ft_strjoin_char(readline->new_input,
						readline->input[var->i++]);
			}
		}
		multi_instru(readline, &var, l_env);
		if_if_exp(readline, var);
	}
}

void	expand_heredoc(t_read *readline, t_env *l_env)
{
	t_variables	var;

	init_expand(readline, &var);
	while (readline->input && readline->input[var.i])
	{
		if (readline->input && readline->input[var.i] == '<'
			&& readline->input[var.i + 1] == '<')
			var.e = 1;
		var.i++;
	}
	var.i = 0;
	if (readline->input[var.i])
	{
		while (readline->input[var.i])
		{
			if (readline->input[var.i] == '\'' && var.s_d == 0)
				expand_single(readline, &var, l_env);
			else if (readline->input[var.i] == '\"'
				&& var.s_c == 0 && var.e == 0)
				expand_d_c(readline, &var, l_env);
			else
				else_expand(readline, &var, l_env);
		}
	}
}

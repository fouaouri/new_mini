/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:40:33 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/07 16:53:05 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_char(char c)
{
	if (c == '`' || c == '.' || c == '$' || c == '-' || c == '+' || c == '/'
		|| c == '*' || c == '\\' || c == '?' || c == '!' || c == '>'
		|| c == '<' || c == ',' || c == '=' || c == '+' || c == ')'
		|| c == '(' || c == '&' || c == '^' || c == '%' || c == '#'
		|| c == '\t' || c == ' ' || c == ':' || c == '\'' || c == '$')
		return (0);
	return (1);
}

void	else_expand_2(t_read *readline, t_variables *var)
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
		while (readline->input[var->i] && readline->input[var->i] != '\"'
			&& check_special_char(readline->input[var->i]) == 1)
			readline->exp = ft_strjoin_char(readline->exp,
					readline->input[var->i++]);
	}
	var->k = 1;
}

void	if_else_expand(t_read *readline, t_variables *var, t_env *l_env)
{
	while (readline->input[var->i] == '$')
	{
		var->count++;
		var->i++;
	}
	if (((var->count % 2) == 0))
	{
		var->k = 0;
		while (readline->input[var->i] && readline->input[var->i] != '$')
			readline->exp = ft_strjoin_char(readline->exp,
					readline->input[var->i++]);
	}
	else
		else_expand_2(readline, var);
	while (readline->input[var->i] && readline->input[var->i] != '\"'
		&& check_special_char(readline->input[var->i]) == 1)
		readline->new_input = ft_strjoin_char(readline->new_input,
				readline->input[var->i++]);
	if (var->k == 1)
		call_env(readline, readline->new_input, l_env, var);
	readline->new_input = calloc(1, 1);
}

void	else_expand(t_read *readline, t_variables *var, t_env *l_env)
{
	var->count = 0;
	if (readline->input[var->i] == '$')
		if_else_expand(readline, var, l_env);
	else
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i++]);
}

void	expand_s_c(t_read *readline, t_variables *var)
{
	if (var->s_c == 0)
		var->s_c = 1;
	else if (var->s_c == 1)
		var->s_c = 0;
	var->count = 0;
	if (readline->input[var->i] && readline->input[var->i] == '\'')
	{
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i++]);
		var->count += 1;
	}
	if (var->s_c == 1)
		while (readline->input[var->i] && readline->input[var->i] != '\'')
			readline->exp = ft_strjoin_char(readline->exp,
					readline->input[var->i++]);
}

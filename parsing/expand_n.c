/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:42:08 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/07 17:07:24 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_env(t_read *readline, char *str, t_env *l_env, t_variables *var)
{
	initial_env(var);
	var->len = ft_strlen(str) + 1;
	var->e = 0;
	while (l_env->next != NULL)
	{
		if (ft_strcmp(l_env->key, str) == 0)
		{
			while (l_env->value[var->e])
				readline->exp = ft_strjoin_char(readline->exp,
						l_env->value[var->e++]);
			var->k = 1;
		}
		l_env = l_env->next;
	}
}

void	else_d_c(t_read *readline, t_variables *var)
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

void	while_d_c(t_read *readline, t_variables *var)
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
				if_if_exp_2(readline, var);
			else
				else_d_c(readline, var);
		}
	}
}

void	expand_d_c(t_read *readline, t_variables *var, t_env *l_env)
{
	if (var->s_d == 0)
		var->s_d = 1;
	else if (var->s_d == 1)
		var->s_d = 0;
	if (readline->input[var->i] && readline->input[var->i] == '\"')
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i++]);
	if (readline->input[var->i] != '\'')
	{
		while_d_c(readline, var);
		if (readline->input[var->i - 1] == '$')
			while (readline->input[var->i]
				&& check_special_char(readline->input[var->i]) == 1
				&& readline->input[var->i] != '\"')
				readline->new_input = ft_strjoin_char(readline->new_input,
						readline->input[var->i++]);
		if (var->k == 1)
			call_env(readline, readline->new_input, l_env, var);
		else if (var->k == 0)
			readline->exp = ft_strjoin(readline->exp, readline->new_input);
		if_if_exp(readline, var);
	}
}

void	expand_arr(t_read *readline, t_env *l_env)
{
	t_variables	var;

	var.i = 0;
	var.count = 0;
	var.k = 0;
	var.e = 0;
	var.s_d = 0;
	var.s_c = 0;
	readline->exp = calloc(1, 1);
	readline->new_input = calloc(1, 1);
	while (readline->input[var.i])
	{
		if (readline->input[var.i] == '\'' && var.s_d == 0)
			expand_s_c(readline, &var);
		else if (readline->input[var.i] == '\"' && var.s_c == 0)
			expand_d_c(readline, &var, l_env);
		else
			else_expand(readline, &var, l_env);
	}
	free (readline->new_input);
}

// echo 'ssss'"$USER"

// echo " <|> '"''

// echo "'$USER'"

// echo ""'"$USER"'

// echo $+ //(*)

// echo $USER?

// 'l'"s"
// echo "$USER'"

// echo "$USER $PWD"

// echo "$USER-*/"'+.,;#?<|>:"

// echo ''""
// """'$USER $HOME'"""$USER'$USER' //(*)
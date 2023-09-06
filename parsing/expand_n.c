/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:42:08 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/03 21:50:59 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_env(t_read *readline, char *str, char **env, t_variables *var)
{
	initial_env(var);
	while (str[var->count] && check_special_char(str[var->count]) == 1)
	{
		if (str[var->count] != '\"')
			var->str1 = ft_strjoin_char(var->str1, str[var->count]);
		var->count++;
		var->j++;
	}
	var->len = ft_strlen(var->str1) + 1;
	var->str1 = ft_strjoin(var->str1, "=");
	while (env[var->e])
	{
		if (ft_strncmp(env[var->e], var->str1, var->len) == 0)
		{
			while (env[var->e][var->len])
				readline->exp = ft_strjoin_char(readline->exp,
						env[var->e][var->len++]);
			var->k = 1;
		}
		var->e++;
	}
	var->len = ft_strlen(str) + 1;
	if (var->k == 1)
		while (var->j < var->len - 1)
			readline->exp = ft_strjoin_char(readline->exp, str[var->j++]);
}

void	else_d_c(t_read *readline, t_variables *var)
{
	if (readline->input[var->i - 1] == '$' && readline->input[var->i] == '+')
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i - 1]);
	else if (readline->input[var->i - 1] == '$'
		&& readline->input[var->i] == '?')
	{
		var->exit0 = ft_itoa(readline->exit_status);
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

void	expand_d_c(t_read *readline, t_variables *var, char **env)
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
			call_env(readline, readline->new_input, env, var);
		else if (var->k == 0)
			readline->exp = ft_strjoin(readline->exp, readline->new_input);
		if_if_exp(readline, var);
	}
}

void	expand_arr(t_read *readline, char **env)
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
			expand_d_c(readline, &var, env);
		else
			else_expand(readline, &var, env);
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
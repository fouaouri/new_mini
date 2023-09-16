/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:16:57 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/16 21:16:56 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_if_exp(t_read *readline, t_variables *var)
{
	if (check_special_char(readline->input[var->i]) == 0
		&& readline->input[var->i] != '$'
		&& readline->input[var->i] == '\"')
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i++]);
	readline->new_input = ft_calloc(1, 1);
}

void	if_if_exp_2(t_read *readline, t_variables *var)
{
	var->k = 0;
	while (readline->input[var->i]
		&& readline->input[var->i] != '$')
		readline->exp = ft_strjoin_char(readline->exp,
				readline->input[var->i++]);
}

void	initial_env(t_variables *var)
{
	var->str1 = ft_calloc(1, 1);
	var->j = 0;
	var->count = 0;
}

void	init_expand(t_read *readline, t_variables *var)
{
	var->i = 0;
	var->count = 0;
	var->k = 0;
	var->e = 0;
	var->s_d = 0;
	var->s_c = 0;
	readline->exp = ft_calloc(1, 1);
	readline->new_input = ft_calloc(1, 1);
}

void	skip_f_numbre(char c, t_variables **var)
{
	if (c >= '0' && c <= '9' && (*var)->k == 1)
	{
		(*var)->i += 1;
		(*var)->k = 0;
	}
}

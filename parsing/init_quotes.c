/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:18:06 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/09 21:21:00 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quote(t_read *readline, t_variables *var)
{
	var->i = 0;
	var->j = 0;
	var->len = ft_strlen(readline->replace);
	readline->string = my_malloc(count_words(readline->replace) + 1);
}

void	ft_clean_s(char *str, t_variables *var)
{
	if (check_special_char1(str) == 1)
	{
		var->str1[var->k++] = str[var->i++];
		while (str[var->i] != '\'')
			var->str1[var->k++] = str[var->i++];
		var->str1 = ft_strjoin_char(var->str1, str[var->i++]);
		var->k += 1;
	}
	else
	{
		var->i++;
		while (str[var->i] != '\'')
			var->str1[var->k++] = str[var->i++];
	}
}

void	ft_clean_d(char *str, t_variables *var)
{
	if (check_special_char1(str) == 1)
	{
		var->str1[var->k++] = str[var->i++];
		while (str[var->i] != '\"')
			var->str1[var->k++] = str[var->i++];
		var->str1 = ft_strjoin_char(var->str1, str[var->i++]);
		var->k += 1;
	}
	else
	{
		var->i++;
		while (str[var->i] != '\"')
			var->str1[var->k++] = str[var->i++];
	}
}

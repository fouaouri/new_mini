/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:27:15 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/06 22:22:14 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sep_replace(t_read *readline, t_variables *var)
{
	if (readline->exp[var->i] == '\'')
	{
		readline->replace[var->i] = '1';
		var->i += 1;
		while (readline->exp[var->i] != '\'')
		{
			readline->replace[var->i] = '1';
			var->i++;
		}
		readline->replace[var->i] = '1';
	}
	else if (readline->exp[var->i] == '\"')
	{
		readline->replace[var->i] = '1';
		var->i += 1;
		while (readline->exp[var->i] != '\"')
		{
			readline->replace[var->i] = '1';
			var->i++;
		}
		readline->replace[var->i] = '1';
	}
}

void	replace_char(t_read *readline)
{
	t_variables	var;

	var.i = 0;
	readline->replace = malloc(ft_strlen(readline->exp) + 1);
	while (readline->exp[var.i])
	{
		if (readline->exp[var.i] == '\"' || readline->exp[var.i] == '\'')
			sep_replace(readline, &var);
		else if (readline->exp[var.i] == '>')
			readline->replace[var.i] = '2';
		else if (readline->exp[var.i] == '<')
			readline->replace[var.i] = '5';
		else if (readline->exp[var.i] == '|')
			readline->replace[var.i] = '3';
		else if (readline->exp[var.i] == ' ' || readline->exp[var.i] == '\t')
			readline->replace[var.i] = '0';
		else
			readline->replace[var.i] = '1';
		var.i++;
	}
	readline->replace[var.i] = '\0';
}

void	skip_spaces_in_the_input(t_read *readline)
{
	t_variables	var;

	var.i = 0;
	var.j = 0;
	var.len = ft_strlen(readline->replace);
	readline->string = malloc(count_words(readline->replace) + 1);
	while (var.i < var.len)
	{
		if (readline->exp[var.i] != ' ' && readline->exp[var.i] != '\t')
		{
			if (readline->exp[var.i] == 34 || readline->exp[var.i] == 39)
			{
				readline->string[var.j++] = readline->exp[var.i++];
				while (readline->exp[var.i] != 34
					&& readline->exp[var.i] != 39)
					readline->string[var.j++] = readline->exp[var.i++];
			}
			readline->string[var.j] = readline->exp[var.i];
			var.j++;
		}
		var.i++;
	}
	readline->string[var.j] = '\0';
}

void	sep_by_spaces(t_read *readline)
{
	t_variables	var;

	var.i = 0;
	var.j = 0;
	var.len = ft_strlen(readline->replace);
	var.count = counter(readline->replace);
	readline->put_zero = malloc(sizeof(char) * (var.len + var.count + 1));
	while (var.i < var.len)
	{
		if (readline->replace[var.i] != readline->replace[var.i + 1])
		{
			readline->put_zero[var.j] = readline->replace[var.i];
			var.j++;
			readline->put_zero[var.j] = '0';
			var.j++;
		}
		else
		{
			readline->put_zero[var.j] = readline->replace[var.i];
			var.j++;
		}
		var.i++;
	}
	readline->put_zero[var.j] = '\0';
}

void	add_spaces_in_the_input(t_read *readline)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(readline->put_zero) + 1;
	readline->add_spaces = malloc(len);
	if (!readline->add_spaces)
		return ;
	while (readline->put_zero[i])
	{
		if (readline->put_zero[i] != '0')
			readline->add_spaces[j++] = readline->string[k++];
		else
			readline->add_spaces[j++] = ' ';
		i++;
	}
	readline->add_spaces[j] = '\0';
}

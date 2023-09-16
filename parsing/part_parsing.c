/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:24:24 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/16 21:13:16 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_d_quotes(t_read *readline)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (readline->input[i])
	{
		if (readline->input[i] == '\"' || readline->input[i] == '\'')
			count += 1;
		i++;
	}
	return (count);
}

int	count_exp(t_read *readline)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (readline->exp[i])
	{
		count += 1;
		if (readline->exp[i] == ' ')
			count += 1;
		i++;
	}
	return (count);
}

void	clean_d_quotes(t_read *readline)
{
	int	i;
	int	len;

	i = 0;
	len = counter_arr(readline->put_zero);
	readline->arr1 = my_malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (ft_strcmp(readline->arr[i], "<<") == 0
			&& there_is_quotes(readline->arr[i + 1]) == 1)
			g_data.heredoc = 1;
		readline->arr1[i] = ft_clean_d_quotes(readline->arr[i]);
		i++;
	}
	readline->arr1[i] = NULL;
}

int	counter_arr(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] != '0')
			i++;
		else
		{
			while (str[i] == '0')
				i++;
			counter++;
		}
	}
	return (counter);
}

void	fill_the_arr(t_read *readline)
{
	t_variables	var;

	var.i = 0;
	var.j = 0;
	var.k = 0;
	var.count = 0;
	var.len = counter_arr(readline->put_zero) + 1;
	readline->arr = my_malloc(sizeof(char *) * var.len);
	while (readline->put_zero[var.j])
	{
		if (readline->put_zero[var.j] != '0')
		{
			var.k = var.j;
			var.count = 0;
			while (readline->put_zero[var.k++] != '0')
				var.count++;
			readline->arr[var.i++] = ft_substr(readline->add_spaces,
					var.j, var.count);
			var.j += var.count;
		}
		else
			var.j++;
	}
	readline->arr[var.i] = NULL;
}

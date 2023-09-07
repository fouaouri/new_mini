/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:25:10 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/07 22:29:23 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_count(char *str, int i, int count, int len)
{
	while (i < len)
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				count++;
				i++;
			}
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				count++;
				i++;
			}
		}
		else
			count++;
		i++;
	}
	return (count);
}

int	ft_count_d_quotes(char *str)
{
	int	i;
	int	count;
	int	len;
	int	count1;

	i = 0;
	count = 0;
	if (str)
		len = ft_strlen(str);
	count1 = help_count(str, i, count, len);
	return (count1);
}

void	data_clean(char *str, t_variables *var)
{
	var->i = 0;
	var->alloc = ft_count_d_quotes(str);
	var->k = 0;
	var->str1 = my_malloc(var->alloc + 1);
	if (str)
	{
		var->len = ft_strlen(str);
		
	}
}

char	*ft_clean_d_quotes(char *str)
{
	t_variables	var;

	data_clean(str, &var);
	if (str)
	{
		while (var.i < var.len)
		{
			if (str[var.i] == '\'')
			{
				var.i++;
				while (str[var.i] != '\'')
					var.str1[var.k++] = str[var.i++];
			}
			else if (str[var.i] == '\"')
			{
				var.i++;
				while (str[var.i++] != '\"')
					var.str1[var.k++] = str[var.i++];
			}
			else
				var.str1[var.k++] = str[var.i];
			var.i++;
		}
		var.str1[var.k] = 0;
		return (var.str1);
	}
	return (NULL);
}

int	errors(void)
{
	write(2, "Minishell: syntax error near unexpected token\n", 46);
	g_data.exit_status = 258;
	return (-1);
}

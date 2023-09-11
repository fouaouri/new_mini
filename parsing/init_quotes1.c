/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quotes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:31 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/11 18:15:24 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_d_quotes1(char *str)
{
	int	i;
	int	count;
	int	len;
	int	count1;

	i = 0;
	count = 0;
	if (str)
		len = ft_strlen(str);
	if (check_special_char1(str) != 1)
		count1 = len;
	else
		count1 = help_count(str, i, count, len);
	return (count1);
}

void	data_clean1(char *str, t_variables *var)
{
	var->i = 0;
	var->alloc = ft_count_d_quotes1(str);
	var->k = 0;
	var->str1 = my_malloc(var->alloc + 1);
	if (str)
		var->len = ft_strlen(str);
}

void	ft_clean_s1(char *str, t_variables *var)
{
	if (check_special_char1(str) == 1)
	{
		var->i++;
		while (str[var->i] != '\'')
			var->str1[var->k++] = str[var->i++];
		var->i++;
	}
	else
	{
		var->str1[var->k++] = str[var->i++];
		while (str[var->i] && str[var->i] != '\'')
			var->str1[var->k++] = str[var->i++];
		if (str[var->i])
			var->str1[var->k++] = str[var->i++];
	}
}

void	ft_clean_d1(char *str, t_variables *var)
{
	if (check_special_char1(str) == 1)
	{
		var->i++;
		while (str[var->i] != '\"')
			var->str1[var->k++] = str[var->i++];
		var->i++;
	}
	else
	{
		var->str1[var->k++] = str[var->i++];
		while (str[var->i] && str[var->i] != '\"')
			var->str1[var->k++] = str[var->i++];
		if (str[var->i])
			var->str1[var->k++] = str[var->i++];
	}
}

char	*ft_clean_d_quotes1(char *str)
{
	t_variables	var;

	data_clean1(str, &var);
	if (str)
	{
		while (var.i < (int)ft_strlen(str))
		{
			if (str[var.i] == '\'')
				ft_clean_s1(str, &var);
			else if (str[var.i] == '\"')
				ft_clean_d1(str, &var);
			else if (str[var.i])
				var.str1[var.k++] = str[var.i++];
		}
		var.str1[var.k] = '\0';
		return (var.str1);
	}
	return (NULL);
}

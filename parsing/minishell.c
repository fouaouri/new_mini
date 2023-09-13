/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/13 19:56:12 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_error(t_read *readline)
{
	t_variables	var;

	if (check_redirections(readline) == -1 || check_pipes(readline) == -1)
	{
		errors();
		return (-1);
	}
	if (check_redi(readline) == -1 || check_ands(readline) == -1)
	{
		errors();
		return (-1);
	}
	if (check_d_quotes(readline, var) == -1)
	{
		errors();
		return (-1);
	}
	return (0);
}

void	print_minishell(t_read *readln)
{
	readln->input = readline("\033[0;32mMinishell $> \033[0m");
	if (ft_strcmp(readln->input, "\0") != 0)
		add_history(readln->input);
	if (readln->input == NULL)
		exit(0);
}

void	if_export_clean(t_read *readline)
{
	int	i;
	int	len;

	if (ft_strcmp(readline->arr[0], "export") != 0)
		clean_d_quotes(readline);
	else
	{
		i = 0;
		len = counter_arr(readline->put_zero);
		readline->arr1 = my_malloc(sizeof(char *) * (len + 1));
		while (i < len)
		{
			readline->arr1[i] = ft_strdup(readline->arr[i]);
			i++;
		}
		readline->arr1[i] = NULL;
	}
}

t_list	**parsing(t_read *readline, t_env *l_env)
{
	t_file	*sep;
	int		sepe;

	sep = my_malloc(sizeof(t_file));
	print_minishell(readline);
	if (ft_strcmp(readline->input, "\0") != 0)
	{
		expand_arr(readline, l_env);
		sepe = check_syntax_error(readline);
		if (sepe != -1)
		{
			replace_char(readline);
			skip_spaces_in_the_input(readline);
			sep_by_spaces(readline);
			add_spaces_in_the_input(readline);
			fill_the_arr(readline);
			if_export_clean(readline);
			return (sep_files(readline, sep));
		}	
	}
	return (NULL);
}

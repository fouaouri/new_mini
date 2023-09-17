/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/17 23:40:05 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

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
	readln->input = readline("Minishell $> ");
	if (ft_strcmp(readln->input, "\0") != 0)
		add_history(readln->input);
	if (readln->input == NULL)
		exit(0);
}

void	ft_parsing(t_read *readline)
{
	replace_char(readline);
	skip_spaces_in_the_input(readline);
	sep_by_spaces(readline);
	add_spaces_in_the_input(readline);
	fill_the_arr(readline);
	clean_d_quotes(readline);
	free(readline->input);
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
			ft_parsing(readline);
			return (sep_files(readline, sep));
		}
		else
			free(readline->input);
	}
	else if (readline->input)
		free(readline->input);
	return (NULL);
}

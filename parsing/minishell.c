/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/10 18:43:08 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_error(t_read *readline)
{
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
	return (0);
}

void	print_minishell(t_read *readln)
{
	readln->input = readline("\033[0;32mMinishell $> \033[0m");
	add_history(readln->input);
	if (readln->input == NULL)
		exit(0);
}

t_list	**parsing(t_read *readline, t_env *l_env)
{
	t_file	*sep;
	int		sepe;

	sep = my_malloc(sizeof(t_file));
	print_minishell(readline);
	expand_arr(readline, l_env);
	sepe = check_syntax_error(readline);
	if (sepe != -1)
	{
		replace_char(readline);
		skip_spaces_in_the_input(readline);
		sep_by_spaces(readline);
		add_spaces_in_the_input(readline);
		fill_the_arr(readline);
		clean_d_quotes(readline);
		return (sep_files(readline, sep));
	}
	return (NULL);
}

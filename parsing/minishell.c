/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/06 15:32:18 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_error(t_read *readline)
{
	if (check_redirections(readline) == -1 || check_pipes(readline) == -1)
		return (-1);
	if (check_redi(readline) == -1 || check_ands(readline) == -1)
		return (-1);
	if (check_parentheses(readline) == -1)
		return (-1);
	return (0);
}

void	print_minishell(t_read *readln)
{
	readln->input = readline("\033[0;32mMinishell $> \033[0m");
	add_history(readln->input);
	if (readln->input == NULL)
		readln->input = ft_calloc(1, 1);
}

t_list	**parsing(t_read *readline, char **env)
{
	t_file	*sep;
	int		sepe;

	readline->exit_status = 0;
	sep = malloc(sizeof(t_file));
	print_minishell(readline);
	expand_arr(readline, env);
	sepe = check_d_quotes(readline);
	if (sepe != -1)
	{
		replace_char(readline);
		skip_spaces_in_the_input(readline);
		sep_by_spaces(readline);
		add_spaces_in_the_input(readline);
		fill_the_arr(readline);
		clean_d_quotes(readline);
		// sepe = check_syntax_error(readline);
		free(readline->arr);
		free(readline->string);
		free(readline->replace);
		// if (sepe != -1)
			return (sep_files(readline, sep));
	}
	return (NULL);
}

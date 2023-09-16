/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:29:00 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/16 17:46:05 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sep_fill_commands_files(t_read *readline, t_file *sep)
{
	sep->file_name = my_malloc(sizeof(char *) * (count_files(readline) + 1));
	sep->type = my_malloc(sizeof(char *) * (count_files(readline) + 1));
	sep->commandes = my_malloc(sizeof(char *) * (count_commande(readline) + 1));
	sep->sum = (count_files(readline) * 2) + count_commande(readline);
}

void	init_fill(t_read *readline, t_variables *var,
		t_file *sep, int pipe_index)
{
	var->i = 0;
	var->k = 0;
	var->j = 0;
	sep_fill_commands_files(readline, sep);
	if (pipe_index == -1)
		sep->sum = counter_arr(readline->put_zero);
}

char	*cmd_files(char *str1)
{
	char	*str2;

	if (ft_strcmp(str1, "<") == 0)
		str2 = ft_strdup("i");
	else if (ft_strcmp(str1, ">") == 0)
		str2 = ft_strdup("o");
	else if (ft_strcmp(str1, ">>") == 0)
		str2 = ft_strdup("a");
	else if (ft_strcmp(str1, "<<") == 0)
		str2 = ft_strdup("h");
	return (str2);
}

void	fill_commands_files(t_read *readline, t_file *sep,
	int pipe_index, t_variables	*var)
{
	init_fill(readline, var, sep, pipe_index);
	while (readline->arr1[var->i] && var->i < sep->sum)
	{
		if (redi_check(readline->arr1[var->i]) == 1)
		{
			sep->type[var->j] = cmd_files(readline->arr1[var->i]);
			if (readline->arr1[var->i + 1] != NULL)
			{
				if (ft_strcmp(readline->arr1[var->i + 1], "|") == 0)
					sep->file_name[var->j]
						= ft_strdup(readline->arr1[var->i + 2]);
				else
					sep->file_name[var->j]
						= ft_strdup(readline->arr1[var->i + 1]);
				var->i += 2;
			}
			else
				sep->commandes[var->k++] = ft_strdup(readline->arr1[var->i++]);
			var->j++;
		}
		else
			sep->commandes[var->k++] = ft_strdup(readline->arr1[var->i++]);
	}
	null_function(sep, var);
}

t_list	**sep_files(t_read *readline, t_file *sep)
{
	int			pipe_index;
	t_variables	*var;
	t_list		**node;

	node = my_malloc(sizeof(t_list));
	var = my_malloc(sizeof(t_variables));
	pipe_index = index_pipe(readline);
	fill_commands_files(readline, sep, pipe_index, var);
	*node = ft_lstnew(sep->file_name, sep->commandes, sep->type);
	while (pipe_index >= 0)
	{
		readline->arr1 += pipe_index + 1;
		fill_commands_files(readline, sep, pipe_index, var);
		ft_lst_add_back(node, sep->file_name, sep->commandes, sep->type);
		pipe_index = index_pipe(readline);
	}
	return (free(var), free(sep), node);
}

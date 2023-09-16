/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:00:07 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 00:36:57 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	find_file_type(char **type, char *t)
{
	int	i;
	int	last_index;

	i = 0;
	last_index = ERROR;
	while (type[i])
	{
		if (ft_strcmp(type[i], t) == 0)
			last_index = i;
		i++;
	}
	return (last_index);
}

int	open_append(t_list *node, int i)
{
	int	status;

	status = open(node->file_name[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (status < 0)
	{
		status = access(node->file_name[i], F_OK);
		if (status == -1)
			return (ft_error(FILE_NOT_EXIST, node->file_name[i]));
		else
			return (ft_error(PERSMISSION_DENIED, node->file_name[i]));
	}
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	node->outfile = status;
	return (SUCCESS);
}

int	open_heredoc(t_list *node, int i)
{
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	node->infile = ft_atoi(node->file_name[i]);
	if (node->infile == -1)
		return (-2);
	return (SUCCESS);
}

int	open_outfiles(t_list *node, int i)
{
	int	status;

	if (g_data.if_export && ft_strchr(node->file_name[i], ' '))
	{
		ft_dprintf(2, "minishell: %s: ambiguous redirect\n", node->file_name[i]);
		return (-1);
	}
	if (!node->file_name[i])
	{
		ft_dprintf(2, "minishell: ambiguous redirect\n");
		return (-1);
	}
	status = open(node->file_name[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (status < 0)
	{
		status = access(node->file_name[i], F_OK);
		if (status == -1)
			return (ft_error(FILE_NOT_EXIST, node->file_name[i]));
		else
			return (ft_error(PERSMISSION_DENIED, node->file_name[i]));
	}
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	node->outfile = status;
	return (SUCCESS);
}

int	open_infiles(t_list *node, int i)
{
	int	status;

	status = check_infile_acces(node->file_name[i]);
	if (status < 0)
		return (status);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	node->infile = status;
	return (SUCCESS);
}

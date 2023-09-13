/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:38:48 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/13 18:51:59 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// normed
int	check_infile_acces(char *file)
{
	int	status;

	status = access(file, F_OK);
	if (status == -1)
		return (ft_error(FILE_NOT_EXIST, file));
	else
	{
		status = open(file, O_RDONLY);
		if (status == -1)
			return (ft_error(PERSMISSION_DENIED, file));
		else 
			return (status);
	}
	return (ERROR);
}

int	check_outfile_acces(char *file)
{
	int	status;

	status = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (status == -1)
		return (ft_error(PERSMISSION_DENIED, file));
	else 
		return (status);
}

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
		return (ft_error(FILE_NOT_EXIST, node->file_name[i]));
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

	status = open(node->file_name[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (status < 0)
		return (ft_error(FILE_NOT_EXIST, node->file_name[i]));
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

int	handle_files(t_list *node)
{
	int	i;

	i = -1;
	while (node->type[++i])
	{
		if (!ft_strcmp(node->type[i], "i"))
		{
			if (open_infiles(node, i) < 0)
				return (ERROR);
		}
		else if (!ft_strcmp(node->type[i], "H"))
		{
			if (open_heredoc(node, i) < 0)
				return (ERROR);
		}
		else if (!ft_strcmp(node->type[i], "o"))
		{
			if (open_outfiles(node, i) < 0)
				return (ERROR);
		}
		else if (!ft_strcmp(node->type[i], "a"))
			if (open_append(node, i) < 0)
				return (ERROR);
	}
	return (SUCCESS);
}

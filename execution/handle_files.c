/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:38:48 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/09 22:28:26 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_infile_acces(char *file)
{
	// check file acces
	int status;
	
	status = access(file, F_OK);
	if (status == -1)
	{
		printf("3\n");
		return (ft_error(FILE_NOT_EXIST, file));
	}
	else {
		// premision denied
		status = open(file, O_RDONLY);
		if (status == -1)
		{
		printf("2\n");

			return (ft_error(PERSMISSION_DENIED, file));
		}
		else 
			return (status);
	}
	return (ERROR);
}

int	check_outfile_acces(char *file)
{
	// check file acces
	int status;
	
		// premision denied
	status = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (status == -1)
	{
		printf("1\n");
		return (ft_error(PERSMISSION_DENIED, file));
	}
	else 
		return (status);
}

int find_file_type(char **type, char *t) {
	int i, last_index;

	last_index = ERROR; // Initialize last_index to -1
	i = 0;

	while (type[i]) {
		if (ft_strcmp(type[i], t) == 0)
			last_index = i; // Update last_index to the current index
		i++;
	}
	return last_index;
}

int	handle_files(t_list *node)
{
	int i;
	int status;

	i = 0;
	while (node->type[i])
	{
		// check files and open it;
		if (!ft_strcmp(node->type[i], "i"))
		{
			status = check_infile_acces(node->file_name[i]);
			if (status < 0)
				return (status);
			if (node->infile != STDIN_FILENO)
				close(node->infile);
			node->infile = status;
		}
		else if (!ft_strcmp(node->type[i], "h"))
		{
			if (node->infile != STDIN_FILENO)
				close(node->infile);
			node->infile = ft_atoi(node->file_name[i]);
			if (node->infile == -1)
				return (-2);
		}
		else if (!ft_strcmp(node->type[i], "o"))
		{
			status = open(node->file_name[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (status < 0)
				return (status);
			if (node->outfile != STDOUT_FILENO)
				close(node->outfile);
			node->outfile = status;
		}
		else if (!ft_strcmp(node->type[i], "a"))
		{
			status = open(node->file_name[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (status < 0)
				return (status);
			if (node->outfile != STDOUT_FILENO)
				close(node->outfile);
			node->outfile = status;
		}
		i++;
	}
	return (SUCCESS);
}

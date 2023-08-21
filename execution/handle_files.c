/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:38:48 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/20 21:28:19 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_file_acces(char *file)
{
	// check file acces
	int status;
	
	status = access(file, F_OK);
	if (status == -1)
		return (ft_error(FILE_NOT_EXIST, file));
	else {
		// premision denied
		status = open(file, O_RDONLY);
		if (status == -1)
			return (ft_error(PERSMISSION_DENIED, file));
		else 
			return (status);
	}
	return (ERROR);
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
			status = check_file_acces(node->file_name[i]);
			if (status < 0)
				return (status);
			node->infile = status;
		}
		else if (!ft_strcmp(node->type[i], "h"))
		{
			// status = check_file_acces(node->file_name[i]);
			// if (status < 0)
			// 	return (status);
			node->infile = ft_heredoc(node->file_name[i]);
		}
		else if (!ft_strcmp(node->type[i], "o"))
		{
			status = check_file_acces(node->file_name[i]);
			if (status < 0)
				return (status);
			node->outfile = status;
		}
		else if (!ft_strcmp(node->type[i], "a"))
		{
			status = check_file_acces(node->file_name[i]);
			if (status < 0)
				return (status);
			node->outfile = status;
		}
		i++;
	}
	return (SUCCESS);
}

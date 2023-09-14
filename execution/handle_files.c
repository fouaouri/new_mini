/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:38:48 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/14 18:59:56 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

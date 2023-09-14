/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:47:16 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/14 17:23:47 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	open_pipes(t_list *node, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		ft_dprintf(2, "minishell: pipe: %s\n", strerror(errno));
		g_data.exit_status = 1;
		return (ERROR);
	}
	node->next->infile = pipe_fd[0];
	node->outfile = pipe_fd[1];
	return (SUCCESS);
}

int	execute(t_list *node)
{
	int	pipe_fd[2];
	int	err;

	node->pid = 0;
	if (node->next != NULL)
	{
		if (open_pipes(node, pipe_fd) == ERROR)
			return (ERROR);
	}
	else
		node->outfile = STDOUT_FILENO;
	if (node->type)
	{
		err = handle_files(node);
		if (err < 0)
		{
			g_data.exit_status = 1;
			return (err);
		}
	}
	if (exec_cmd(node) == ERROR)
		return (ERROR);
	close_fd(node->infile, node->outfile);
	return (SUCCESS);
}

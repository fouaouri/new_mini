/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:47:16 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/10 21:40:10 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	 BUG:
	 => I need to close infile for first cmd: like => cat | ls. ls should print then cat
*/
int	execute(t_list *node)
{
	int pipe_fd[2];
	int err;

	// if (node->commandes[0])
	// 	return (ERROR);
	node->pid = 0;
	if (node->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_dprintf(2, "minishell: pipe: %s\n", strerror(errno));
			g_data.exit_status = 1;
			return (ERROR);
    }
		node->next->infile = pipe_fd[0];  // Set next command's input
		node->outfile = pipe_fd[1]; // Set this command to write to pipe;
	}
	else
		node->outfile = STDOUT_FILENO; // Set last command's output to terminal
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

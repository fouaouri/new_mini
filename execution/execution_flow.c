/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:47:16 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/29 12:00:59 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute(t_list *node,char **env)
{
	int pipe_fd[2];

	if (node->next != NULL)
	{
		pipe(pipe_fd);
		node->outfile = pipe_fd[1]; // Set this command to write to pipe;
		node->next->infile = pipe_fd[0];  // Set next command's input
	}
	else
		node->outfile = STDOUT_FILENO; // Set last command's output to terminal

	if (node->type)
	{
		if (handle_files(node) < 0)
			return (ERROR);
	}

	exec_cmd(node, env);

	if (node->next != NULL)
	{
		// close_fd(node->infile, node->outfile);
		close(pipe_fd[1]); // Close current pipe's write end
	}
	
	
	/* BUG:
	 * I need to close infile for first cmd: like => cat | ls. ls should print then cat
	 */
	return (SUCCESS);
}

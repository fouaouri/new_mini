/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:47:16 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/06 12:22:11 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	 BUG:
	 => I need to close infile for first cmd: like => cat | ls. ls should print then cat
*/
void	execute(t_list *node)
{
	int pipe_fd[2];

	if (node->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return ;
    }
		node->next->infile = pipe_fd[0];  // Set next command's input
		node->outfile = pipe_fd[1]; // Set this command to write to pipe;
	}
	else
		node->outfile = STDOUT_FILENO; // Set last command's output to terminal

	if (node->type)
	{
		if (handle_files(node) < 0)
			return ;
	}

	exec_cmd(node);
}

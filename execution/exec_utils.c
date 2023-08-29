/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:19:28 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/29 16:39:01 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/wait.h>

void	close_fd(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

int	wait_childs(t_list *node)
{
	int g_exit_status;
	int status;

	g_exit_status = 0;
	while (node)
	{
		if (node->pid != 0)
		{
			if (waitpid(node->pid, &status, 0) == -1)
				return (ERROR);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_exit_status = WTERMSIG(status) + 128;
		}
		node = node->next;
	}
	return (g_exit_status);
}

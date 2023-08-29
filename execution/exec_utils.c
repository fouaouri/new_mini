/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:19:28 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/29 12:05:41 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_fd(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

int	wait_childs(t_list *node)
{
	int status;
	// loop over the pids and wait for each one of them
	
	while (node != NULL)
	{
		if (node->pid != 0)
		{
			waitpid(node->pid, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
		node = node->next;
	}
	return status;
}

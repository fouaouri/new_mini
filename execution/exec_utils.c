/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:19:28 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/05 17:52:26 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	close_fd(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

void	ft_dup2(int in_fd, int out_fd)
{
	dup2(in_fd, STDIN_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	dup2(out_fd, STDOUT_FILENO);
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

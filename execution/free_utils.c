/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:53:42 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 22:11:27 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_list(t_list **node)
{
	t_list	*temp;

	while (*node != NULL)
	{
		temp = (*node);
		free((*node)->commandes);
		free((*node)->type);
		free((*node)->file_name);
		(*node) = (*node)->next;
		free(temp);
	}
}

void	ft_free(char **str)
{
	int	i;

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

void	wait_for_all(t_list *node, int *g_exit_status, int *should_update)
{
	*should_update = 1;
	while (node)
	{
		if (node->pid == 0 || *g_exit_status == 127)
		{
			close_fd(node->infile, node->outfile);
			node = node->next;
			continue ;
		}
		if (*g_exit_status == 126)
		{
			waitpid(node->pid, NULL, 0);
			should_update = 0;
			node = node->next;
			continue ;
		}
		if (waitpid(node->pid, g_exit_status, 0) == -1)
			exit(EXIT_FAILURE);
		if (WIFEXITED(*g_exit_status))
			*g_exit_status = WEXITSTATUS(*g_exit_status);
		else if (WIFSIGNALED(*g_exit_status))
			*g_exit_status = WTERMSIG(*g_exit_status) + 128;
		close_fd(node->infile, node->outfile);
		node = node->next;
	}
}

void	check_error(char *cmd_full_path)
{
	if (!ft_strcmp(cmd_full_path, "."))
		g_data.exit_status = 126;
	if (!ft_strcmp(cmd_full_path, ".."))
		g_data.exit_status = 126;
	if (access(cmd_full_path, X_OK) != 0)
		g_data.exit_status = 126;
}

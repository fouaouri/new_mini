/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:37:50 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/29 22:34:08 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_cmd(t_list *node, char **env) {
	char *cmd_full_path;

	// just for now
	// check for builtins exit
	if (node->commandes[0] && !ft_strcmp(node->commandes[0], "exit"))
		ft_exit(node->commandes);

	// FIX: just fix for now
	if (node->commandes[0])
	{
		cmd_full_path = check_cmd(parse_path(getenv("PATH")), node->commandes[0]);

		if (cmd_full_path)
		{
			node->pid = fork();
			if (node->pid == 0)
			{
				if (node->infile != STDIN_FILENO)
					dup2(node->infile, STDIN_FILENO);
				if (node->outfile != STDOUT_FILENO)
					dup2(node->outfile, STDOUT_FILENO);

				// close in and out fds
				close_fd(node->infile, node->outfile);

				if (execve(cmd_full_path, node->commandes, env) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else if (node->pid != 0)
				close_fd(node->infile, node->outfile);
			else if (node->pid < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
		}
		else // error checking
		{
			if (ft_strchr(node->commandes[0], '/'))
				printf("minishell: %s: no such file or directory\n", node->commandes[0]);
			else
				printf("minishell: %s: command not found\n", node->commandes[0]);
		}
	}
}

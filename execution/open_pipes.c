/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:37:50 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/04 16:01:24 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <unistd.h>

void	exec_cmd(t_list *node, char **env, t_env **env_list)
{
	char *cmd_full_path;

	// just for now
	// check for builtins exit
	if (node->commandes[0] && !ft_strcmp(node->commandes[0], "exit"))
		ft_exit(node->commandes);
	
	if (node->commandes[0] && !ft_strcmp(node->commandes[0], "export"))
	{
		ft_export(env_list, node->commandes);
		return ;
	}
	if (node->commandes[0] && !ft_strcmp(node->commandes[0], "unset"))
	{
		ft_unset(env_list, node->commandes);
		return ;
	}

	// FIX: just fix for now
	if (node->commandes[0])
	{
		// cmd_full_path = check_cmd(parse_path(getenv("PATH")), node->commandes[0]);
		cmd_full_path = check_cmd(parse_path(env_list), node->commandes[0]);
		if (cmd_full_path)
		{
			node->pid = fork();
			if (node->pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				ft_dup2(node->infile, node->outfile);

				// check if infile is 0. then close it
				if (node->next)
				{
					if (node->next->infile != STDIN_FILENO)
						close(node->next->infile);
				}
				if (execve(cmd_full_path, node->commandes, env) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else if (node->pid != 0)
			{
				signal(SIGINT, SIG_IGN);
				close_fd(node->infile, node->outfile);
			}
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

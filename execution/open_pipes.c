/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:37:50 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/06 15:12:03 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_builtins(t_list *node, char *builtin)
{
	if (!ft_strcmp(builtin, "export"))
		ft_export(node->commandes);
	else if (!ft_strcmp(builtin, "unset"))
		ft_unset(node->commandes);
	else if (!ft_strcmp(builtin, "env"))
		ft_env();
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(node->commandes);
	// else if (!ft_strcmp(builtin, "echo"))
	// 	ft_echo(node->commandes);
	// else if (!ft_strcmp(builtin, "cd"))
	// 	ft_cd(node->commandes);
	// else if (!ft_strcmp(builtin, "pwd"))
	// 	ft_pwd();
}

void	exec_cmd(t_list *node)
{
	char	*cmd_full_path;
	char	**env;

	if (!node->commandes[0])
		return ;
	env = create_env();
	execute_builtins(node, node->commandes[0]);
	cmd_full_path = check_cmd(parse_path(), node->commandes[0]);
	if (!cmd_full_path)
	{
		if (ft_strchr(node->commandes[0], '/'))
			printf("minishell: %s: no such file or directory\n", node->commandes[0]);
		else
			printf("minishell: %s: command not found\n", node->commandes[0]);


		return ;
	}
	node->pid = fork();
	if (node->pid < 0)
	{
		perror(strerror(errno));
		exit(0);
	}
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
			perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else if (node->pid != 0)
	{
		signal(SIGINT, SIG_IGN);
	}
	ft_free(env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:37:50 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/10 17:32:25 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_builtins(t_list *node, char *builtin)
{
	if (!ft_strcmp(builtin, "export"))
		ft_export(node->commandes);
	else if (!ft_strcmp(builtin, "unset"))
		ft_unset(node->commandes);
	else if (!ft_strcmp(builtin, "env"))
		ft_env();
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(node->commandes);
	else if (!ft_strcmp(builtin, "cd"))
		ft_cd(node->commandes);
	else if (!ft_strcmp(builtin, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(builtin, "echo"))
		ft_echo(node);
	else
		return 0;
	return 1;
}

int	exec_cmd(t_list *node)
{
	char	*cmd_full_path;
	char	**env;

	if(!node->commandes[0]) 
		return (ERROR);
	if (!node->commandes[0][0])
	{
		ft_dprintf(2, "minishell: %s: command not found\n", node->commandes[0]);
		return (ERROR);
	}

	env = create_env();

	// check if builtin should be executed on child or not
	if (execute_builtins(node, node->commandes[0]))
		return (SUCCESS);
	cmd_full_path = check_cmd(parse_path(), node->commandes[0]);

	if (!cmd_full_path)
	{
		if (ft_strchr(node->commandes[0], '/'))
			ft_dprintf(2,"minishell: %s: no such file or directory\n", node->commandes[0]);
		else
			ft_dprintf(2,"minishell: %s: command not found\n", node->commandes[0]);
		g_data.exit_status = 127;
		return (ERROR);
	}
	else if (!ft_strcmp(cmd_full_path, "p"))
	{
		ft_dprintf(2,"minishell: %s: Permission denied\n", node->commandes[0]);
		g_data.exit_status = 127;
		return (ERROR);
	}
	node->pid = fork();
	if (node->pid < 0)
	{
		ft_dprintf(2,"minishell: fork: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
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
			// ft_dprintf(2,"minishell: %s: ", node->commandes[0]);
			ft_dprintf(2,"minishell: %s: %s\n", node->commandes[0], strerror(errno));
			g_data.exit_status = 127;
			exit(EXIT_FAILURE);
		}
	}
	else if (node->pid != 0)
	{
		signal(SIGINT, SIG_IGN);
	}
	ft_free(env);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:37:50 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/13 16:13:24 by melhadou         ###   ########.fr       */
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

int	is_builtins(char *builtin)
{
	if (!ft_strcmp(builtin, "export"))
		return 1;
	else if (!ft_strcmp(builtin, "unset"))
		return 1;
	else if (!ft_strcmp(builtin, "env"))
		return 1;
	else if (!ft_strcmp(builtin, "exit"))
		return 1;
	else if (!ft_strcmp(builtin, "cd"))
		return 1;
	else if (!ft_strcmp(builtin, "pwd"))
		return 1;
	else if (!ft_strcmp(builtin, "echo"))
		return 1;
	return 0;
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
	cmd_full_path = check_cmd(parse_path(), node->commandes[0]);

	if (!cmd_full_path && !is_builtins(node->commandes[0]))
	{
		if (ft_strchr(node->commandes[0], '/'))
			ft_dprintf(2,"minishell: %s: no such file or directory\n", node->commandes[0]);
		else
			ft_dprintf(2,"minishell: %s: command not found\n", node->commandes[0]);
		g_data.exit_status = 127;
		ft_free(env);
		return (ERROR);
	}
	else if (!ft_strcmp(cmd_full_path, "p"))
	{
		ft_dprintf(2,"minishell: %s: Permission denied\n", node->commandes[0]);
		g_data.exit_status = 127;
		ft_free(env);
		return (ERROR);
	}
	node->pid = fork();
	if (node->pid < 0)
	{
		ft_dprintf(2,"minishell: fork: %s\n", strerror(errno));
		ft_free(env);
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
		// execute builtin
		if (is_builtins(node->commandes[0]))
		{
			if (execute_builtins(node, node->commandes[0]))
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		}
		else if (execve(cmd_full_path, node->commandes, env) == -1)
		{
			ft_dprintf(2,"minishell: %s: %s\n", node->commandes[0], strerror(errno));
			g_data.exit_status = 127;
			ft_free(env);
			exit(EXIT_FAILURE);
		}
	}
	else if (node->pid != 0)
	{
		signal(SIGINT, SIG_IGN);
	}
	if (env)
		ft_free(env);
	return (SUCCESS);
}

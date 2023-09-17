/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:37:50 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 22:03:47 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_builtins(t_list *node, char *builtin)
{
	int	err;

	err = 0;
	if (!ft_strcmp(builtin, "export"))
		err = ft_export(node->commandes);
	else if (!ft_strcmp(builtin, "unset"))
		ft_unset(node->commandes);
	else if (!ft_strcmp(builtin, "env"))
		ft_env();
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(node->commandes);
	else if (!ft_strcmp(builtin, "cd"))
		err = ft_cd(node->commandes);
	else if (!ft_strcmp(builtin, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(builtin, "echo"))
		err = ft_echo(node);
	else
		return (0);
	if (err == -1)
		return (0);
	else
		g_data.exit_status = 0;
	return (1);
}

int	run_builtins_pipe(t_list *node)
{
	int	err;

	err = execute_builtins(node, node->commandes[0]);
	if (err)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

void	exec_in_child(t_list *node, char **env, char *cmd_full_path)
{
	signal(SIGQUIT, SIG_DFL);
	ft_dup2(node->infile, node->outfile);
	if (node->next)
		if (node->next->infile != STDIN_FILENO)
			close(node->next->infile);
	if (is_builtins(node->commandes[0]))
		exit(run_builtins_pipe(node));
	else if (execve(cmd_full_path, node->commandes, env) == -1)
	{
		ft_dprintf(2, "minishell: %s: %s\n", \
			node->commandes[0], strerror(errno));
		g_data.exit_status = 126;
		exit(EXIT_FAILURE);
	}
}

int	exec_cmd(t_list *node)
{
	char	*cmd_full_path;
	char	**env;

	if (check_for_valid_cmd(node) == ERROR)
		return (ERROR);
	env = create_env();
	cmd_full_path = full_path(node);
	if (!cmd_full_path)
		return (ERROR);
	node->pid = fork();
	if (node->pid < 0)
	{
		ft_dprintf(2, "minishell: fork: %s\n", strerror(errno));
		g_data.exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (node->pid == 0)
		exec_in_child(node, env, cmd_full_path);
	else if (node->pid != 0)
		signal(SIGINT, SIG_IGN);
	check_error(cmd_full_path);
	return (SUCCESS);
}

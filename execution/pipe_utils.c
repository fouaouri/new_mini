/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:53:20 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/14 18:54:05 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtins(char *builtin)
{
	if (!ft_strcmp(builtin, "export"))
		return (1);
	else if (!ft_strcmp(builtin, "unset"))
		return (1);
	else if (!ft_strcmp(builtin, "env"))
		return (1);
	else if (!ft_strcmp(builtin, "exit"))
		return (1);
	else if (!ft_strcmp(builtin, "cd"))
		return (1);
	else if (!ft_strcmp(builtin, "pwd"))
		return (1);
	else if (!ft_strcmp(builtin, "echo"))
		return (1);
	return (0);
}

int	check_for_valid_cmd(t_list *node)
{
	if (!node->commandes[0]) 
		return (ERROR);
	if (!node->commandes[0][0])
	{
		ft_dprintf(2, "minishell: %s: command not found\n", node->commandes[0]);
		return (ERROR);
	}
	return (SUCCESS);
}

char	*full_path(t_list *node)
{
	char	*cmd_full_path;

	cmd_full_path = check_cmd(parse_path(), node->commandes[0]);
	if (!cmd_full_path && !is_builtins(node->commandes[0]))
	{
		if (ft_strchr(node->commandes[0], '/'))
			ft_dprintf(2, "minishell: %s: no such file or directory\n", \
				node->commandes[0]);
		else
			ft_dprintf(2, "minishell: %s: command not found\n", \
				node->commandes[0]);
		g_data.exit_status = 127;
		return (NULL);
	}
	else if (!ft_strcmp(cmd_full_path, "p"))
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", node->commandes[0]);
		g_data.exit_status = 127;
		return (NULL);
	}
	return (cmd_full_path);
}

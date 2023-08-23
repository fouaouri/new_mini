/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:37:50 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/23 13:01:11 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* 
 * open pipes ?? => why i need them
 * fork then open pipe . to begin execution
 * check command and exec
 * [] 
 */

void	exec_one_cmd(t_list *node, char **env)
{
	char	*cmd_full_path;
	int	pid;

	cmd_full_path = check_cmd(parse_path(getenv("PATH")), node->commandes[0]);
	if (cmd_full_path)
	{
		pid = fork();
		// causes a segfualt
		if (pid == 0)
		{
			if (node->outfile != 1)
			{
				dup2(node->outfile, 1);
			}
			if (execve(cmd_full_path, node->commandes, env) == -1)
				exit(1);
		}
		wait(&pid);
	}
}

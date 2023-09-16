/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:32:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/16 20:21:17 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	handle_heredoc(t_read *readline, t_env *l_env, t_list *node)
{
	int	i;
	int	fd;

	while (node != NULL)
	{
		i = 0;
		while (node->type[i])
		{
			if (!ft_strcmp(node->type[i], "h"))
			{
				if (node->file_name[i] == NULL)
					return (0);
				fd = ft_heredoc(readline, l_env, node->file_name[i]);
				if (fd == -1)
					return (fd);
				free(node->type[i]);
				node->type[i] = ft_strdup("H");
				free(node->file_name[i]);
				node->file_name[i] = ft_itoa(fd);
			}
			i++;
		}
		node = node->next;
	}
	return (SUCCESS);
}

int	run_in_parent(int p_fd[2], int pid)
{
	close(p_fd[1]);
	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &g_data.exit_status, 0) == -1)
	{
		ft_dprintf(2, "minishell: waitpid: %s\n", strerror(errno));
		return (-1);
	}
	if (WIFSIGNALED(g_data.exit_status))
	{
		close(p_fd[0]);
		return (-1);
	}
	signal(SIGINT, ctl_c_handler);
	return (SUCCESS);
}

void	heredoc_handler(t_read *readln, t_env *l_env, int p_fd[2], char *dilimiter)
{
	readln->input = readline("> ");
	if (g_data.heredoc == 0)
		expand_arr(readln, l_env);
	else
		readln->exp = ft_strdup(readln->input);
	if (!readln->exp)
	{
		ft_dprintf(2, \
			"Minishell: warning: heredoc error: (wanted delemter'%s')\n", \
			dilimiter);
		close(p_fd[1]);
		exit(0);
	}
	if (!ft_strcmp(readln->exp, dilimiter))
	{
		close(p_fd[1]);
		exit(0);
	}
	write(p_fd[1], readln->exp, ft_strlen(readln->exp));
	write(p_fd[1], "\n", 1);
}

int	ft_heredoc(t_read *readline, t_env *l_env, char *dilimiter)
{
	// char	*line;
	int		pid;
	int		p_fd[2];

	// line = NULL;
	if (dilimiter == NULL)
		return (-1);
	pipe(p_fd);
	pid = fork();
	if (pid == 0)
	{
		close(p_fd[0]);
		signal(SIGINT, SIG_DFL);
		while (1)
			heredoc_handler(readline, l_env, p_fd, dilimiter);
	}
	else if (pid != 0)
		if (run_in_parent(p_fd, pid) == -1)
			return (-1);
	return (p_fd[0]);
}

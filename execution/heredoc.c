/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:32:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/01 21:17:21 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	handle_heredoc(t_list *node)
{
	int	i;

	while (node != NULL)
	{
		i = 0;
		while (node->type[i])
		{
			if (!ft_strcmp(node->type[i], "h"))
			{
				// FIX: handle err
				if (node->file_name[i] == NULL)
					return 0;
				int fd = ft_heredoc(node->file_name[i]);
				if (fd == -1)
					return (fd); // error
				free(node->file_name[i]);
				node->file_name[i] = ft_itoa(fd);
			}
			i++;
		}
		node = node->next;
	}
	return (SUCCESS);
}

int	ft_heredoc(char *dilimiter)
{
	char	*line;
	int		pid;
	int		p_fd[2];

	// check for error in pipe
	if (dilimiter == NULL)
		return (-1);

	pipe(p_fd);
	pid = fork();
	if (pid == 0)
	{
		close(p_fd[0]);

		signal(SIGINT, SIG_DFL);

		while (1)
		{
			line = readline("> ");
			if (!line || !ft_strcmp(line, dilimiter))
			{
				close(p_fd[1]);
				exit(0);
			}
			write(p_fd[1], line, ft_strlen(line));
			write(p_fd[1], "\n", 1);
			free(line);
		}
	}
	else if (pid != 0)
	{
		close(p_fd[1]);
		signal(SIGINT, SIG_IGN);
		if (waitpid(pid, &g_data.exit_status, 0) == -1)
		{
			perror("waitpid");
			return -1;
		}
		if (WIFSIGNALED(g_data.exit_status))
				return -1;
		signal(SIGINT, ctl_c_handler);
	}
	// char *data = malloc(1000);
	// read(p_fd[0], data, 1000);
	// printf("%s \n", data);
	return (p_fd[0]);
}

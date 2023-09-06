/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:32:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/28 18:43:52 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_heredoc(t_list *node)
{
	int	i;

	while (node != NULL)
	{
		i = 0;
		while (node->type[i])
		{
			if (!ft_strcmp(node->type[i], "h"))
			{
				if (node->file_name[i] == NULL)
					return ;
				int fd = ft_heredoc(node->file_name[i]);
				free(node->file_name[i]);
				node->file_name[i] = ft_itoa(fd);
			}
			i++;
		}
		node = node->next;
	}
}

int	ft_heredoc(char *dilimiter)
{
	char *line;
	int p_fd[2];

	// check for error in pipe
	if (dilimiter == NULL)
	{
		return (-1);
	}
	pipe(p_fd);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, dilimiter))
			break ;
		write(p_fd[1], line, ft_strlen(line));
		write(p_fd[1], "\n", 1);
		free(line);
	}
	close(p_fd[1]);
	return (p_fd[0]);
}

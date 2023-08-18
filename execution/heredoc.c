/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:32:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/18 21:47:20 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_heredoc(char *dilimiter)
{
	char *line;
	int p_fd[2];

	// check for error in pipe
	pipe(p_fd);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, dilimiter))
			break ;
		write(p_fd[1], line, ft_strlen(line));
		free(line);
		close(p_fd[1]);
	}
	return (p_fd[0]);
}

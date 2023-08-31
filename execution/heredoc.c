/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:32:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/31 21:17:04 by melhadou         ###   ########.fr       */
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
					return (fd);
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
	char *line;
	int pid;
	int p_fd[2];

	// check for error in pipe
	if (dilimiter == NULL)
	{
		return (-1);
	}

	pipe(p_fd);
	pid = fork();
	if (pid == 0)
	{
		close(p_fd[1]);
		// seting signals to default
		signal(SIGINT, SIG_DFL);

		while (1)
		{
			line = readline("> ");
			if (!line)
				// need to exit with a code
				exit(0);
			if (!ft_strcmp(line, dilimiter))
				exit(0) ;
			write(p_fd[1], line, ft_strlen(line));
			write(p_fd[1], "\n", 1);
			free(line);
		}
	}
	else if (pid != 0)
	{
		signal(SIGINT, SIG_IGN);
		// close parent
		// NOTE: read about 
		waitpid(pid, &g_data.exit_status, 0);
		if(WIFSIGNALED(g_data.exit_status))
			return -1;
		signal(SIGINT, ctl_c_handler);
	}
	return (p_fd[0]);
}

// int handle_heredoc(t_list *node) {
// 	int i;

// 	while (node != NULL) {
// 		i = 0;
// 		while (node->type[i]) {
// 			if (!strcmp(node->type[i], "h"))
// 			{
// 				if (node->file_name[i] == NULL)
// 						return 0; // Handle error
// 				int fd = ft_heredoc(node->file_name[i]);
// 				if (fd == -1)
// 						return fd; // Handle error
// 				free(node->file_name[i]);
// 				node->file_name[i] = ft_itoa(fd);
// 			}
// 			i++;
// 		}
// 		node = node->next;
// 	}
// 	return 1; // Success
// }

// // Function for heredoc processing
// int ft_heredoc(char *delimiter) {
// 	char *line;
// 	int pid;
// 	int p_fd[2];

// 	if (delimiter == NULL)
// 		return -1;

// 	if (pipe(p_fd) == -1)
// 	{
// 		perror("Pipe creation failed");
// 		return -1;
// 	}

// 	pid = fork();
// 	if (pid == 0) {
// 		signal(SIGINT, SIG_DFL);

// 		close(p_fd[0]); // Close the read end in the child

// 		while (1)
// 		{
// 			line = readline("> ");
// 			if (!line)
// 				_exit(0); // Terminate the child process immediately
// 			if (!ft_strcmp(line, delimiter))
// 				_exit(0);
// 			write(p_fd[1], line, strlen(line));
// 			write(p_fd[1], "\n", 1);
// 			free(line);
// 		}
// 	}
// 	else if (pid > 0)
// 	{
// 		signal(SIGINT, SIG_IGN);

// 		close(p_fd[1]); // Close the write end in the parent

// 		int status;
// 		waitpid(pid, &status, 0);
// 		
// 		if (WIFSIGNALED(status))
// 			return -1;
// 		signal(SIGINT, ctl_c_handler);
// 	}
// 	else
// 	{
// 		perror("Fork failed");
// 		close(p_fd[0]);
// 		close(p_fd[1]);
// 		return -1;
// 	}
// 	
// 	return p_fd[0]; // Return the read end of the pipe
// }

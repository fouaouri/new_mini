/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/27 16:52:28 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main(int ac, char **av, char **env) {
	(void)av;
	t_read *readline;
	t_list **hold;
	int i;
	int pipe_fd[2];

	readline = malloc(sizeof(t_read));
	
	while (ac == 1) {
		hold = parsing(readline, env);
		(*hold)->outfile = STDOUT_FILENO;
		(*hold)->infile = STDIN_FILENO;

		t_list *current = *hold;
		
		while (current != NULL)
		{
			i = 0;
			while (current->type[i])
			{
				if (!ft_strcmp(current->type[i], "h"))
				{
					int fd = ft_heredoc(current->file_name[i]);
					free(current->file_name[i]);
					current->file_name[i] = ft_itoa(fd);
				}
				i++;
			}
			current = current->next;
		}

		current = *hold;

		while (current != NULL)
		{
			if (current->next != NULL) {
				pipe(pipe_fd);
				current->outfile = pipe_fd[1]; // Set this command to write to pipe;
				current->next->infile = pipe_fd[0];  // Set next command's input
			} else
				current->outfile = STDOUT_FILENO; // Set last command's output to terminal

			if (current->type)
			{
				int status = handle_files(current);
				if (status < 0)
				{
					// FIX: Handle error and make exec function not in main
					break ;
				}
			}

			exec_cmd(current, env);

			if (current->next != NULL) {
					close(pipe_fd[1]); // Close current pipe's write end
			}
			current = current->next;
		}

		// Clean up linked list or move this to a separate function
		t_list *temp;
		while (*hold != NULL) {
				temp = (*hold);
				(*hold) = (*hold)->next;
				free(temp);
		}
	}
}

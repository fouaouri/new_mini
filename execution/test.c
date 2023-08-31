/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/30 18:58:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int ac, char **av, char **env) {
	t_read *readline;
	t_list **hold;

	(void)av;
	readline = malloc(sizeof(t_read));
	while (ac == 1) {
		hold = parsing(readline, env);
		if(hold)
		{
			(*hold)->outfile = STDOUT_FILENO;
			(*hold)->infile = STDIN_FILENO;

			t_list *current = *hold;
			
			// heredoc and handle it
				handle_heredoc(current);

			while (current != NULL)
			{
				execute(current, env);
				current = current->next;
			}

			// Clean up linked list or move this to a separate function
			// if (current->infile != STDIN_FILENO)
			// 	close(current->infile);
			// if (current->outfile != STDOUT_FILENO)
			// 	close(current->outfile);
			free_list(hold);
			
		}
	}
}

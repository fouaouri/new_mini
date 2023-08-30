/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/29 23:09:58 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int ac, char **av, char **env) {
	t_read	*readline;
	t_list	**hold;

	(void)av;
	readline = malloc(sizeof(t_read));
	while (ac == 1) {
		hold = parsing(readline, env);
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

		// need to wait for all childs
		int status = wait_childs(*hold);
		if (status == -1)
			return (ERROR);

		// Clean up linked list or move this to a separate function
		free_list(hold);
	}
}

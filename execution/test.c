/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/09 22:25:03 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

t_data	g_data;

int	main(int ac, char **av, char **env) {
	t_read	*readline;
	t_list	**hold;
	int status;
	g_data.exit_status = 0;

	(void)av;
	readline = malloc(sizeof(t_read));
	if (!readline)
		return (ERROR);
	g_data.l_env = init_env(env);

	while (ac == 1)
	{
		// setting signals
		signal(SIGINT, ctl_c_handler);
		// ctr-/
		signal(SIGQUIT, SIG_IGN);
		
		hold = parsing(readline, g_data.l_env);
		if (hold)
		{
			printf("exit_status: %d\n", g_data.exit_status);
			(*hold)->outfile = STDOUT_FILENO;
			(*hold)->infile = STDIN_FILENO;

			t_list *current = *hold;
			
			// heredoc and handle it
			if (handle_heredoc(current) == -1)
			{
				// close fds
				close_fd(current->infile, current->outfile);
				// set the right status code
				g_data.exit_status = 130;
				ft_dprintf(2, "minishell: heredoc: %s\n", strerror(errno));
				continue ;
			}

			while (current != NULL)
			{
				if (execute(current) == SUCCESS)
					g_data.exit_status = 0;
				current = current->next;
			}

			// need to wait for all childs
			// if (!g_data.error)
			// {
			status = wait_childs(*hold);
			if (status == -1)
				return (ERROR);
			// }
			free_list(hold);
		}
		else
			continue ;
		
	}
	return 0;
}

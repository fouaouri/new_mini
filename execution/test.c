/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/11 16:43:42 by melhadou         ###   ########.fr       */
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
		// int i;
		// 	i = 0;
		// 	while((*hold)->commandes && (*hold)->commandes[i])
		// 		printf("commandes :%s\n", (*hold)->commandes[i++]);
		// 	i = 0;
		// 	 while((*hold)->file_name && (*hold)->file_name[i])
		// 	 	printf("file_name : %s\n", (*hold)->file_name[i++]);
		// 	i = 0;
		// 	while ((*hold)->type && (*hold)->type[i])
		// 		printf("type : %s\n", (*hold)->type[i++]);
		if (hold)
		{
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

			if (current->next == NULL)
			{
				if (execute_builtins(current, current->commandes[0]))
					continue ;
				else
					close_fd(current->infile, current->outfile);
			}
			while (current != NULL)
			{
				if (execute(current) == SUCCESS)
					g_data.exit_status = 0;
				else
					close_fd(current->infile, current->outfile);
				current = current->next;
			}

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

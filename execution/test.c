/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/12 17:49:53 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

t_data	g_data;

int	main(int ac, char **av, char **env) {
	t_read	*readline;
	t_list	**hold;
	t_list *current;
	t_list *tmp;
	int i;
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
			(*hold)->outfile = STDOUT_FILENO;
			(*hold)->infile = STDIN_FILENO;

			current = *hold;
			// heredoc and handle it
			if (handle_heredoc(current) == -1)
			{
				tmp = *hold;
				// close fds
				close_fd(current->infile, current->outfile);
				// set the right status code
				g_data.exit_status = 130;
				// while nodes
				while(tmp)
				{
					i = 0;
					while(tmp->type[i])
					{
						if (!ft_strcmp(tmp->type[i], "H"))
							close(ft_atoi(tmp->file_name[i]));
						i++;
					}
					tmp = tmp->next;
				}
				continue ;
			}

			if (current->next == NULL)
			{
				if (execute_builtins(current, current->commandes[0]))
					continue;
				else
					close_fd(current->infile, current->outfile);
			}
			while (current)
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
			g_data.exit_status = status;
		}
		else
			continue ;
		free_list(hold);
	}
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/14 17:12:04 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"
#include <readline/readline.h>

t_data	g_data;

int	main(int ac, char **av, char **env) {
	t_read	*readline;
	t_list	**hold;
	t_list *current;
	t_list *tmp;
	int i;
	int status;
	int std_in;
	int std_out;
	int err;
	g_data.exit_status = 0;

	(void)av;
	readline = my_malloc(sizeof(t_read));
	if (!readline)
		return (ERROR);
	g_data.l_env = init_env(env);

	while (ac == 1)
	{
		signal(SIGINT, ctl_c_handler);
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

			if (current->next == NULL && is_builtins(current->commandes[0]))
			{

				std_in = dup(STDIN_FILENO);
				std_out = dup(STDOUT_FILENO);
				err = handle_files(current);
				if (err < 0)
				{
					g_data.exit_status = 1;
					return (err);
				}
				ft_dup2(current->infile, current->outfile);
				if (execute_builtins(current, current->commandes[0]))
				{
					dup2(std_in, STDIN_FILENO);
					dup2(std_out, STDOUT_FILENO);
					close(std_in);
					close(std_out);
					continue;
				}
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
			free(readline->input);
		}
		else
			continue ;
	}
	return 0;
}

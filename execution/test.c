/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/06 15:20:40 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

t_data	g_data;

int	main(int ac, char **av, char **env) {
	t_read	*readline;
	t_list	**hold;
	int status;

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

		hold = parsing(readline, env);
		if (hold)
		{

			(*hold)->outfile = STDOUT_FILENO;
			(*hold)->infile = STDIN_FILENO;

			t_list *current = *hold;
			
			// heredoc and handle it
			if (handle_heredoc(current) == -1)
			{
				// set the right status code
				g_data.exit_status = 130;
				printf("heredoc error\n");
				continue ;
			}

			while (current != NULL)
			{
				execute(current);
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

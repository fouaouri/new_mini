/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/03 19:25:42 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

t_data	g_data;

int	main(int ac, char **av, char **env) {
	t_read	*readline;
	t_list	**hold;
	t_env *env_list;

	(void)av;
	readline = malloc(sizeof(t_read));

	env_list = init_env(env);

	while (ac == 1)
	{
		// setting signals

		signal(SIGINT, ctl_c_handler);
		// ctr-/
		signal(SIGQUIT, SIG_IGN);

		hold = parsing(readline, env);
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
			execute(current, env, &env_list);
			current = current->next;
		}

		// need to wait for all childs
		int status = wait_childs(*hold);
		if (status == -1)
			return (ERROR);

		free_list(hold);
	}
}

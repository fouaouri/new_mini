/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 00:17:24 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_data	g_data;

int	run_execution(t_list *current, t_list **hold)
{
	int	status;

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
	if (status == 13)
		status = 127;
	printf("status -> %d\n", status);
	g_data.exit_status = status;
	return (SUCCESS);
}

void	run_heredoc(t_list **hold, t_list *current)
{
	t_list	*tmp;
	int		i;

	tmp = *hold;
	close_fd(current->infile, current->outfile);
	g_data.exit_status = 130;
	while (tmp)
	{
		i = 0;
		while (tmp->type[i])
		{
			if (!ft_strcmp(tmp->type[i], "H"))
				close(ft_atoi(tmp->file_name[i]));
			i++;
		}
		tmp = tmp->next;
	}
	free_list(&tmp);
}

int	main(int ac, char **av, char **env)
{
	t_read	*readline;
	t_list	*current;

	current = NULL;
	(void)av;
	readline = my_malloc(sizeof(t_read));
	if (!readline)
		return (ERROR);
	g_data.l_env = init_env(env);
	if (run_minishell(ac, readline,g_data.l_env ,current) == ERROR)
		return (ERROR);
	return (0);
}

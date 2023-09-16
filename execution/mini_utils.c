/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:50:43 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/16 22:04:17 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	run_builtin(t_list *current)
{
	int	std_in;
	int	std_out;
	int	err;

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
		return (1);
	}
	else
		close_fd(current->infile, current->outfile);
	return (2);
}

void	set_hold(t_list *hold)
{
	hold->outfile = STDOUT_FILENO;
	hold->infile = STDIN_FILENO;
}

void	sig_handler(void)
{
	signal(SIGINT, ctl_c_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	run_minishell_util(t_read *readline, t_env *l_env, t_list *current, t_list **hold)
{
	int	err;

	if (handle_heredoc(readline, l_env,current) == -1)
	{
		run_heredoc(hold, current);
		return (2);
	}
	if (current->next == NULL && is_builtins(current->commandes[0]))
	{
		err = run_builtin(current);
		if (err == 1)
			return (2);
		else if (err < 0)
			return (ERROR);
	}
	if (run_execution(current, hold) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	run_minishell(int ac, t_read *readline, t_env *l_env, t_list *current)
{
	int		err;
	t_list	**hold;

	while (ac == 1)
	{
		sig_handler();
		hold = parsing(readline, g_data.l_env);
		if (!hold)
			continue ;
		set_hold(*hold);
		current = *hold;
		err = run_minishell_util(readline,l_env,current, hold);
		if (err < 0)
			return (ERROR);
		else if (err == 2)
			continue ;
		g_data.heredoc = 0;
	}
	return (SUCCESS);
}

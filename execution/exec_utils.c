/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:19:28 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 19:13:36 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_lst_size(void)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = g_data.l_env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*ft_concat(char *s1, char c, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = i;
	if (!s2)
		return (ft_strdup(s1));
	str = my_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	str[i++] = c;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	**create_env(void)
{
	char	**env;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = g_data.l_env;
	env = my_malloc(sizeof(char *) * (ft_lst_size() + 1));
	if (!env)
		return (NULL);
	while (tmp)
	{
		env[i] = ft_concat(tmp->key, '=', tmp->value);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	ft_dup2(int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		ft_dprintf(2, "minishell: dup2: %s\n", strerror(errno));
		g_data.exit_status = 1;
		my_free_all();
		exit(EXIT_FAILURE);
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	dup2(out_fd, STDOUT_FILENO);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		ft_dprintf(2, "minishell: dup2: %s\n", strerror(errno));
		g_data.exit_status = 1;
		my_free_all();
		exit(EXIT_FAILURE);
	}
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

int	wait_childs(t_list *node)
{
	int	g_exit_status;
	int shouldUpdate = 1;

	g_exit_status = g_data.exit_status;
	int res = g_exit_status;
	dprintf(2, "-> exit code at the begninng of time %d\n", g_exit_status);
	while (node)
	{
		if (node->pid == 0 || g_exit_status == 127)
		{
			dprintf(2, "-> skipping command\n");
			close_fd(node->infile, node->outfile);
			node = node->next;
			continue ;
		}

		if (g_exit_status == 126) {
			waitpid(node->pid, NULL, 0);
			shouldUpdate = 0;
			node = node->next;
			continue;
		}

		if (waitpid(node->pid, &g_exit_status, 0) == -1)
		{
			ft_dprintf(2, "minishell: waitpid: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(g_exit_status)) {
			g_exit_status = WEXITSTATUS(g_exit_status);
			dprintf(2, "-> command exited normally\n");
		} else if (WIFSIGNALED(g_exit_status)) {
			g_exit_status = WTERMSIG(g_exit_status) + 128;
			dprintf(2, "-> command exited due to uncaught signal\n");
		}

		close_fd(node->infile, node->outfile);
		node = node->next;
	}

	if (shouldUpdate)
		res = g_exit_status;

	return (res);
}

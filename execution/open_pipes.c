/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:37:50 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/05 18:05:12 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_lst_size()
{
	t_env *tmp;

	int i = 0;
	tmp = g_data.l_env;
	while (tmp)
	{
		tmp= tmp->next;
		i++;
	}
	return (i);
}

char *ft_concat(char *s1, char c, char *s2)
{
	char	*str;
	int	i;
	int j;

	i = 0;
	j = i;
	if (!s2)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	str[i++] = c;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char **create_env()
{
	char **env;
	t_env *tmp;
	int i;

	i = 0;
	tmp = g_data.l_env;
	env = malloc(sizeof(char *) * (ft_lst_size() + 1));
	while(tmp)
	{
		env[i] = ft_concat(tmp->key, '=', tmp->value);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	exec_cmd(t_list *node)
{
	char	*cmd_full_path;
	char	**env;

	env = create_env();
	// just for now
	// check for builtins exit
	if (node->commandes[0] && !ft_strcmp(node->commandes[0], "exit"))
		ft_exit(node->commandes);
	
	if (node->commandes[0] && !ft_strcmp(node->commandes[0], "export"))
	{
		ft_export(node->commandes);
		return ;
	}
	if (node->commandes[0] && !ft_strcmp(node->commandes[0], "unset"))
	{
		ft_unset(node->commandes);
		return ;
	}
	if (node->commandes[0] && !ft_strcmp(node->commandes[0], "env"))
	{
		ft_env();
		return ;
	}

	// FIX: just fix for now
	if (node->commandes[0])
	{
		// cmd_full_path = check_cmd(parse_path(getenv("PATH")), node->commandes[0]);
		cmd_full_path = check_cmd(parse_path(), node->commandes[0]);
		if (cmd_full_path)
		{
			node->pid = fork();
			if (node->pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				ft_dup2(node->infile, node->outfile);

				// check if infile is 0. then close it
				if (node->next)
				{
					if (node->next->infile != STDIN_FILENO)
						close(node->next->infile);
				}
				if (execve(cmd_full_path, node->commandes, env) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else if (node->pid != 0)
			{
				signal(SIGINT, SIG_IGN);
				close_fd(node->infile, node->outfile);
			}
			else if (node->pid < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
		}
		else // error checking
		{
			if (ft_strchr(node->commandes[0], '/'))
				printf("minishell: %s: no such file or directory\n", node->commandes[0]);
			else
				printf("minishell: %s: command not found\n", node->commandes[0]);
		}
		ft_free(env);
	}
}

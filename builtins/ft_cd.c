/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:16:02 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/12 16:10:39 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_cd(char **args)
{
	t_env	*home;
	char	*pwd;
	int		status;
	int		changed_dir;
	char	*oldpwd;
	t_env	*pwd_env;

	oldpwd = getcwd(NULL, 0);
	// check for multiple args
	if (args[1] && args[2])
	{
		ft_dprintf(2,"minishell: cd: too many arguments\n", 2);
		g_data.exit_status = 1;
		return ;
	}
	// checking for home = cd only
	if (!args[1])
	{
		home = ft_search_for_key("HOME");
		if (home)
		{
			changed_dir = chdir(home->value);
			if(changed_dir)
			{
				ft_dprintf(2,"minishell: cd: %s: not a directory\n", home->value);
				g_data.exit_status = 1;
				return ;
			}
			else
			{
				pwd_env = ft_search_for_key("PWD");
				if (pwd_env)
				{
					pwd = getcwd(NULL, 0);
					if (!pwd)
						return ;
					free(pwd_env->value);
					pwd_env->value = pwd;
				}
				pwd_env = ft_search_for_key("OLDPWD");
				if (pwd_env)
				{
					if (!oldpwd)
						return ;
					free(pwd_env->value);
					pwd_env->value = oldpwd;
				}
			}
			return ;
		}
		else
		{
			ft_dprintf(2,"minishell: cd: HOME not set\n");
			g_data.exit_status = 1;
			return ;
		}
	}

	status = access(args[1], F_OK);
	if (status)
	{
		g_data.exit_status = 1;
		ft_dprintf(2,"minishell: cd: %s: cd No such file or directory\n", args[1]);
		return ;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			ft_dprintf(2,"minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			g_data.exit_status = 1;
		}
		changed_dir = chdir(args[1]);
		if (changed_dir)
		{
			g_data.exit_status = 1;
			ft_dprintf(2,"minishell: cd: %s: not a directory\n", args[1]);
			return ;
		}
		else
		{
			pwd_env = ft_search_for_key("PWD");
			if (pwd_env)
			{
				free(pwd_env->value);
				pwd_env->value = pwd;
			}
			pwd_env = ft_search_for_key("OLDPWD");
			if (pwd_env)
			{
				if (!oldpwd)
					return ;
				free(pwd_env->value);
				pwd_env->value = oldpwd;
			}
		}
	}
}

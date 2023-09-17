/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:16:02 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 21:58:31 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	check_pwd(t_env *pwd_env, char *pwd, char *oldpwd)
{
	free(pwd);
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

int	check_home(t_env *home, t_env *pwd_env, char *pwd, char *oldpwd)
{
	int		changed_dir;

	if (home)
	{
		changed_dir = chdir(home->value);
		if (changed_dir)
		{
			ft_dprintf(2, "minishell: cd: %s: not a directory\n", home->value);
			g_data.exit_status = 1;
			free(oldpwd);
			return (-1);
		}
		else
			check_pwd(pwd_env, pwd, oldpwd);
	}
	else
	{
		ft_dprintf(2, "minishell: cd: HOME not set\n");
		g_data.exit_status = 1;
		free(oldpwd);
		return (-1);
	}
	return (1);
}

int	change_dir(char *args, char *pwd, char *oldpwd, t_env *pwd_env)
{
	int	changed_dir;

	changed_dir = chdir(args);
	if (changed_dir)
	{
		g_data.exit_status = 1;
		ft_dprintf(2, "minishell: cd: %s: not a directory\n", args);
		free(oldpwd);
		return (-1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_dprintf(2, "minishell: cd: error retrieving current directory:");
		ft_dprintf(2, \
	" getcwd: cannot access parent directories: No such file or directory\n");
		g_data.exit_status = 1;
	}
	else
		check_pwd(pwd_env, pwd, oldpwd);
	return (1);
}

int	ft_cd(char **args)
{
	t_env	*home;
	char	*pwd;
	int		status;
	char	*oldpwd;
	t_env	*pwd_env;

	oldpwd = getcwd(NULL, 0);
	pwd = NULL;
	pwd_env = NULL;
	if (check_args(args) < 0)
		return (free(oldpwd), (-1));
	if (!args[1])
	{
		home = ft_search_for_key("HOME");
		check_home(home, pwd_env, pwd, oldpwd);
		return (-1);
	}
	status = access(args[1], F_OK);
	if (check_access_status(status, args) < 0)
		return (free(oldpwd), (-1));
	else
		if (change_dir(args[1], pwd, oldpwd, pwd_env) < 0)
			return (-1);
	return (1);
}

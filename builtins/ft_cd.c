/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:16:02 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/06 21:52:02 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_cd(char **args)
{
	t_env *home;
	int status;
	// check for multiple args
	if (args[2])
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		return ;
	}
	// check arg for home
	if (!args[1])
	{
		home = ft_search_for_key("HOME");
		if (home->value)
		{
			// check acces for home
			status = access(home->value, F_OK);
			if (status == 0)
			{
				// check acces for home
				status = access(home->value, R_OK);
				if (status == 0)
				{
					// change dir
					status = chdir(home->value);
					if (status == 0)
					{
						// update pwd
						t_env *pwd = ft_search_for_key("PWD");
						pwd->value = getcwd(NULL, 0);
					}
					else
						ft_putstr_fd("Minishell: cd: permission denied\n", 2);
				}
				else
					ft_putstr_fd("Minishell: cd: permission denied\n", 2);
			}
			else
				ft_putstr_fd("Minishell: cd: no such file or directory\n", 2);
		}
		else
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			return ;
		}
	}
	else
	{
		// check acces to args[1]
		status = access(args[1], F_OK);
		if (status == 0)
		{
			// change dir
			status = chdir(args[1]);
			if (status == 0)
			{
				// update pwd
				t_env *pwd = ft_search_for_key("PWD");
				pwd->value = getcwd(NULL, 0);
			}
			else
				ft_putstr_fd("Minishell: cd: permission denied\n", 2);
		}
		else
			ft_putstr_fd("Minishell: cd: permission denied\n", 2);
	}
}

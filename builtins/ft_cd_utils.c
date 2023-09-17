/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:01:03 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 16:41:25 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n", 2);
		g_data.exit_status = 1;
		return (-1);
	}
	return (1);
}

int	check_access_status(int status, char **args)
{
	if (status)
	{
		g_data.exit_status = 1;
		ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", \
		args[1]);
		return (-1);
	}
	return (1);
}

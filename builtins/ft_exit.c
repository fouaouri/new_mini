/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:29:15 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/06 15:07:31 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_exit(char **args)
{
	char exit_code;

	if (!args[1])
		exit(0);
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		g_data.exit_status = 1;
		return ;
	}
	if (ft_isdigit(ft_atoi(args[1])))
	{
		exit_code = ft_atoi(args[1]);
		printf("minishell: exit: %s: succes\n", args[1]);
		exit(exit_code);
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
}

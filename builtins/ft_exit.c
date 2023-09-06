/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:29:15 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/06 16:22:10 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_exit(char **args)
{
	unsigned char exit_code;
	int i;

	i = 0;
	if (!args[1])
	{
		dprintf(2, "exit with 0\n");
		exit(0);
	}
	if (args[2])
	{
		printf("Minishell: exit: too many arguments\n");
		g_data.exit_status = 1;
		return ;
	}
	if (!args[1][i])
	{
		printf("Minishell: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	while (args[1][i])
	{
		if (i == 0 && (args[1][i] == '+' || args[1][i] == '-'))
			i++;
		if (!ft_isdigit(args[1][i]) || !args[1][i])
		{
			printf("Minishell: %s: numeric argument required\n", args[1]);
			exit(2);
		}
		i++;
	}
	exit_code = ft_atoi(args[1]);
	exit(exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:29:15 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 22:25:59 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	valid_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && (arg[i] != '-' && arg[i] != '+'))
		{
			ft_dprintf(2, \
			"Minishell: exit: %s: numeric argument required\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

unsigned char	ft_exit_util(char **args, char *str)
{
	unsigned char	exit_code;
	int				j;

	j = 0;
	if (args[2])
	{
		if (!valid_arg(args[1]))
			exit(2);
		ft_dprintf(2, "Minishell: exit: too many arguments\n");
		g_data.exit_status = 1;
		return (-1);
	}
	if (!valid_arg(args[1]))
		exit(2);
	str = ft_ltoa(ft_atol(args[1]));
	if (args[1][0] == '0' || args[1][0] == '+' || args[1][0] == '-')
		j = skip_zeros(args[1]);
	if (ft_strcmp(str, args[1] + j))
	{
		ft_dprintf(2, "Minishell: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	exit_code = ft_atol(args[1]);
	return (exit_code);
}

int	check_if_zeros(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != '0')
			return (-1);
		i++;
	}
	return (i);
}

void	ft_exit(char **args)
{
	unsigned char	exit_code;
	char			*str;
	int				i;

	str = NULL;
	i = 0;
	if (!args[1])
		exit(0);
	if (!args[1][i])
	{
		ft_dprintf(2, "Minishell: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (check_if_zeros(args[1]) != -1)
		exit(0);
	if (!ft_strcmp(args[1], "-1"))
		exit(-1);
	exit_code = ft_exit_util(args, str);
	if (exit_code == (unsigned char)-1)
		return ;
	exit(exit_code);
}

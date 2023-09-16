/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:45:54 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/16 18:15:36 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	case_n(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (len <= 1)
		return (1);
	while (str[i] && str[i + 1])
	{
		if (str[0] != '-' || str[i + 1] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_cases(t_list *hold, t_variables *var)
{
	while (hold->commandes[var->i] && hold->commandes[var->i + 1])
	{
		if (!case_n(hold->commandes[var->i]))
		{
			var->check = 1;
			var->i++;
		}
		else
			break ;
	}
	while (hold->commandes[var->i])
	{
		ft_putstr_fd(hold->commandes[var->i], 1);
		if (hold->commandes[var->i + 1])
			ft_putstr_fd(" ", 1);
		var->i++;
	}
	if (var->check == 0)
		ft_putstr_fd("\n", 1);
}

int	check_first_arg(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	if (str[0] == '-')
		i += 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (i == len)
		return (1);
	return (0);
}

int	ft_echo(t_list *hold)
{
	t_variables	var;

	var.i = 1;
	var.check = 0;
	if (!hold->commandes[1])
		printf("\n");
	else if (check_first_arg(hold->commandes[1]) && !hold->commandes[2])
		return 1;
	else
		ft_cases(hold, &var);
	return 1;
}

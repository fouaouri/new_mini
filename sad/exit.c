/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:59:35 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/24 22:59:35 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s3)
	{
		ft_putstr_fd(s3, 2);
		ft_putchar_fd('\n', 2);
	}
}

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi_atoi(char *str)
{
	unsigned char	result;
	int				i;
	int				sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (sign == -1)
		return (result = (signed char)result * sign);
	return (result * sign);
}

int	is_number(char *str)
{
	int	i;
	int	nb;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (-1);
		i++;
	}
	nb = ft_atoi_atoi(str);
	return (nb);
}

void	exit_many_arg(char *s)
{
	printf("%s\n", s);
	write(1, "bash: ", 6);
	error(s, NULL, "too many arguments");
	// g_globe.exit_status = 1;
}

void	__exit__(t_list *sep)
{
	if (sep->commandes[1] == NULL)
	{
		printf("%s\n", sep->commandes[0]);
		exit(100);
	}
	if (is_number(sep->commandes[1]) == -1)
	{
		printf("%s\n", sep->commandes[0]);
		write(1, "bash: ", 6);
		error(sep->commandes[0], sep->commandes[1], "numeric argument required");
		exit(255);
	}
	else if (sep->commandes[2])
		exit_many_arg(sep->commandes[0]);
	else
	{
		printf("%s\n", sep->commandes[0]);
		// g_globe.exit_status = is_number(cmd->commandes[1]);
		exit(10);
		// exit(g_globe.exit_status);

	}
}
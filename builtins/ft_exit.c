/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:29:15 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/12 19:29:26 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static long	nlen(long n)
{
	long	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_ltoa(long n)
{
	long	len;
	char	*ret;

	len = 0;
	if (!n)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = nlen(n);
	ret = my_malloc(len + 1);
	if (!ret)
		return (NULL);
	*(ret + len--) = '\0';
	if (n < 0)
	{
		*(ret) = '-';
		n = n * -1;
	}
	while (n)
	{
		*(ret + len--) = n % 10 + '0';
		n = n / 10;
	}
	return (ret);
}

static long ft_atol(const char *nptr)
{
	unsigned long long	n;
	int					i;
	int					sign;

	n = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		sign = 1 - 2 * (nptr[i++] == '-');
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + (nptr[i] - '0');
		i++;
	}
	return (n * sign);
}

void	ft_exit(char **args)
{
	unsigned char	exit_code;
	// long res;
	char *str;
	int	i;

	i = 0;
	if (!args[1])
	{
		dprintf(2, "exit with 0\n");
		exit(0);
	}
	if (args[2])
	{
		ft_dprintf(2, "Minishell: exit: too many arguments\n");
		g_data.exit_status = 1;
		return ;
	}
	if (!args[1][i])
	{
		ft_dprintf(2, "Minishell: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	while (args[1][i])
	{
		if (i == 0 && (args[1][i] == '+' || args[1][i] == '-'))
			i++;
		if (!ft_isdigit(args[1][i]) || !args[1][i])
		{
			ft_dprintf(2, "Minishell: %s: numeric argument required\n", args[1]);
			exit(2);
		}
		i++;
	}
	str = ft_ltoa(ft_atol(args[1]));
	if (ft_strcmp(str, args[1]))
	{
		ft_dprintf(2, "Minishell: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	else
		exit_code = ft_atol(args[1]);
	exit(exit_code);
}

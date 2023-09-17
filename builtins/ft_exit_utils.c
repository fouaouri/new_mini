/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:28:58 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 22:27:11 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

long	nlen(long n)
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

long	ft_atol(const char *nptr)
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

int	skip_zeros(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] != '0')
			break ;
		i++;
	}
	return (i);
}

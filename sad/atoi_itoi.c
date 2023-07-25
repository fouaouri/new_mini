/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_itoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:59:10 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/25 02:17:35 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *str)
{
	unsigned long int	result;
	int					sign;

	result = 0;
	sign = 1;
	while ((*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	while (ft_is_digit(*str))
	{
		result = (result * 10) + (*str - '0');
		if (result > LLONG_MAX && sign == -1)
			return (0);
		else if (result > LLONG_MAX && sign == 1)
			return (-1);
		str++;
	}
	return (result * sign);
}

int	ft_numlen(long d)
{
	int	i;

	i = 0;
	if (d == 0)
		return (1);
	if (d < 0)
	{
		i++;
		d = d * (-1);
	}
	while (d > 0)
	{
		i++;
		d = d / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	len;

	len = ft_numlen (n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
		len--;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * (-1);
	}
	while (n > 0)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len --;
	}
	return (str);
}

void	ft_list_remove_if(t_data **begin_list, char *data_ref)
{
	t_data	*cur;
	t_data	*prev;

	cur = *begin_list;
	prev = NULL;
	if (begin_list == NULL || *begin_list == NULL)
		return ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->content, data_ref, strlen1(cur->content)) == 0
			&& ft_strlen(data_ref) == strlen1(cur->content))
		{
			if (prev == NULL)
				*begin_list = cur->next;
			else
				prev->next = cur->next;
			// (free(cur->content), free(cur));
			(prev == NULL) && (cur = *begin_list);
			(prev != NULL) && (cur = prev->next);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

int	strlen1(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
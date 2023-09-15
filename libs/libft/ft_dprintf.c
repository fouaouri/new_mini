/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:22:17 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/15 19:26:59 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vdprintf(int fd, const char *str, va_list vlist)
{
	int		i;
	int		val;

	i = 0;
	val = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 'd')
				val += ft_putnbr_fd(va_arg(vlist, int), fd);
			else if (str[i] == 's')
				val += ft_putstr_fd(va_arg(vlist, char *), fd);
			else if (str[i] == '%')
				val += write(fd, "%", 1);
		}
		else
			val += write(fd, &str[i], 1);
		i++;
	}
	return (val);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	vlist;
	int		val;

	va_start(vlist, str);
	val = ft_vdprintf(fd, str, vlist);
	va_end(vlist);
	return (val);
}

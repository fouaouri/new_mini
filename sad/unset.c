/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 00:52:18 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/25 03:07:06 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_to_env_value(char *str)
{
	char	*str1;
	int		nb;

	str1 = get_env_value1(str);
	nb = ft_atoi(str1);
	free(str1);
	nb += 1;
	str1 = ft_itoa(nb);
	return (str1);
}

void	to___unset__(char **tmp, char **tmp1, char **str)
{
	*tmp = equale_value(*str);
	*tmp1 = join_to_env_value(*str);
	*str = ft_strjoin_join01(*tmp, *tmp1);
	free(*tmp1);
}

int	is_alphanum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(ft_isalpha(s[i])) && !(ft_is_digit(s[i])) && s[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	__unset__(t_list *sep, t_data **data)
{
	t_data	*tmp;
	int		i;
	int		l;

	l = 0;
	i = 1;
	tmp = (*data);
	while (sep->commandes[i])
	{
		if (is_alphanum(sep->commandes[i]))
			(error(sep->commandes[0], sep->commandes[i], "not a valid identifier"),
				l = 1);
		tmp = (*data);
		while ((tmp))
		{
			if (ft_strncmp(tmp->content, sep->commandes[i], ft_strlen(sep->commandes[i])) == 0)
			{
				ft_list_remove_if(data, sep->commandes[i]);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (l);
}

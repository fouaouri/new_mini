/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:26:57 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/27 16:53:43 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_env	*ft_new_env(char *str)
{
	t_env *node;
	char *ptr;

	node = malloc(sizeof(t_env));
	ptr = ft_strchr(str, '=');

	if (ptr)
	{
		node->key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ptr));
		node->value = ft_strdup(ptr + 1);
	}
	else
	{
		node->key = ft_strdup(str);
		node->value = NULL;
	}
	
	return (node);
}

void	ft_add_back_env(t_env **lst, t_env *node)
{
	t_env *tmp;

	tmp = *lst;

	if (*lst == NULL)
	{
		*lst = node;
		return ;
 	}

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_env	*init_env(char **env)
{
	t_env *ret;
	t_env *node;
	int i;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		// string => Key=value
		node = ft_new_env(env[i]);
		ft_add_back_env(&ret, node);
		i++;
	}

	return (ret);
}

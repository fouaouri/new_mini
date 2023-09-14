/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:53:55 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/13 19:56:12 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env(char *str)
{
	t_env	*node;
	char	*ptr;

	node = my_malloc(sizeof(t_env));
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
	node->next = NULL;
	return (node);
}

void	ft_add_back_env(t_env **lst, t_env *node)
{
	t_env	*tmp;

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
	t_env	*ret;
	t_env	*node;
	int		i;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		node = ft_new_env(env[i]);
		ft_add_back_env(&ret, node);
		i++;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:58:00 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/13 19:36:48 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	check_for_node(t_env *node, t_env *bf_node)
{
	bf_node = g_data.l_env;
	while (bf_node->next != node)
		bf_node = bf_node->next;
	bf_node->next = node->next;
	// free(node->key);
	// if (node->value)
	// 	free(node->value);
	// free(node);
}

void	ft_unset_util(t_env *node)
{
	g_data.l_env = node->next;
	// free(node->key);
	// if (node->value)
	// 	free(node->value);
	// free(node);
}

void	ft_unset(char **keys)
{
	t_env	*node;
	t_env	*bf_node;
	char	*key;
	int		i;

	i = 1;
	bf_node = NULL;
	while (keys[i])
	{
		key = keys[i++];
		if (!ft_validate_key(key))
			return ;
		node = ft_search_for_key(key);
		if (node)
		{
			if (node == g_data.l_env)
			{
				ft_unset_util(node);
				continue ;
			}
			check_for_node(node, bf_node);
		}
	}
}

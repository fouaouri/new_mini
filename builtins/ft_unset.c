/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:58:00 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/08 17:03:09 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(char **keys)
{
	t_env *node;
	t_env *bf_node;
	char *key;
	int i;

	i = 1;
	while (keys[i])
	{
		key = keys[i++];
		if (!ft_validate_key(key))
			return ;
		node = ft_search_for_key(key);
		if (node)
		{
			// check if the node is the first one
			if (node == g_data.l_env)
			{
				g_data.l_env = node->next;
				free(node->key);
				if (node->value)
					free(node->value);
				free(node);
				continue ;
			}

			bf_node = g_data.l_env;
			while (bf_node->next != node)
				bf_node = bf_node->next;
			bf_node->next = node->next;
			free(node->key);
			if (node->value)
				free(node->value);
			free(node);
		}
	}
}

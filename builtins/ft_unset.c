/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:58:00 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/04 15:49:12 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(t_env **env, char **keys)
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
		node = ft_search_for_key(env, key);
		if (node)
		{
			bf_node = *env;
			while (bf_node->next != node)
				bf_node = bf_node->next;
			bf_node->next = node->next;
			free(node->key);
			if (node->value)
				free(node->value);
			free(node);
		}
		// else
		// 	exit(0);
	}
}

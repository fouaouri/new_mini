/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:38:09 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/15 17:52:17 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*ft_add_new_env(char *str)
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

t_env	*ft_search_for_key(char *key)
{
	t_env	*node;

	node = g_data.l_env;
	while (node)
	{
		if (!ft_strcmp((node)->key, key))
			return (node);
		node = (node)->next;
	}
	return (NULL);
}

int	ft_validate_key(char *key)
{
	int	i;

	i = 0;
	if (!key)
		ft_dprintf(2, "Minishell: export: `%s': not a valid identifier\n", key);
	if (key[i] != '_' && !ft_isalpha(key[i]))
	{
		ft_dprintf(2, "Minishell: export: `%s': not a valid identifier\n", key);
		return (0);
	}
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			ft_dprintf(2, \
			"Minishell: export: `%s': not a valid identifier\n", key);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_print_env(void)
{
	t_env	*env;

	env = g_data.l_env;
	while (env)
	{
		printf("declare -x ");
		printf("%s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

void	ft_update_value(t_env *node, char *str)
{
	char	*ptr;

	if (node->value)
		free(node->value);
	node->value = NULL;
	ptr = ft_strchr(str, '=');
	if (ptr)
		node->value = ft_strdup(ptr + 1);
}

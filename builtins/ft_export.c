/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:57:54 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/05 17:19:08 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*ft_add_new_env(char *str)
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
	node->next = NULL;
	return (node);
}

t_env	*ft_search_for_key(char *key)
{
	t_env *node;
	node = g_data.l_env;

	while(node)
	{
		if (!ft_strcmp((node)->key, key))
			return (node);
		node = (node)->next;
	}
	return (NULL);
}

int	ft_validate_key(char *key)
{
	int i;

	i = 0;
	if (key[i] != '_' && !ft_isalpha(key[i]))
	{
		printf(":Minishell: export: `%s': not a valid identifier\n", key);
		return (0);
	}
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			printf(":Minishell: export: `%s': not a valid identifier\n", key);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_print_env()
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
	char *ptr;

	if (node->value)
		free(node->value);
	node->value = NULL;
	ptr = ft_strchr(str, '=');
	if (ptr)
		node->value = ft_strdup(ptr + 1);
}

void	ft_export(char **cmds)
{
	int i;
	char *key;
	t_env *node;

	if (!cmds[1])
	{
		ft_print_env();
		return ;
	}
	i = 1;
	while (cmds[i])
	{
		key = ft_strchr(cmds[i], '=');
		if (key) // NOTE: leaks
			key = ft_substr(cmds[i], 0, ft_strlen(cmds[i]) - ft_strlen(key));
		else
			key = ft_strdup(cmds[i]);
		if (ft_validate_key(key))
		{
			node = ft_search_for_key(key);
			if (node)
				ft_update_value(node, cmds[i]);
			else
			{
				node = ft_add_new_env(cmds[i]);
				ft_add_back_env(&g_data.l_env, node);
			}
		}
		free(key);
		i++;
	}
}

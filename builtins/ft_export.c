/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:57:54 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/13 12:35:46 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* ************* TODO ******************
 * NOTE; check for => export key+=valu,
 * should update the value
 * ******* TODO ****************** */

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
			ft_dprintf(2, "Minishell: export: `%s': not a valid identifier\n", key);
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
	char *pluse_key;
	char *new_value;
	char *old_value;

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
		pluse_key = ft_strchr(key, '+');
		if (!ft_strchr(cmds[i], '=') && pluse_key)
		{
			ft_dprintf(2, "Minishell: export: `%s': not a valid identifier\n", key);
			return ;
		}
		if (pluse_key && ft_strlen(pluse_key) == 1)
			key = ft_substr(key, 0, ft_strlen(key) - ft_strlen(pluse_key));
		if (ft_validate_key(key))
		{
			node = ft_search_for_key(key);
			if (pluse_key && node)
			{
				// get old value from key
				if (!node->value)
					old_value = ft_strdup("");
				else
					old_value = node->value;
				// get new value
				key = ft_strchr(cmds[i], '=');
				// printf("key: %s\n", key);
				new_value = ft_strjoin(old_value, key + 1);
				// printf("new_value: %s\n",new_value);
				old_value = ft_substr(cmds[i], 0, ft_strlen(cmds[i]) - ft_strlen(key - 1));
				// printf("old_value: %s\n",old_value);
				old_value = ft_strjoin(old_value, "=");
				cmds[i] = ft_strjoin(old_value, new_value);
				// printf("cmds: %s\n", cmds[i]);
			}
			if (node)
				ft_update_value(node, cmds[i]);
			else
			{
				// check for + key, and rm from cmds[i]
				if (pluse_key && !node)
				{
					// remove + from cmds[i]
					old_value = ft_strjoin(key, "=");
					key = ft_strchr(cmds[i], '=');
					cmds[i] = ft_strjoin(old_value, key + 1);
				}
				node = ft_add_new_env(cmds[i]);
				ft_add_back_env(&g_data.l_env, node);
			}
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:57:54 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/15 19:00:04 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_for_pluse_key(char *cmds, char *pluse_key, char *key)
{
	if (!ft_strchr(cmds, '=') && pluse_key)
	{
		ft_dprintf(2, "Minishell: export: `%s': not a valid identifier\n", key);
		g_data.exit_status = 1;
		return (-1);
	}
	return (1);
}

void	ft_export_util(t_env *node, char *key, char *pluse_key, char *cmds)
{
	char	*old_value;

	if (pluse_key && node)
	{
		if (!node->value)
			old_value = ft_strdup("");
		else
			old_value = node->value;
		cmds = check_for_pluse(cmds, old_value, key);
	}
	if (node)
	{
		key = ft_strchr(cmds, '=');
		if (!key && !pluse_key)
			return ;
		ft_update_value(node, cmds);
	}
	else
	{
		if (pluse_key && !node)
			cmds = add_new_key_after(cmds, key);
		node = ft_add_new_env(cmds);
		ft_add_back_env(&g_data.l_env, node);
	}
}

void	ft_export(char **cmds)
{
	int		i;
	char	*key;
	char	*pluse_key;
	t_env	*node;

	i = 1;
	if (print_export(cmds) == -1)
		return ;
	while (cmds[i])
	{
		key = get_key(cmds[i]);
		pluse_key = ft_strchr(key, '+');
		if (check_for_pluse_key(cmds[i], pluse_key, key) == -1)
			return ;
		if (pluse_key && ft_strlen(pluse_key) == 1)
			key = ft_substr(key, 0, ft_strlen(key) - ft_strlen(pluse_key));
		if (ft_validate_key(key))
		{
			node = ft_search_for_key(key);
			ft_export_util(node, key, pluse_key, cmds[i]);
		}
		i++;
	}
}

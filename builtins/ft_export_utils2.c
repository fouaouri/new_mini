/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:59:51 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/15 18:59:56 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*check_for_pluse(char *cmds, char *old_value, char *key)
{
	char	*new_value;

	key = ft_strchr(cmds, '=');
	new_value = ft_strjoin(old_value, key + 1);
	old_value = ft_substr(cmds, 0, ft_strlen(cmds) - ft_strlen(key - 1));
	old_value = ft_strjoin(old_value, "=");
	cmds = ft_strjoin(old_value, new_value);
	return (cmds);
}

char	*add_new_key_after(char *cmds, char *key)
{
	char	*old_value;

	old_value = ft_strjoin(key, "=");
	key = ft_strchr(cmds, '=');
	cmds = ft_strjoin(old_value, key + 1);
	return (cmds);
}

char	*get_key(char *cmd)
{
	char	*key;

	key = ft_strchr(cmd, '=');
	if (key)
		key = ft_substr(cmd, 0, ft_strlen(cmd) - ft_strlen(key));
	else
		key = ft_strdup(cmd);
	return (key);
}

int	print_export(char **cmds)
{
	if (!cmds[1])
	{
		ft_print_env();
		return (-1);
	}
	return (1);
}

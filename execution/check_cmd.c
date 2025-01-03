/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:17:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 18:32:12 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*check_valid_path(char *cmd)
{
	int	ret;

	if (cmd[0] == '.' || cmd[0] == '/')
	{
		ret = access(cmd, F_OK);
		if (!ret)
		{
			ret = access(cmd, X_OK);
			if (!ret)
				return (cmd);
			else
				return ("p");
		}
	}
	return (NULL);
}

char	*check_cmd(char **path, char *cmd)
{
	char	*tmp;
	int		ret;

	if (!cmd || !cmd[0])
		return (NULL);
	if (check_valid_path(cmd))
		return (cmd);
	if (!path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		tmp = ft_strjoin(tmp, cmd);
		ret = access(tmp, X_OK);
		if (!ret)
			return (tmp);
		path++;
	}
	ret = access(cmd, X_OK);
	if (!ret)
		return (cmd);
	return (NULL);
}

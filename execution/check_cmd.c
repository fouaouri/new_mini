/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:17:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/07 18:18:05 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

char	*check_cmd(char **path, char *cmd)
{
	char	*tmp;
	int		ret;

	/* NOTE: checking for valid cmd */
	if (!cmd)
		return NULL;

	// checking for valid path => ./cmd or /bin/cmd
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		ret = access(cmd, F_OK);
		if (!ret)
			return (cmd);
		else
			return (NULL);
	}
	// ret = access(cmd + 1, X_OK);
	// if (!ret)
	// 	return (cmd);
	// else if (ft_strchr(cmd, '/'))
	// 	return (NULL);

	// checking for valid path => path + cmd
	if (!path)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		tmp = ft_strjoin(tmp, cmd);
		// leaks
		ret = access(tmp, X_OK);
		if (!ret)
			return (tmp);
		free(tmp);
		path++;
	}
	return (NULL);
}

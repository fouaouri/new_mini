/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:17:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/09 22:27:40 by melhadou         ###   ########.fr       */
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
		{
			ret = access(cmd, X_OK);
			if (!ret)
				return (cmd);
			else
				return ("p");
		}
		else
			return (NULL);
	}
	// checking for valid path => path + cmd
	if (!path)
		return (NULL);
	/* NOTE: checking for valid cmd */
	if (!cmd[0])
		return NULL;
	// ret = access(cmd, F_OK); //file
	ret = access(cmd, X_OK);//executable
	if (!ret)
		return (cmd);
	else if (ft_strchr(cmd, '/'))
		return NULL;
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		tmp = ft_strjoin(tmp, cmd);
		// leaks
		ret = access(tmp, X_OK);
		if (!ret)
		{
			return (tmp);
		}
		free(tmp);
		path++;
	}
	return (NULL);
}

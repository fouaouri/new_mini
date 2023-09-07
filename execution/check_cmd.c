/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:17:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/07 16:33:16 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

char	*check_cmd(char **path, char *cmd)
{
	char	*tmp;
	int		ret;

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
		ret = access(tmp, F_OK);
		if (!ret)
		{
			return (tmp);
		}
		free(tmp);
		path++;
	}
	return (NULL);
}

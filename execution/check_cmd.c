/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:17:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/07 16:26:30 by melhadou         ###   ########.fr       */
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
	if (
		!ft_strcmp(cmd, "//")
		|| !ft_strcmp(cmd, "/..")
		|| !ft_strcmp(cmd, "/.")
		|| !ft_strcmp(cmd, "~") 
		|| !ft_strcmp(cmd, "~/")
		)
		return ("d");
	ret = access(cmd, F_OK);
	if (!ret)
		return (cmd);
	else if (ft_strchr(cmd, '/'))
		return (NULL);

	if (!path)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		tmp = ft_strjoin(tmp, cmd);
		// leaks
		ret = access(tmp, F_OK);
		if (!ret)
			return (tmp);
		free(tmp);
		path++;
	}
	return (NULL);
}

// char	*check_cmd(char **path, char *cmd)
// {
// 	char	*tmp;
// 	int		ret;

// 	if (!cmd)
// 		return (NULL);
// 	/* NOTE: checking for valid cmd */
// 	
	// if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
	// 	return (NULL);
	// if (!ft_strcmp(cmd, "./") || !ft_strcmp(cmd, "../"))
	// 	return (NULL);
	// if (!ft_strcmp(cmd, "/") || !ft_strcmp(cmd, "//") || !ft_strcmp(cmd, "/.") || !ft_strcmp(cmd, "/.."))
	// 	return ("d");
	// if (!ft_strcmp(cmd, "~") || !ft_strcmp(cmd, "~/"))
	// 	return (NULL);
	// if(!ft_strcmp(cmd, " "))
	// 	return (NULL);
	// if (!ft_strcmp(cmd, ""))
	// 	return (NULL);
// 	
// 	ret = access(cmd, F_OK);
// 	if (!ret)
// 		return (cmd);
// 	else if (ft_strchr(cmd, '/'))
// 		return (NULL);

// 	// if (!path)
// 	// 	return (NULL);
// 	while (*path)
// 	{
// 		tmp = ft_strjoin(*path, "/");
// 		tmp = ft_strjoin(tmp, cmd);
// 		// leaks
// 		ret = access(tmp, F_OK);
// 		if (!ret)
// 			return (tmp);
// 		free(tmp);
// 		path++;
// 	}
// 	return (NULL);
// }

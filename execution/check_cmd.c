/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:17:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/23 12:47:16 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

// i needd to join the cmd from t_node and check if its exisct or not using acces function
char	*check_cmd(char **path, char *cmd)
{
	char	*tmp;
	int		ret;

	ret = access(cmd, F_OK);
	if (!ret)
		return (cmd);
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

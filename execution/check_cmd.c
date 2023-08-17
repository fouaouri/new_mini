/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:17:31 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/16 17:55:07 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

// i needd to join the cmd from t_node and check if its exisct or not using acces function
int check_cmd(char *path, char *cmd)
{
	char	*tmp;
	int		ret;
	tmp = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp, cmd);
	ret = access(tmp, F_OK);
	free(tmp);
	return (ret);
}

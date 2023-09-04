/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:27:02 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/04 16:08:15 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

char	**parse_path(t_env **env_list)
{
	char	**res;
	t_env	*path;

	res = NULL;
	path = ft_search_for_key(env_list, "PATH");
	if (path)
		res = ft_split(path->value, ':');
	// free(path);
	return (res);
}

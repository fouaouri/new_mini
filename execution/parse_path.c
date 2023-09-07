/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:27:02 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/07 14:37:20 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

char	**parse_path()
{
	char	**res;
	t_env	*path;

	res = NULL;
	path = ft_search_for_key("PATH");
	if (path)
		res = ft_split(path->value, ':');
	return (res);
}

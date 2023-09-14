/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:27:02 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/14 17:26:43 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**parse_path(void)
{
	char	**res;
	t_env	*path;

	res = NULL;
	path = ft_search_for_key("PATH");
	if (path)
		res = ft_split(path->value, ':');
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:27:02 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/15 22:23:01 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>

char **parse_path(char *path)
{
	char **res;
	res = ft_split(path, ':');
	return (res);
}

int main(int argc, char *argv[])
{
	char **path;

	char *pp = getenv("PATH");
	if (!pp)
		return 0;
	path = parse_path(pp);
	while (*path)
	{
		printf("%s\n", *path);
		path++;
	}
	return 0;
}

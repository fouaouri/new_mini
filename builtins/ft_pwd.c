/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:18:34 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/11 21:49:04 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    ft_pwd()
{
	char *cwd;
	char str[1024];
	char *string;
	char *path;
	t_env *node;

	cwd = getcwd(str, sizeof(str));
	if(cwd)
	{
		string = ft_strdup(cwd);
		printf("%s\n", string);
	}
	else
	{
		// printf("titiim\n");
		// should work with our env struct
		node = ft_search_for_key("PWD");
		if (node)
		{
			path = node->value;
			if(path)
				printf("%s\n", path);
			else
				return ;
		}
		else
			return ;
	}
}

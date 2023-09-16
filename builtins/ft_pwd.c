/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:18:34 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/16 18:19:22 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(void)
{
	char	*cwd;
	char	*path;
	t_env	*node;

	cwd = getcwd(NULL, 0);
	if (cwd)
		printf("%s\n", cwd);
	else
	{
		node = ft_search_for_key("PWD");
		if (node)
		{
			path = node->value;
			if (path)
				printf("%s\n", path);
			else
				return ;
		}
		else
			return ;
	}
	free(cwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/18 21:47:56 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int ac, char **av)
{
	// char **path;
	// t_list shell;
	// 

	// char *pp = getenv("PATH");
	// if (!pp)
	// 	return 0;
	// path = parse_path(pp);
	// while (*path)
	// {
	// 	printf("%s\n", *path);
	// 	printf("ret => %s\n",check_cmd(*path, "ls"));
	// 	path++;
	// }
	
	// should test heredoc. and open files with the propriat path and make sure that parsing of fatima is working
	(void)ac;
	ft_heredoc(av[1]);
}

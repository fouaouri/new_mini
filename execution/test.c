/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:15:06 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/23 16:14:56 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	// int i;
	t_read	*readline;
	t_list	**hold;

	readline = malloc(sizeof(t_read));
	while (ac == 1)
	{
		hold = parsing(readline, env);
		(*hold)->outfile = 1;
		(*hold)->infile = 0;
		while((*hold) != NULL)
		{
			// calling exection function
			if ((*hold)->type)
				handle_files((*hold));
			exec_one_cmd((*hold), env);
			// i = 0;
			// while((*hold)->commandes[i])
			// {
			// 	printf("commandes :%d = %s\n", i,(*hold)->commandes[i]);
			// 	i++;	
			// }
			// i = 0;
			//  while((*hold)->file_name[i])
			//  {
			//  	printf("file_name :%d = %s\n", i,(*hold)->file_name[i]);
			// 	i++;
			//  }
			// i = 0;
			// while ((*hold)->type[i])
			// 	printf("type : %s\n", (*hold)->type[i++]);
			(*hold) = (*hold)->next;
		}
	}
}

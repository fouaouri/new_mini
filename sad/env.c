/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhachab <nkhachab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:56:05 by nkhachab          #+#    #+#             */
/*   Updated: 2023/07/21 17:07:10 by nkhachab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	**array_env(char **env, int j)
{
	char	**p;
	int		i;
	int		len;

	len = 0;
	i = 0;
	p = malloc(sizeof(char *) * 3);
	while (env[j][i] != '=')
		i++;
	while (env[j][len])
		len++;
	p[0] = ft_substr(env[j], 0, i);
	p[1] = ft_substr(env[j], i + 1, len);
	p[2] = NULL;
	return (p);
}

void	print_env(t_env *lst)
{
		while(lst)
		{
			printf("%s", lst->key);
			if(lst->data)
				printf("=%s", lst->data);
			printf("\n");
			lst=lst->next;
		}
}

void env_func(t_env *lst, char **env)
{
	int i;

	i = 0;
 	lst = NULL;
    while(env[i])
    {
        char **p = array_env(env, i);
		ft_add_back_env(&lst, ft_lstnew_env(p[0], p[1]));
		i++;
    }
	print_env(lst);
}


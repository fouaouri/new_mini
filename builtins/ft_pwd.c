/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:18:34 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/09 17:39:57 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    ft_pwd()
{
    char *cwd;
    char str[1024];
    char *string;
    char *path;

    cwd = getcwd(str, sizeof(str));
    if(cwd)
    {
        string = ft_strdup(cwd);
        printf("%s\n", string);
    }
    else
    {
        printf("titiim\n");
        path = getenv("PWD");
        if(path)
            printf("%s\n", path);
        else
            return ;
    }
}
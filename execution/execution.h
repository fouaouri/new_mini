/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:26:36 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/18 21:47:28 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../parsing/minishell.h"
# include "../libs/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

enum {
	SUCCESS = 1,
	ERROR = -1,
};

// execution
char	**parse_path(char *path);
char	*check_cmd(char *path, char *cmd);
int ft_heredoc(char *dilimiter);

#endif

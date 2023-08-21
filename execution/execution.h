/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:26:36 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/20 21:02:31 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../parsing/minishell.h"
# include "../libs/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

enum {
	SUCCESS = 1,
	ERROR = -1,
	// errors types
	FILE_NOT_EXIST = -2,
	PERSMISSION_DENIED = -3,
};

// execution
char	**parse_path(char *path);
char	*check_cmd(char *path, char *cmd);

// heredoc section
int	ft_heredoc(char *dilimiter);

// error section
int ft_error(int err_id, char *file_name);

// files execution
int	check_file_acces(char *file);
int handle_files(t_list *node);
#endif

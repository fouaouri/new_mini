/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:26:36 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/03 19:27:00 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/minishell.h"
# include "../libs/libft/libft.h"
# include "../builtins/builtins.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

enum {
	SUCCESS = 1,
	ERROR = -1,
	// errors types
	FILE_NOT_EXIST = -2,
	PERSMISSION_DENIED = -3,
};

// execution
char	**parse_path(char *path);
char	*check_cmd(char **path, char *cmd);

// exec utils
int	handle_heredoc(t_list *node);
int	wait_childs(t_list *node);
void	close_fd(int in_fd, int out_fd);
void	ft_dup2(int in_fd, int out_fd);

// heredoc section
int	ft_heredoc(char *dilimiter);

// error section
int ft_error(int err_id, char *file_name);

// files execution
int	find_file_type(char **type, char *t);
int	check_infile_acces(char *file);
int	check_outfile_acces(char *file);
int handle_files(t_list *node);

// exec function
void	exec_one_cmd(t_list *node, char **env);
void	exec_cmd(t_list *node, char **env, t_env **env_list);
// void	exec_cmd(t_list *node, char **env);

// exuction flow functions
// int	execute(t_list *node,char **env);
int	execute(t_list *node,char **env, t_env **env_list);

// free utils
void	free_list(t_list **node);


// signla handlers
void	ctl_c_handler(int sig);

#endif

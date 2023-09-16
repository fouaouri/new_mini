/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:26:36 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/16 22:04:04 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/minishell.h"
# include "../libs/libft/libft.h"
# include "../builtins/builtins.h"
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

enum {
	SUCCESS = 1,
	ERROR = -1,
	FILE_NOT_EXIST = -2,
	PERSMISSION_DENIED = -3,
};

/* **** Void Function ****** */
void	run_builtins_pipe(t_list *node);
void	close_fd(int in_fd, int out_fd);
void	ft_dup2(int in_fd, int out_fd);
void	heredoc_handler(t_read *readline, t_env *l_env, int p_fd[2], char *dilimiter);
void	ft_free(char **str);
void	free_list(t_list **node);
void	ctl_c_handler(int sig);
void	set_hold(t_list *hold);
void	run_heredoc(t_list **hold, t_list *current);
void	sig_handler(void);
void	exec_in_child(t_list *node, char **env, char *cmd_full_path);

/* **** Function returuning char ****** */
char	**parse_path(void);
char	*check_cmd(char **path, char *cmd);
char	*check_valid_path(char *cmd);
char	**create_env(void);
char	*ft_concat(char *s1, char c, char *s2);
char	*full_path(t_list *node);

/* **** Function returuning int ****** */
int	handle_heredoc(t_read *readline, t_env *l_env, t_list *node);
int		wait_childs(t_list *node);
int		ft_lst_size(void);
int	ft_heredoc(t_read *readline, t_env *l_env, char *dilimiter);
int		run_in_parent(int p_fd[2], int pid);
int		ft_error(int err_id, char *file_name);
int		find_file_type(char **type, char *t);
int		check_infile_acces(char *file);
int		check_outfile_acces(char *file);
int		handle_files(t_list *node);
int		exec_cmd(t_list *node);
int		execute_builtins(t_list *node, char *builtin);
int		is_builtins(char *builtin);
int		execute(t_list *node);
int		run_builtin(t_list *current);
int		run_execution(t_list *current, t_list **hold);
int		run_minishell(int ac, t_read *readline, t_env *l_env, t_list *current);
int		run_minishell_util(t_read *readline, t_env *l_env,t_list *current, t_list **hold);
int		check_for_valid_cmd(t_list *node);
int		open_append(t_list *node, int i);
int		open_heredoc(t_list *node, int i);
int		open_outfiles(t_list *node, int i);
int		open_infiles(t_list *node, int i);

#endif

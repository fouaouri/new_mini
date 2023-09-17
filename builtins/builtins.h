/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:29:38 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 22:27:47 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libs/libft/libft.h"
# include "../parsing/minishell.h"

void	ft_unset(char **keys);
void	ft_env(void);
void	ft_pwd(void);
void	ft_exit(char **args);
void	check_pwd(t_env *pwd_env, char *pwd, char *oldpwd);
void	ft_update_value(t_env *node, char *str);
void	ft_print_env(void);
void	ft_export_util(t_env *node, char *key, char *pluse_key, char *cmds);
t_env	*ft_search_for_key(char *key);
t_env	*ft_add_new_env(char *str);
char	*ft_ltoa(long n);
char	*check_for_pluse(char *cmds, char *old_value, char *key);
char	*add_new_key_after(char *cmds, char *key);
char	*get_key(char *cmd);
int		check_if_zeros(char *arg);
int		ft_cd(char **args);
int		ft_echo(t_list *hold);
int		ft_export(char **cmds);
int		skip_zeros(char *str);
int		ft_validate_key(char *key);
int		check_args(char **args);
int		check_access_status(int status, char **args);
int		change_dir(char *args, char *pwd, char *oldpwd, t_env *pwd_env);
int		check_home(t_env *home, t_env *pwd_env, char *pwd, char *oldpwd);
int		valid_arg(char *arg);
int		print_export(char **cmds);
int		ft_validate_key(char *key);
long	nlen(long n);
long	ft_atol(const char *nptr);
#endif

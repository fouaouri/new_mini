/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:29:38 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/09 22:23:36 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libs/libft/libft.h"
# include "../parsing/minishell.h"

void	ft_update_value(t_env *node, char *str);
void	ft_unset(char **keys);
t_env	*ft_search_for_key(char *key);
t_env	*ft_add_new_env(char *str);
int		ft_validate_key(char *key);
void	ft_cd(char **args);
void	ft_pwd();
void	ft_echo(t_list *hold);
void	ft_env();
void	ft_exit(char **args);
void	ft_export(char **cmds);
#endif

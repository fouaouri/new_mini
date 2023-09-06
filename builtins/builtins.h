/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:29:38 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/06 21:44:42 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libs/libft/libft.h"
# include "../parsing/minishell.h"
void	ft_exit(char **args);
void	ft_export(char **cmds);
void	ft_update_value(t_env *node, char *str);
void	ft_unset(char **keys);
void	ft_env();
t_env	*ft_search_for_key(char *key);
t_env	*ft_add_new_env(char *str);
int	ft_validate_key(char *key);
void	ft_cd(char **args);
#endif

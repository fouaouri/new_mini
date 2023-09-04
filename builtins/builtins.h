/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:29:38 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/04 15:40:54 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libs/libft/libft.h"
# include "../parsing/minishell.h"
void	ft_exit(char **args);
void	ft_export(t_env **env, char **cmds);
t_env	*ft_search_for_key(t_env **env, char *key);
t_env	*ft_add_new_env(char *str);
void	ft_update_value(t_env *node, char *str);
int	ft_validate_key(char *key);
void	ft_unset(t_env **env, char **keys);
#endif

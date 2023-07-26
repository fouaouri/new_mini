/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhachab <nkhachab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:03:50 by nkhachab          #+#    #+#             */
/*   Updated: 2023/07/19 19:49:19 by nkhachab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include<stdlib.h>
# include<unistd.h>
# include<limits.h>
# include<stdio.h>
# include<string.h>
#include"minishell.h"


size_t	ft_strlen(const char *str)
{
	size_t	i;
	if(!str)
		return(0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;
	if(!s1)
		return(NULL);
	str = malloc(sizeof(char) * (ft_strlen((char *)s1) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	len_env(char **en)
{
	int	i;

	i = 0;
	while (en[i])
		i++;
	return (i);
}

t_env	*ft_lstnew_env(char *s1, char *s2)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if(!s1)
		env->key = NULL;
	else
		env->key = ft_strdup(s1);
	if(!s2)
		env->data = NULL;
	else
		env->data = ft_strdup(s2);
	env->next = NULL;
	return (env);
}

t_env	*ft_last_env(t_env **list)
{
	t_env	*tmp;

	tmp = (*list);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_add_back_env(t_env **lst, t_env *new)
{
	t_env	*tem;

	if (!*lst)
		*lst = new;
	else
	{
		tem = ft_last_env(lst);
		tem->next = new;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s1;
	char	*sa;

	s1 = (char *)s;
	i = 0;
	if (!s1)
		return (0);
	if (start >= ft_strlen((char *)s1))
		return (ft_strdup("\0"));
	if (len > ft_strlen(s1) - start)
		len = ft_strlen(s1) - start;
	sa = malloc(sizeof(char) *(len + 1));
	if (!sa)
		return (0);
	while (i < len && s1[i] != '\0')
	{
		sa[i++] = s1[start++];
	}
	sa[i] = '\0';
	return (sa);
}
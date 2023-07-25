/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:02:02 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/25 02:12:49 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//***
int	ft_strlen_len(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
//***
char	*ft_strjoin_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen_len(s1) + ft_strlen_len(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
	{
		if (i <= ft_strlen_len(s1))
			str[i] = s1[i];
	}
	j = -1;
	while (s2 && s2[++j])
	{
		if (i < ft_strlen_len(s1) + ft_strlen_len(s2))
			str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*get_env(char *s, t_data **env)
{
	t_data	*tmp;
	char	*str;

	if (!(*env)->content)
		return (NULL);
	tmp = *env;
	str = ft_calloc(1, 1);
	while (tmp)
	{
		if (ft_strncmp(s, tmp->content, ft_strlen(s)) == 0)
		{
			str = ft_strjoin_join(str, tmp->content + ft_strlen(s) + 1);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		return (free(str), NULL);
	return (str);
}

// char	*getsecondlast(char *s)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 		i++;
// 	i -= 1;
// 	while (i > 0 && s[i] != '/')
// 		i--;
// 	str = malloc(i + 1);
// 	while (j < i)
// 	{
// 		str[j] = s[j];
// 		j++;
// 	}
// 	str[j] = '\0';
// 	return (str);
// }

char	*get_content(char *str)
{
	char	*s1;
	char	*s2;

	s1 = str;
	s2 = __pwd__();
	str = ft_strjoin("PWD=", s2);
	(free(s1), free(s2));
	return (str);
}

void	oldpwd_from_env(char *str, t_data **data)
{
	t_data	*tmp;
	int		count;
	char	*s1;

	count = 0;
	tmp = *data;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "OLDPWD", 6) == 0)
		{
			s1 = tmp->content;
			tmp->content = ft_strjoin("OLDPWD=", str);
			free(s1);
			count++;
		}
		else if (ft_strncmp(tmp->content, "PWD=", 4) == 0)
		{
			tmp->content = get_content(tmp->content);
			count++;
		}
		if (count == 2)
			break ;
		tmp = tmp->next;
	}
}

int	get_cd_d_point(t_data **data)
{
	char	*oldpwd;

	oldpwd = __pwd__();
	chdir("..");
	if ((*data)->content)
		oldpwd_from_env(oldpwd, data);
	free(oldpwd);
	return (1);
}

int	empty_cmd(t_list *sep, t_data **data)
{
	char	*pwd;
	char	*ennv;

	pwd = __pwd__();
	ennv = get_env("HOME", data);
	if (!ennv)
	{
		free(pwd);
		error("bash", sep->commandes[0], "HOME not set");
		return (0);
	}
	chdir(ennv);
	oldpwd_from_env(pwd, data);
	(free(ennv), free(pwd));
	return (1);
}

int	get_cd_d_point1(t_list *sep, t_data **data)
{
	char	*d_pwd;
	int		i;

	i = 0;
	d_pwd = __pwd__();
	oldpwd_from_env(d_pwd, data);
	i = chdir(sep->commandes[1]);
	if (i == -1)
	{
		error(sep->commandes[0], sep->commandes[1], "No such file or directory");
		free(d_pwd);
		return (1);
	}
	free(d_pwd);
	return (1);
}

int	__cd__(t_list *sep, t_data **data)
{
	char	*d_pwd;

	if (ft_strcmp(sep->commandes[0], "CD") == 0)
		return (0);
	if (sep->commandes[1] == NULL)
		return (empty_cmd(sep, data));
	else
	{
		if (ft_strncmp(".", sep->commandes[1], 1) == 0 && sep->commandes[1][1] == '\0')
		{
			d_pwd = null_buffer();
			if (!d_pwd)
				ft_putstr_fd("cd: error retrieving current directory: \
					getcwd: cannot access\
					parent directories: No such file or directory\n", 2);
			else
				free(d_pwd);
			return (1);
		}
		else if (ft_strncmp("..", sep->commandes[1], 2) == 0 && sep->commandes[1][2] == '\0')
			return (get_cd_d_point(data));
		else
			return (get_cd_d_point1(sep, data));
	}
	return (0);
}
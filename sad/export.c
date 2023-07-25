#include "minishell.h"

void	error01(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s3)
	{
		ft_putstr_fd(s3, 2);
		ft_putchar_fd('\n', 2);
	}
	// g_globe.exit_status = 1;
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	special_characters(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalpha(str[i])) && !(ft_is_digit(str[i])) && str[i] != '='
			&& (str[i] != '_') && (str[i] != '+'))
			return (0);
		i++;
	}
	return (1);
}

int	get_one_or_zero(char *str, t_data **data, int l)
{
	t_data	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, l) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	*ft_strjoin_join01(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		k;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	p = (char *)malloc(sizeof(char) * (i + ft_strlen(s2) + 2));
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i] && s1[i] != '=')
		p[i] = s1[i];
	p[i++] = '=';
	k = 0;
	while (s2[k])
	{
		p[k + i] = s2[k];
		k++;
	}
	p[k + i] = '\0';
	free(s1);
	return (p);
}

int	search_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*equale_value(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = search_for_equal(s);
	if (i == 0)
		return (NULL);
	str = malloc(i + 1);
	i = 0;
	while (s[i] != '=')
		str[i++] = s[j++];
	str[i] = '\0';
	return (str);
}

char	*split_str_with_plus(char *s)
{
	char	*str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (s[i] != '+')
		i++;
	str = malloc(i + 1);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	str = ft_strjoin_join(str, s + i + 1);
	return (str);
}

// int	help_exp(char *s, int flag)
// {
// 	int	i;

// 	i = 0;
// 	if (!ft_isalpha(s[0]) && s[0] != '_')
// 	{
// 		if (flag == 0)
// 			free(s);
// 		return (1);
// 	}
// 	while (s[i])
// 	{
// 		if (!(ft_isalpha(s[i])) && !(ft_is_digit(s[i])) && s[i] != '_'
// 			&& (s[i] != '='))
// 		{
// 			if (flag == 0)
// 				free(s);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	check_exported1(char *s, int l)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		if (l == 0)
			free(s);
		return (1);
	}
	while (s[i])
	{
		if (!(ft_isalpha(s[i])) && !(ft_is_digit(s[i])) && s[i] != '_'
			&& (s[i] != '='))
		{
			if (l == 0)
				free(s);
			return (1);
		}
		i++;
	}
	return (0);
}

// int	checkchar(char *str)
// {
// 	int		i;
// 	char	*s;
// 	int		flag;

// 	flag = 0;
// 	i = 0;
// 	s = equale_value(str);
// 	if (s == NULL)
// 	{
// 		(s = str);
// 		(flag = 1);
// 	}
// 	if (help_exp(s, flag))
// 		return (1);
// 	if (flag == 0)
// 		free(s);
// 	return (0);
// }
int	check_exported(char *str)
{
	int		i;
	int		l;
	char	*s;

	l = 0;
	i = 0;
	s = equale_value(str);
	if (s == NULL)
	{
		(s = str);
		(l = 1);
	}
	if (check_exported1(s, l))
		return (1);
	if (l == 0)
		free(s);
	return (0);
}

char	*get_env_value1(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	while (s[j] != '=')
		j++;
	str = malloc(i - j);
	j++;
	i = 0;
	while (s[j])
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	get_env_value(char *s, t_data **data, int *check)
{
	t_data	*tmp;
	char	*str;

	tmp = *data;
	str = get_env_value1(s);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, s, *check) == 0
			&& ((ft_strncmp(tmp->content + *check, "=", 1) == 0)
				|| !(tmp->content[*check])))
		{
			tmp->content = ft_strjoin_join01(tmp->content, str);
			free(str);
			return (0);
		}
		tmp = tmp->next;
	}
	free(str);
	return (1);
}

int	checkingifexist(char *s, t_data **data)
{
	t_data	*tmp;
	char	*str;
	int		len;

	len = 0;
	str = equale_value(s);
	tmp = *data;
	if (!(tmp))
		return (1);
	while (tmp)
	{
		if (!str)
			len = ft_strlen(s);
		else
			len = ft_strlen(str);
		if (ft_strncmp(tmp->content, s, len) == 0
			&& strlen1(tmp->content) == ft_strlen(s))
		{
			free(str);
			return (0);
		}
		tmp = tmp->next;
	}
	free(str);
	return (1);
}

void	help_export(t_data **data, char *s, int *check1, int *i)
{
	if (check_exported(s) == 1)
		error01("export", s, "not a valid identifier");
	else if (get_one_or_zero(s, data, *check1) == 0)
	{
		if (get_env_value(s, data, check1) == 1)
			ft_lstadd_back1(data, ft_lstnew1(s));
		// g_globe.exit_status = 0;
	}
	else if (checkingifexist(s, data) == 0)
	{
		(*i)++;
		// g_globe.exit_status = 0;
	}
	else
	{
		ft_lstadd_back1(data, ft_lstnew1(s));
		// g_globe.exit_status = 0;
	}
}
int	equal(char *s)
{
	int		i;
	int		len;
	char	*str;

	str = equale_value(s);
	if (!str)
		len = 0;
	else
	{
		len = ft_strlen(str);
		free(str);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == '+')
		{
			if (s[i + 1] == '=')
				return (i);
			else if (i < len)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	free_exp(char *s, int i)
{
	free(s);
	return (i);
}
//**********************************************************
int	checknotexist(char *s, t_data **data, int len)
{
	t_data	*tmp;
	char	*str;

	len = 0;
	str = equale_value(s);
	tmp = *data;
	while (tmp)
	{
		if (!str)
			len = ft_strlen(s);
		else
		{
			if (equal(s) != 0)
				len = ft_strlen(str) - 1;
			else
				len = ft_strlen(str);
		}
		if (ft_strncmp(tmp->content, s, len) == 0)
			return (free_exp(str, 0));
		tmp = tmp->next;
	}
	return (free_exp(str, -1));
}
void	smt(int *i, int *check, int *flag)
{
	ft_putchar_fd('=', 1);
	if (*flag == 0)
		ft_putchar_fd('"', 1);
	(*i)++;
	*check = 1;
	*flag = 1;
}
void	checktossawiwzid(char *s)
{
	int	i;
	int	check;
	int	flag;

	i = 0;
	check = 0;
	flag = 0;
	ft_putstr_fd("declare -x ", 1);
	while (s[i])
	{
		if (s[i] != '=')
			ft_putchar_fd(s[i++], 1);
		else
			smt(&i, &check, &flag);
	}
	if (s[i] == '\0' && check == 1)
		ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
}
int	checktossawi(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
void	joining(char *s, t_data **data, int *check)
{
	t_data	*tmp;
	char	*str;

	tmp = *data;
	str = get_env_value1(s);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, s, *check) == 0
			&& (tmp->content[*check] == '=' || tmp->content[*check] == '\0'))
		{
			if (!checktossawi(tmp->content))
				tmp->content = ft_strjoin_join(tmp->content, str);
			else
			{
				tmp->content = ft_strjoin_join01(tmp->content, "=");
				tmp->content = ft_strjoin_join01(tmp->content, str);
			}
		}
		tmp = tmp->next;
	}
	free(str);
}

void	export_2(t_data **data, char *s, int *check)
{
	char	*str;

	if (checknotexist(s, data, *check) == -1)
	{
		
		str = split_str_with_plus(s);
		ft_lstadd_back1(data, ft_lstnew1(str));
		// g_globe.exit_status = 0;
		free(str);
	}
	else
	{
		joining(s, data, check);
		// g_globe.exit_status = 0;
	}
}

void	iniiiit(t_data_data *info)
{
	info->check = 0;
	info->check1 = 0;
	info->i_exp = 1;
}

int	check_exported01(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+')
		return (0);
	while (s[i])
	{
		if (!(ft_isalpha(s[i])) && !(ft_is_digit(s[i])) && s[i] != '_'
			&& ((s[i] == '=') && ft_strlen(s) != 1))
			return (1);
		i++;
	}
	return (0);
}








int	returntossawi(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}














void	printenvwithx(t_data **data)
{
	t_data	*tmp;

	tmp = *data;
	while (tmp)
	{
		checktossawiwzid(tmp->content);
		tmp = tmp->next;
	}
}

void	iniiiit1(t_data_data *info, char *s)
{
	info->check = equal(s);
	info->check1 = search_for_equal(s);
}

int	export_3(t_data **data, char *s)
{
	if (!s[0])
	{
		error01("export", s, "not a valid identifier");
		return (1);
	}
	else if (checkingifexist(s, data) == 0)
	{
		// g_globe.exit_status = 0;
		return (1);
	}
	else
	{
		if (check_exported(s) == 1)
		{
			error01("export", s, "not a valid identifier");
			return (1);
		}
		else
		{
			ft_lstadd_back1(data, ft_lstnew1(s));
			// g_globe.exit_status = 0;
		}
	}
	return (0);
}

void	export_4(t_data **data, t_list *p, t_data_data *info)
{
	while (p->commandes[info->i_exp])
	{
		iniiiit1(info, p->commandes[info->i_exp]);
		if (info->check == 0 && checktossawi(p->commandes[info->i_exp]) == 1)
		{
			
			if (export_3(data, p->commandes[info->i_exp]) == 1)
			{
				info->i_exp++;
				continue ;
			}
		}
		else if (info->check == -1)
		{
			
			if (check_exported(p->commandes[info->i_exp]) == 1)
			{
				error01(p->commandes[0], p->commandes[info->i_exp],
					"not a valid identifier");
			}
		}
		else if (info->check == 0 && checktossawi(p->commandes[info->i_exp]) == 0)
		{
			
			help_export(data, p->commandes[info->i_exp], &info->check1, &info->i_exp);
		}
		else if (info->check != 0 && info->check != -1)
		{
			
			export_2(data, p->commandes[info->i_exp], &info->check);

		}
		info->i_exp++;
	}
}

int	ft_lstsize(t_data *lst)
{
	int	total;

	total = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		total++;
	}
	return (total);
}
t_data	*sort_list(t_data *lst)
{
	char	*swap;
	t_data	*tmp;

	tmp = lst;
	if (ft_lstsize(tmp) < 1)
		return (lst);
	while (lst->next != NULL)
	{
		if (ft_strcmp(lst->content, lst->next->content) > 0)
		{
			swap = lst->content;
			lst->content = lst->next->content;
			lst->next->content = swap;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}
void	__export__(t_list *p, t_data **data, t_data_data *info)
{
	iniiiit(info);
	if (p->commandes[1] == NULL)
	{
		(sort_list(*data), printenvwithx(data));
		// g_globe.exit_status = 0;
	}
	else
		export_4(data, p, info);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:33:48 by fouaouri          #+#    #+#             */
/*   Updated: 2023/08/31 17:03:14 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
#	include <readline/readline.h>
#	include <readline/history.h>
// local includes
# include "../libs/libft/libft.h"

// golobal variable for exit status

extern int exit_status;
// int exit_status = 0;

typedef struct s_variables
{
	int		i;
	int		j;
	int		k;
	int		e;
	int		count;
	int		alloc;
	int		check;
	int		space;
	int		s_d;
	int		len;
	char	*str1;
}	t_variables;

typedef struct s_list
{
	char			**file_name;
	char			**commandes;
	char			**type;
	// execution vars
	int	infile;
	int	outfile;
	int	pid;
	struct s_list	*next;
}	t_list;

typedef struct s_read
{
	char	*skip_zero;
	char	*new_input;
	char	*input;
	char	*input1;
	char	*replace;
	char	*put_zero;
	char	*add_spaces;
	char	*string;
	char	**split;
	char	**arr;
	char	*exp;
	char	**split_arr;
	char	**arr1;
	int		exit_status;
}	t_read;

typedef struct s_file
{
	char	**file_name;
	char	**commandes;
	char	**type;
	int		sum;
}	t_file;

// Parsing Environment
typedef struct t_env
{
	char *key;
	char *value;
	struct t_env *next;
} t_env;

// Data Structure for global variables
typedef struct	t_data
{
	int		exit_status;
	t_env	*env;
}	t_data;

// global variable for data
// t_data g_data;

/* init env functions*/
t_env	*init_env(char **env);


// int		ft_strlen(char *s);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strdup(char *s1);
// void	*ft_calloc(int count, int size);
t_list	**parsing(t_read *readline, char **env); // parsing function
int		count_words(char *str);
int		counter(char *str);
void	print_minishell(t_read *readln);
void	replace_char(t_read *readline);
void	skip_spaces(t_read *readline);
void	fill_the_arr(t_read	*readline);
// char	*ft_substr(char *s, int start, int len);
void	skip_spaces_in_the_input(t_read *readline);
int		ft_strcmp(const char *s1, const char *s2);
// void	sep_files(t_read *readline, t_file *sep, t_list **node);
t_list	**sep_files(t_read *readline, t_file *sep);
t_list	*ft_lstnew(char **file_name, char **commandes, char **type);
void	ft_lst_add_back(t_list **head, char **file_name,
			char **commandes, char **type);
int		count_files(t_read *readline);
// char	*ft_strcpy(char *s1, char *s2);
void	sep_by_spaces(t_read *readline);
int		counter_sep(char *str);
void	add_spaces_in_the_input(t_read *readline);
int		counter_arr(char *str);
int		count_commande(t_read *readline);
void	exit_function(t_read *readline);
void	clean_d_quotes(t_read *readline);
char	*ft_clean_d_quotes(char *str);
int		check_d_quotes(t_read *readline);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	expand_arr(t_read *readline, char **env);
char	*ft_strjoin_char(char *s1, char c);
// char	**ft_split(char const *s, char c);
void	split_into_arr(t_read *readline);
void	syntax_error(t_read *readline, char **env);
void	help_clean(char *str, char *str1, int i, int k);
void	help_clean_1(char *str, char *str1, int i, int k);
int		count_dquotes(t_read *readline);
int		count_s_quotes(t_read *readline);
void	__exit__(t_list *cmd);
char	*__pwd__(void);
void	error(char *s1, char *s2, char *s3);
char	*null_buffer(void);
// void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin_join(char *s1, char *s2);
// void	ft_putchar_fd(char c, int fd);
int		ft_is_digit(int c);
char	*ft_strjoin_join01(char *s1, char *s2);
// int		ft_isalpha(int c);
int		search_for_equal(char *s);
char	*get_env_value1(char *s);
// int		strlen1(char *s);
char	*equale_value(char *s);
// char	*ft_itoa(int n);
// int		ft_atoi(const char *str);
int		strlen1(char *s);
// int		check_syntax_error(t_read *readline);
#endif

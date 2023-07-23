/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:42:08 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/23 23:51:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_char(char c)
{
	if (c == '`' || c == '.' || c == '$' || c == '-' || c == '+' || c == '/'
		|| c == '*' || c == '\\' || c == '?' || c == '!' || c == '>'
		|| c == '<' || c == ',' || c == '=' || c == '+' || c == ')'
		|| c == '(' || c == '&' || c == '^' || c == '%' || c == '#'
		|| c == '\t' || c == ' ' || c == ':' || c == '\'' || c == '$')
		return (0);
	return (1);
}

void	initial_env(t_variables *var)
{
	var->str1 = calloc(1, 1);
	var->j = 0;
	var->i = 0;
	var->count = 0;
}

void	call_env(t_read *readline, char *str, char **env, t_variables *var)
{
	initial_env(var);
	while (str[var->count] && check_special_char(str[var->count]) == 1)
	{
		if (str[var->count] != '\"')
			var->str1 = ft_strjoin_char(var->str1, str[var->count]);
		var->count++;
		var->j++;
	}
	var->len = ft_strlen(var->str1) + 1;
	var->str1 = ft_strjoin(var->str1, "=");
	var->i = 0;
	while (env[var->i])
	{
		if (ft_strncmp(env[var->i], var->str1, var->len) == 0)
		{
			while (env[var->i][var->len])
				readline->exp = ft_strjoin_char(readline->exp,
						env[var->i][var->len++]);
			var->k = 1;
		}
		var->i++;
	}
	var->len = ft_strlen(str) + 1;
	if (var->k == 1)
		while (var->j < var->len - 1)
			readline->exp = ft_strjoin_char(readline->exp, str[var->j++]);
}

int	count_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count += 1;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	else
		return (0);
}

int	check_ends_pipes(t_read *readline, char c)
{
	if (c == '|')
	{
		write(2, "bash: syntax error near unexpected token `|'\n", 45);
		readline->exit_status = 258;
		return (-1);
	}
	else if (c == '&')
	{
		write(2, "bash: syntax error near unexpected token `&'\n", 45);
		readline->exit_status = 258;
		return (-1);
	}
	else if (c == ')')
	{
		write(2, "bash: syntax error near unexpected token `)'\n", 45);
		readline->exit_status = 258;
		return (-1);
	}
	return (0);
}

int	check_ends_pipes2(t_read *readline, char c, char s)
{
	if (c == '|' || s == '|' || (c == '|' && s == '|'))
	{
		write(2, "bash: syntax error near unexpected token `|'\n", 45);
		readline->exit_status = 258;
		return (-1);
	}
	else if (c == '&' || s == '&' || (c == '&' && s == '&'))
	{
		write(2, "bash: syntax error near unexpected token `&'\n", 45);
		readline->exit_status = 258;
		return (-1);
	}
	else if (c == ')')
	{
		write(2, "bash: syntax error near unexpected token `)'\n", 45);
		readline->exit_status = 258;
		return (-1);
	}
	return (0);
}

int	special_checks(t_read *readline, char c, char s)
{
	int i = 0;
	if(c == '>' && s == '<')
	{
		write(2, "bash: syntax error near unexpected token `<'\n", 45);
		readline->exit_status = 258;
		return (-1);
	}
	else if (c == '<' && s == '>')
	{
		write(2, "bash: syntax error near unexpected token `<'\n", 45);
		readline->exit_status = 258;
		return (-1);
	}
	else if (c == '>')
	{
		while(c == '>')
			i++;
		if(i >= 2)
		{
			write(2, "bash: syntax error near unexpected token `<<'\n", 46);
			readline->exit_status = 258;
			return (-1);
		}
	}
	return (0);
}

int	check_readirictions(t_read *readline, char c)
{
	int	i;

	i = 0;
	if (c == '>')
	{
		while (c == '>')
			i++;
		if (i >= 2)
		{
			write(2, "bash: syntax error near unexpected token `>>'\n", 46);
			readline->exit_status = 258;
			return (-1);
		}
	}
	else if (c == '<')
	{
		i = 0;
		while (c == '<')
			i++;
		if (i >= 2)
		{
			write(2, "bash: syntax error near unexpected token `<<'\n", 46);
			readline->exit_status = 258;
			return (-1);
		}
	}
	else if (c == '&')
	{
		while(c == '&')
			i++;
		if(i >= 2)
		{
			write(2, "bash: syntax error near unexpected token `&&'\n", 46);
			readline->exit_status = 258;
			return (-1);
		}
	}
	return (0);
}

int	check_syntax_error(t_read *readline, char c, char s)
{
	if (check_ends_pipes(readline, c) == -1)
		return (-1);
	if (check_ends_pipes2(readline, c, s) == -1)
		return (-1);
	if (check_readirictions(readline, c) == -1)
	if (special_checks(readline, c, s) == -1)
		return (-1);
	// if (check_parentheses(char c) == -1)
	// 	return (-1);
	return (0);
}

void	expand_arr(t_read *readline, char **env)
{
	t_variables *var;
	var = malloc(sizeof(t_variables));
	int i = 0;
	int count = 0;
	var->k = 0;
	var->s_d = 0;
	int sc = 0;
	readline->exp = calloc(1, 1);
	readline->new_input = calloc(1, 1);
	while (readline->input[i])
	{
		// if (check_syntax_error(readline, readline->input[i], readline->input[i + 1]) == -1)
		// 	return ;
		// else
		// {
			if (readline->input[i] == '\'' && var->s_d == 0)
			{
				if(sc == 0)
					sc = 1;
				else if (sc == 1)
					sc = 0;
				count = 0;
				if (readline->input[i] && readline->input[i] == '\'')
				{
					readline->exp = ft_strjoin_char(readline->exp, readline->input[i++]);
					count += 1;
				}
				if (sc == 1)
				{
					while (readline->input[i] && readline->input[i] != '\'')
						readline->exp = ft_strjoin_char(readline->exp, readline->input[i++]);
				}
			}
			else if (readline->input[i] == '\"' && sc == 0)
			{
				if (var->s_d == 0)
					var->s_d = 1;
				else if (var->s_d == 1)
					var->s_d = 0;
				if (readline->input[i] && readline->input[i] == '\"')
					readline->exp = ft_strjoin_char(readline->exp, readline->input[i++]);
				if (readline->input[i] != '\'')
				{
					while (readline->input[i] && check_special_char(readline->input[i]) == 0)
					{
						count = 0;
						if (readline->input[i] != '$')
							readline->exp = ft_strjoin_char(readline->exp, readline->input[i++]);
						else
						{
							while (readline->input[i] == '$')
							{
								count++;
								i++;
							}
							if (count % 2 == 0)
							{
								var->k = 0;
								while (readline->input[i] && readline->input[i] != '$')
									readline->exp = ft_strjoin_char(readline->exp, readline->input[i++]);
							}
							else
							{
								if (readline->input[i - 1] == '$' && readline->input[i] == '+')
									readline->exp = ft_strjoin_char(readline->exp, readline->input[i - 1]);
								var->k = 1;	
							}
						}
					}
					if (readline->input[i - 1] == '$')
						while (readline->input[i] && check_special_char(readline->input[i]) == 1 && readline->input[i] != '\"')
							readline->new_input = ft_strjoin_char(readline->new_input, readline->input[i++]);
					if (var->k == 1)
						call_env(readline, readline->new_input, env, var);
					else if (var->k == 0)
						readline->exp = ft_strjoin(readline->exp, readline->new_input);	
					if (check_special_char(readline->input[i]) == 0 && readline->input[i] != '$' && readline->input[i] == '\"')
					{
						readline->exp = ft_strjoin_char(readline->exp, readline->input[i]);	
						i++;
					}
					readline->new_input = calloc(1, 1);
				}
			}
			else
			{
				count = 0;
				if (readline->input[i] == '$')
				{
					while (readline->input[i] == '$')
					{
						count++;
						i++;
					}
					if (((count % 2) == 0))
					{
						var->k = 0;
						while (readline->input[i] && readline->input[i] != '$')
								readline->exp = ft_strjoin_char(readline->exp, readline->input[i++]);
					}
					else
					{
						if (readline->input[i - 1] == '$' && readline->input[i] == '+')
							readline->exp = ft_strjoin_char(readline->exp, readline->input[i - 1]);
						var->k = 1;
					}
					while (readline->input[i] && readline->input[i] != '\"' && check_special_char(readline->input[i]) == 1)
						readline->new_input = ft_strjoin_char(readline->new_input, readline->input[i++]);
					if (var->k == 1)
						call_env(readline, readline->new_input, env, var);
					readline->new_input = calloc(1, 1);
				}
				else
					readline->exp = ft_strjoin_char(readline->exp, readline->input[i++]);
			}
			
		}
	// }
}


// echo 'ssss'"$USER"

// echo " <|> '"''

// echo "'$USER'"

// echo ""'"$USER"'

// echo $+ //(*)

// echo $USER?

// 'l'"s"
// echo "$USER'"

// echo "$USER $PWD"

// echo "$USER-*/"'+.,;#?<|>:"

// echo ''""
// """'$USER $HOME'"""$USER'$USER' //(*)
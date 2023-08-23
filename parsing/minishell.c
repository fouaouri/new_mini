/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/08/23 16:00:34 by melhadou         ###   ########.fr       */
/*   Updated: 2023/08/23 15:45:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(t_read *readline)
{
	int i = 0;
	int len = counter_arr(readline->put_zero) - 1;
	if(len < 0)
		len = 0;
	if(ft_strcmp(readline->arr[0], "|") == 0)
	{
		write(2, "bash: syntax error near unexpected token\n", 41);
		readline->exit_status = 258;
		return (-1);
	}
	else if(ft_strcmp(readline->arr[len], "|") == 0)
	{
		write(2, "bash: syntax error near unexpected token\n", 41);
		readline->exit_status = 258;
		return (-1);
	}
	else if(ft_strcmp(readline->arr[0], "&") == 0)
	{
		write(2, "bash: syntax error near unexpected token\n", 41);
		readline->exit_status = 258;
		return (-1);
	}
	else if (ft_strcmp(readline->arr[0], ")") == 0)
	{
		write(2, "bash: syntax error near unexpected token\n", 41);
		readline->exit_status = 258;
		return (-1);
	}
	while(readline->string[i])
	{
		if (readline->string[i] == '\'')
		{
			i += 1;
			while (readline->string[i] != '\'')
				i++;
		}
		else if (readline->string[i] == '\"')
		{
			i += 1;
			while (readline->string[i] != '\"')
				i++;
		}
		else if(readline->string[i] == '|' && readline->string[i + 1] == '|')
		{
			write(2, "bash: syntax error near unexpected token\n", 41);
			readline->exit_status = 258;
			return	(-1);
			break;
		}
		else if((readline->input[i] == '>' && readline->input[i + 1] == ' '
			&& readline->input[i + 2] == '|') || (readline->input[i] == '<' && readline->input[i + 1] == '|')
			|| (readline->input[i] == '<' && readline->input[i + 1] == ' '
			&& readline->input[i + 2] == '|'))
		{
			write(2, "bash: syntax error near unexpected token\n", 41);
			readline->exit_status = 258;
			return (-1);
			break;
		}
		i++;
	}
	return (0);
}

int	check_redirections(t_read *readline)
{
	// int i;
	int len;
	
	len = counter_arr(readline->put_zero) - 1;
	if(len < 0)
		len = 0;
	// i = 0;
		
	if (readline->arr[len] && ((ft_strcmp(readline->arr[len], ">") == 0 || ft_strcmp(readline->arr[len], "<") == 0)
	|| (ft_strcmp(readline->arr[len], ">>") == 0 || ft_strcmp(readline->arr[len], "<<") == 0)))
	{
		write(2, "bash: syntax error near unexpected token\n", 41);
		readline->exit_status = 258;
		return (-1);
	}
	// while(readline->input[i] && readline->string[i] && readline->string[i + 1])
	// {
	// 	if(readline->input[i] == '>' && readline->input[i + 1] == '<')
	// 	{
	// 		write(2, "bash: syntax error near unexpected token\n", 41);
	// 		readline->exit_status = 258;
	// 		return (-1);
	// 		break;
	// 	}
	// 	else
	// 		i++;
	// }
	// i = 0;
	// while(readline->arr[i])
	// {
	// 	if(ft_strcmp(readline->arr[i], ">")
	// 	&& (ft_strncmp(readline->arr[i + 1], "<", 1) || ft_strncmp(readline->arr[i + 1], ">", 1)))
	// 	{
	// 		write(2, "bash: syntax error near unexpected token\n", 41);
	// 		readline->exit_status = 258;
	// 		return (-1);
	// 		break;
	// 	}
	// 	else if(ft_strcmp(readline->arr[i], "<")
	// 	&& (ft_strncmp(readline->arr[i + 1], "<", 1) || ft_strncmp(readline->arr[i + 1], ">", 1)))
	// 	{
	// 		write(2, "bash: syntax error near unexpected token\n", 41);
	// 		readline->exit_status = 258;
	// 		return (-1);
	// 		break;
	// 	}
	// 	i++;
	// }
	return(0);
}

int	check_redi(t_read *readline)
{
	int i;

	i = 0;
	while(readline->input[i] == '<')
		i++;
	if(i > 2)
	{
		write(2, "bash: syntax error near unexpected token\n", 41);
		readline->exit_status = 258;
			return (-1);
	}
	i = 0;
	while(readline->input[i] == '>')
		i++;
	if(i > 2)
	{
		write(2, "bash: syntax error near unexpected token\n", 41);
		readline->exit_status = 258;
			return (-1);
	}
	i = 0;
	while(readline->input[i] == '&')
		i++;
	if(i > 1)
	{
		write(2, "bash: syntax error near unexpected token\n", 41);
		readline->exit_status = 258;
			return (-1);
	}
	return(0);
}

int check_ands(t_read *readline)
{
	int i;
	int len;
	
	len = counter_arr(readline->put_zero) - 1;
	if(len >= 0)
	{
		i = 0;
		while(readline->input[i] && readline->input[i] == '&')
			i++;
		if(i > 1)
		{
			write(2, "bash: syntax error near unexpected token\n", 41);
			{
				readline->exit_status = 258;
				return (-1);
			}
		}
		i = 0;
		while(readline->arr[len][i] && readline->arr[len][i] == '&')
			i++;
		if(i > 2)
		{
			write(2, "bash: syntax error near unexpected token\n", 41);
			readline->exit_status = 258;
				return (-1);
		}
	}

	return(0);
}

int check_parentheses(t_read *readline)
{
	int i;
	int len;
	
	len = 0;
	i = 0;
	while(readline->arr[len])
	{
		i = 0;
		while(readline->arr[len][i])
		{
			if(readline->arr[len][i] == ')')
			{
				write(2, "bash: syntax error near unexpected token \n", 43);
				readline->exit_status = 258;
				return (-1);
				break ;
			}
			i++;
		}
		len++;
	}
	return(0);
}

int check_d_quotes(t_read *readline)
{
	int i = 0;
	int count = 0;
	int count1 = 0;
	while(readline->input[i])
	{
		if(readline->input[i] == '\"' || readline->input[i] == '\'')
			count += 1;
		i++;
	}
	i = 0;
	while(readline->input[i])
	{
		if(readline->input[i] == '\'')
			count1 += 1;
		i++;
	}
	if(count % 2 != 0 || count1 % 2 != 0)
	{
		write(2, "bash: syntax error near unexpected token \n", 43);
		readline->exit_status = 258;
		return (-1);
	}
	return(0);
}

// > >
// < <
// $?

int	check_syntax_error(t_read *readline)
{
	if (check_redirections(readline) == -1 || check_pipes(readline) == -1)
		return (-1);
	if(check_redi(readline) == -1 || check_ands(readline) == -1)
		return (-1);
	if(check_parentheses(readline) == -1)
		return (-1);
	return (0);
}

void	print_minishell(t_read *readln)
{
	readln->input = readline("my_minishell $> ");
	add_history(readln->input);
	if (readln->input == NULL)
		readln->input = ft_calloc(1, 1);
}

t_list	**parsing(t_read *readline, char **env)
{
	t_list	**node;
	t_file	*sep;
	int		sepe;

	readline->exit_status = 0;
	sep = malloc(sizeof(t_file));
	print_minishell(readline);
	printf("input : %s\n", readline->input);
	expand_arr(readline, env);
	printf("exp : %s\n", readline->exp);
	sepe = check_d_quotes(readline);
	if(sepe != -1)
	{
		replace_char(readline);
		skip_spaces_in_the_input(readline);
		sep_by_spaces(readline);
		add_spaces_in_the_input(readline);
		fill_the_arr(readline);
		clean_d_quotes(readline);
		// sepe = check_syntax_error(readline);
		// if (sepe != -1)
			node = sep_files(readline, sep);
	}
	return (node);              
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)av;
// 	t_read	*readline;
// 	int i = 0;
// 	readline = malloc(sizeof(t_read));
// 	while (ac == 1)
// 	{
// 		t_list **hold;
// 		hold = NULL;
// 		hold = parsing(readline, env);
// 		while((*hold) != NULL)
// 		{
// 			i = 0;
// 			while((*hold)->commandes[i])
// 			{
// 				printf("commandes :%d = %s\n", i,(*hold)->commandes[i]);
// 				i++;	
// 			}
// 			i = 0;
// 			 while((*hold)->file_name[i])
// 			 {
// 			 	printf("file_name :%d = %s\n", i,(*hold)->file_name[i]);
// 				i++;
// 			 }
// 			i = 0;
// 			while ((*hold)->type[i])
// 				printf("type : %s\n", (*hold)->type[i++]);
// 			(*hold) = (*hold)->next;
// 		}
// 		// system("leaks minishell");
// 	}
// }

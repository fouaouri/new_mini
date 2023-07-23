/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/23 23:53:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_pipes(t_read *readline)
// {
// 	int i = 0;
// 	****if(ft_strcmp(readline->arr[0], "|") == 0)
// 	{
// 		write(2, "bash: syntax error near unexpected token `|'\n", 45);
// 		readline->exit_status = 258;
// 		return (-1);
// 	}
// 	****else if(ft_strcmp(readline->arr[0], "&") == 0)
// 	{
// 		write(2, "bash: syntax error near unexpected token `&'\n", 45);
// 		readline->exit_status = 258;
// 		return (-1);
// 	}
// 	****else if (ft_strcmp(readline->arr[0], ")") == 0)
// 	{
// 		write(2, "bash: syntax error near unexpected token `)'\n", 45);
// 		readline->exit_status = 258;
// 		return (-1);
// 	}
// 	***while(readline->string[i])
// 	{
// 		******if(readline->string[i] == '|' && readline->string[i + 1] == '|')
// 		{
// 			write(2, "bash: syntax error near unexpected token `||'\n", 46);
// 			readline->exit_status = 258;
// 			return	(-1);
// 			break;
// 		}
// 		else if((readline->input[i] == '>' && readline->input[i + 1] == ' '
// 			&& readline->input[i + 2] == '|') || (readline->input[i] == '<' && readline->input[i + 1] == '|'))
// 		{
// 			write(2, "bash: syntax error near unexpected token `|'\n", 46);
// 			readline->exit_status = 258;
// 			return (-1);
// 			break;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	check_redirections(t_read *readline)
// {
// 	int i;
// 	int len;
	
// 	len = counter_arr(readline->put_zero) - 1;
// 	i = 0;
// 	if ((ft_strcmp(readline->arr[len], ">") == 0 || ft_strcmp(readline->arr[len], "<") == 0)
// 		|| (ft_strcmp(readline->arr[len], ">>") == 0 || ft_strcmp(readline->arr[len], "<<") == 0))
// 	{
// 		write(2, "bash: syntax error near unexpected token `newline'\n", 51);
// 		readline->exit_status = 258;
// 		return (-1);
// 	}
// *******	while(readline->string[i] && readline->string[i + 1])
// 	{
// 		if(readline->input[i] == '>' && readline->input[i + 1] == '<')
// 		{
// 			write(2, "bash: syntax error near unexpected token `<'\n", 45);
// 			readline->exit_status = 258;
// 			return (-1);
// 			break;
// 		}
// 		i++;
// 	}
// 	return(0);
// }

// int	check_redi(t_read *readline)
// {
// 	int i;

// 	i = 0;
// 	while(readline->input[i] == '<')
// 		i++;
// 	*******if(i > 2)
// 	{
// 		write(2, "bash: syntax error near unexpected token `<<'\n", 46);
// 		readline->exit_status = 258;
// 			return (-1);
// 	}
// 	i = 0;
// 	while(readline->input[i] == '>')
// 		i++;
// 	*******if(i > 2)
// 	{
// 		write(2, "bash: syntax error near unexpected token `>>'\n", 46);
// 		readline->exit_status = 258;
// 			return (-1);
// 	}
// 	i = 0;
// 	*******while(readline->input[i] == '&')
// 		i++;
// 	if(i > 1)
// 	{
// 		write(2, "bash: syntax error near unexpected token `&&'\n", 46);
// 		readline->exit_status = 258;
// 			return (-1);
// 	}
// 	return(0);
// }

// int check_ands(t_read *readline)
// {
// 	int i;
// 	int len;
	
// 	len = counter_arr(readline->put_zero) - 1;
// 	i = 0;
// 	while(readline->input[i] == '&')
// 		i++;
// 	if(i > 1)
// 	{
// 		write(2, "bash: syntax error near unexpected token `&&'\n", 46);
// 		{
// 			readline->exit_status = 258;
// 			return (-1);
// 		}
// 	}
// 	i = 0;
// 	while(readline->arr[len][i] == '&')
// 		i++;
// 	if(i > 2)
// 	{
// 		write(2, "bash: syntax error near unexpected token `&&'\n", 46);
// 		readline->exit_status = 258;
// 			return (-1);
// 	}
// 	return(0);
// }

// int check_parentheses(t_read *readline)
// {
// 	int i;
// 	int len;
	
// 	len = 0;
// 	i = 0;
// 	while(readline->arr[len])
// 	{
// 		i = 0;
// 		while(readline->arr[len][i])
// 		{
// 			if(readline->arr[len][i] == ')')
// 			{
// 				write(2, "bash: syntax error near unexpected token `)'\n", 45);
// 				readline->exit_status = 258;
// 				return (-1);
// 				break ;
// 			}
// 			i++;
// 		}
// 		len++;
// 	}
// 	return(0);
// }

// int	check_syntax_error(t_read *readline)
// {
// 	if (check_redirections(readline) == -1 || check_pipes(readline) == -1)
// 		return (-1);
// 	if(check_redi(readline) == -1 || check_ands(readline) == -1)
// 		return (-1);
// 	if(check_parentheses(readline) == -1)
// 		return (-1);
// 	return (0);
// }

void	print_minishell(t_read *readln)
{
	readln->input = readline("my_minishell $> ");
	add_history(readln->input);
	if (readln->input == NULL)
		readln->input = ft_calloc(1, 1);
}

void	exit_function(t_read *readline)
{
	if (ft_strcmp(readline->string, "exit") == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)env;
	t_read	*readline;
	t_file *sep;
	t_list *node = NULL;
	// int sepe = 0;
	// int		i = 0;

	(void)av;
	readline = malloc(sizeof(t_read));
	sep = malloc(sizeof(t_file));
	readline->exit_status = 0;
	while (ac == 1)
	{
		print_minishell(readline);
		expand_arr(readline, env);
		// printf("exp : %s\n", readline->exp);
		// sepe = check_d_quotes(readline);
		// if(sepe != -1)
		// {
			replace_char(readline);
			// printf("replace :%s\n", readline->replace);
			skip_spaces_in_the_input(readline);
			// exit_function(readline);
			sep_by_spaces(readline);
			add_spaces_in_the_input(readline);
			fill_the_arr(readline);
			clean_d_quotes(readline);
			// sepe = check_syntax_error(readline);
			// if (sepe != -1)
			sep_files(readline, sep, &node);	
			if(ft_strcmp(node->commandes[0] , "exit") == 0)
				ft_exit(node);
		// }
		// while(node != NULL)
		// {
		// 	i = 0;
		// 	while(node->commandes[i])
		// 		printf("commandes :%s\n", node->commandes[i++]);
		// 	i = 0;
		// 	 while(node->file_name[i])
		// 	 	printf("file_name : %s\n", node->file_name[i++]);
		// 	i = 0;
		// 	while (node->type[i])
		// 		printf("type : %s\n", node->type[i++]);
		// 	node = node->next;
		// }
	}
}

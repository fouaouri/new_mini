// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minishell.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nkhachab <nkhachab@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
// /*   Updated: 2023/07/23 09:10:19 by nkhachab         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// // int	check_pipes(t_read *readline)
// // {
// // 	int i = 0;
// // 	****if(ft_strcmp(readline->arr[0], "|") == 0)
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `|'\n", 45);
// // 		readline->exit_status = 258;
// // 		return (-1);
// // 	}
// // 	****else if(ft_strcmp(readline->arr[0], "&") == 0)
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `&'\n", 45);
// // 		readline->exit_status = 258;
// // 		return (-1);
// // 	}
// // 	****else if (ft_strcmp(readline->arr[0], ")") == 0)
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `)'\n", 45);
// // 		readline->exit_status = 258;
// // 		return (-1);
// // 	}
// // 	***while(readline->string[i])
// // 	{
// // 		******if(readline->string[i] == '|' && readline->string[i + 1] == '|')
// // 		{
// // 			write(2, "bash: syntax error near unexpected token `||'\n", 46);
// // 			readline->exit_status = 258;
// // 			return	(-1);
// // 			break;
// // 		}
// // 		else if((readline->input[i] == '>' && readline->input[i + 1] == ' '
// // 			&& readline->input[i + 2] == '|') || (readline->input[i] == '<' && readline->input[i + 1] == '|'))
// // 		{
// // 			write(2, "bash: syntax error near unexpected token `|'\n", 46);
// // 			readline->exit_status = 258;
// // 			return (-1);
// // 			break;
// // 		}
// // 		i++;
// // 	}
// // 	return (0);
// // }

// // int	check_redirections(t_read *readline)
// // {
// // 	int i;
// // 	int len;
	
// // 	len = counter_arr(readline->put_zero) - 1;
// // 	i = 0;
// // 	if ((ft_strcmp(readline->arr[len], ">") == 0 || ft_strcmp(readline->arr[len], "<") == 0)
// // 		|| (ft_strcmp(readline->arr[len], ">>") == 0 || ft_strcmp(readline->arr[len], "<<") == 0))
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `newline'\n", 51);
// // 		readline->exit_status = 258;
// // 		return (-1);
// // 	}
// // *******	while(readline->string[i] && readline->string[i + 1])
// // 	{
// // 		if(readline->input[i] == '>' && readline->input[i + 1] == '<')
// // 		{
// // 			write(2, "bash: syntax error near unexpected token `<'\n", 45);
// // 			readline->exit_status = 258;
// // 			return (-1);
// // 			break;
// // 		}
// // 		i++;
// // 	}
// // 	return(0);
// // }

// // int	check_redi(t_read *readline)
// // {
// // 	int i;

// // 	i = 0;
// // 	while(readline->input[i] == '<')
// // 		i++;
// // 	*******if(i > 2)
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `<<'\n", 46);
// // 		readline->exit_status = 258;
// // 			return (-1);
// // 	}
// // 	i = 0;
// // 	while(readline->input[i] == '>')
// // 		i++;
// // 	*******if(i > 2)
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `>>'\n", 46);
// // 		readline->exit_status = 258;
// // 			return (-1);
// // 	}
// // 	i = 0;
// // 	*******while(readline->input[i] == '&')
// // 		i++;
// // 	if(i > 1)
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `&&'\n", 46);
// // 		readline->exit_status = 258;
// // 			return (-1);
// // 	}
// // 	return(0);
// // }

// // int check_ands(t_read *readline)
// // {
// // 	int i;
// // 	int len;
	
// // 	len = counter_arr(readline->put_zero) - 1;
// // 	i = 0;
// // 	while(readline->input[i] == '&')
// // 		i++;
// // 	if(i > 1)
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `&&'\n", 46);
// // 		{
// // 			readline->exit_status = 258;
// // 			return (-1);
// // 		}
// // 	}
// // 	i = 0;
// // 	while(readline->arr[len][i] == '&')
// // 		i++;
// // 	if(i > 2)
// // 	{
// // 		write(2, "bash: syntax error near unexpected token `&&'\n", 46);
// // 		readline->exit_status = 258;
// // 			return (-1);
// // 	}
// // 	return(0);
// // }

// // int check_parentheses(t_read *readline)
// // {
// // 	int i;
// // 	int len;
	
// // 	len = 0;
// // 	i = 0;
// // 	while(readline->arr[len])
// // 	{
// // 		i = 0;
// // 		while(readline->arr[len][i])
// // 		{
// // 			if(readline->arr[len][i] == ')')
// // 			{
// // 				write(2, "bash: syntax error near unexpected token `)'\n", 45);
// // 				readline->exit_status = 258;
// // 				return (-1);
// // 				break ;
// // 			}
// // 			i++;
// // 		}
// // 		len++;
// // 	}
// // 	return(0);
// // }

// // int	check_syntax_error(t_read *readline)
// // {
// // 	if (check_redirections(readline) == -1 || check_pipes(readline) == -1)
// // 		return (-1);
// // 	if(check_redi(readline) == -1 || check_ands(readline) == -1)
// // 		return (-1);
// // 	if(check_parentheses(readline) == -1)
// // 		return (-1);
// // 	return (0);
// // }

// void	print_minishell(t_read *readln)
// {
// 	readln->input = readline("my_minishell $> ");
// 	add_history(readln->input);
// 	if (readln->input == NULL)
// 		readln->input = ft_calloc(1, 1);
// }

// void	exit_function(t_read *readline)
// {
// 	if (ft_strcmp(readline->string, "exit") == 0)
// 	{
// 		write(1, "exit\n", 5);
// 		exit(0);
// 	}
// }

// int lst_size(t_list *node)
// {
// 	int i;
// 	i = 0;
// 	while (node != NULL)
// 	{
// 		node = node->next;
// 		i++;
// 	}
// 	return i;
// }

// // void exucution(t_list *node)
// // {
// // 	int h = 0;
// // 	int		i = 0;
// // 		while(node != NULL)
// // 		{
// // 			i = 0;
// // 			while(node->commandes[i])
// // 				printf("commandes :%s\n", node->commandes[i++]);
// // 			i = 0;
// // 			 while(node->file_name[i])
// // 			 	printf("file_name : %s\n", node->file_name[i++]);
// // 			i = 0;
// // 			while (node->type[i])
// // 				printf("type : %s\n", node->type[i++]);
// // 			node = node->next;
// // 			h++;
// // 		}
// // 	// int i = lst_size(lst);
// // 	// printf("size = %d\n", h);
// //}
// char	*path_bring(char **env)
// {
// 	int		i;
// 	char	*save;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "PATH=", 5) == 0)
// 			save = env[i] + 5;
// 		i++;
// 	}
// 	return (save);
// }

// char	*path_finder(char **env, char **cmd)
// {
// 	int		i;
// 	char	**paths;
// 	char	*temp;

// 	i = 0;
// 	paths = ft_split(path_bring(env), ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		temp = paths[i];
// 		paths[i] = ft_strjoin(temp, "/");
// 			//free (temp);
// 		temp = paths[i];
// 		paths[i] = ft_strjoin(temp, cmd[0]);
// 			//free (temp);
// 			if (access(paths[i], F_OK) == 0)
// 				break ;
// 		i++;
// 	}
// 	return (paths[i]);
// }

// void one_cmd(t_list *node, char **env)
// {

// 	// file = open(node->, O_RDONLY);
// 	// if (file == -1)
// 	// {
// 	// 	perror(av[1]);
// 	// 	exit(1);
// 	// }
// 	//cmd = ft_split(av[2], ' ');
// 	int pid = fork();
// 	if(pid == 0)
// 	{
// 		//dup2()
// 		if (access(node->commandes[0], X_OK) == 0)
// 			execve(node->commandes[0], node->commandes, NULL);
// 		if (access(path_finder(env, node->commandes), X_OK) == -1)
// 		{
// 			write(2, "Access failed\n", 15);
// 			exit(1);
// 		}
// 		execve(path_finder(env, node->commandes), node->commandes, env);
// 		write(2, "Execve failed\n", 15);
// 	}
// }

// void exucution(t_list *node, char **env)
// {
	
// 	if(lst_size(node) == 1)
// 	{
// 		//printf("size \n");
// 		one_cmd(node, env);
// 	}
// 	while (waitpid(-1, NULL, 0) != -1)
// 		;
// }
// int	main(int ac, char **av, char **env)
// {
// 	(void)env;
// 	t_read	*readline;
// 	t_file *sep;
// 	t_list *node = NULL;
// 	// int sepe = 0;
	

// 	(void)av;
// 	readline = malloc(sizeof(t_read));
// 	sep = malloc(sizeof(t_file));
// 	readline->exit_status = 0;
// 	while (ac == 1)
// 	{

// 		print_minishell(readline);
// 		expand_arr(readline, env);
// 		// printf("exp : %s\n", readline->exp);
// 		// sepe = check_d_quotes(readline);
// 		// if(sepe != -1)
// 		// {
// 			replace_char(readline);
// 			// printf("replace :%s\n", readline->replace);
// 			skip_spaces_in_the_input(readline);
// 			exit_function(readline);
// 			sep_by_spaces(readline);
// 			add_spaces_in_the_input(readline);
// 			fill_the_arr(readline);
// 			clean_d_quotes(readline);
// 			// sepe = check_syntax_error(readline);
// 			// if (sepe != -1)
// 			sep_files(readline, sep, &node);	
// 		// }
// 		// system("leaks minishell");
	
// 		//printf("hehe\n");
// 		exucution(node, env);

// 	}
// }


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhachab <nkhachab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/24 02:54:37 by nkhachab         ###   ########.fr       */
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

int lst_size(t_list *node)
{
	int i;
	i = 0;
	while (node != NULL)
	{
		node = node->next;
		i++;
	}
	return i;
}

// void print_parsing(t_list *node)
// {
// 	int h = 0;
// 	int		i = 0;
// 		while(node != NULL)
// 		{
// 			i = 0;
// 			while(node->commandes[i])
// 				printf("commandes :%s\n", node->commandes[i++]);
// 			i = 0;
// 			 while(node->file_name[i])
// 			 	printf("file_name : %s\n", node->file_name[i++]);
// 			i = 0;
// 			while (node->type[i])
// 				printf("type : %s\n", node->type[i++]);
// 			node = node->next;
// 			h++;
// 		}
// 	// int i = lst_size(lst);
// 	// printf("size = %d\n", h);
// }

char	*path_bring(char **env)
{
	int		i;
	char	*save;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			save = env[i] + 5;
		i++;
	}
	return (save);
}

char	*path_finder(char **env, char **cmd)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	paths = ft_split(path_bring(env), ':');
	i = 0;
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(temp, "/");
			//free (temp);
		temp = paths[i];
		paths[i] = ft_strjoin(temp, cmd[0]);
			//free (temp);
			if (access(paths[i], F_OK) == 0)
				break ;
		i++;
	}
	return (paths[i]);
}

void one_cmd(t_list *node, char **env)
{

	// file = open(node->, O_RDONLY);
	// if (file == -1)
	// {
	// 	perror(av[1]);
	// 	exit(1);
	// }
	//cmd = ft_split(av[2], ' ');
	int pid = fork();
	if(pid == 0)
	{
		//dup2()
		if (access(node->commandes[0], X_OK) == 0)
			execve(node->commandes[0], node->commandes, NULL);
		if (access(path_finder(env, node->commandes), X_OK) == -1)
		{
			write(2, "Access failed\n", 15);
			exit(1);
		}
		execve(path_finder(env, node->commandes), node->commandes, env);
		write(2, "Execve failed\n", 15);
	}
	waitpid(pid, 0, 0);
}

int	*create_pipes(int number_of_cmds)
{
	int	*pipes;
	int	i;

	i = 0;
	pipes = malloc (sizeof(int) * ((number_of_cmds - 1) * 2));
	while (i < (number_of_cmds - 1))
	{
		pipe(&pipes[i * 2]);
		i++;
	}
	return (pipes);
}

void	close_pipes(int	*pipes, int number_of_cmds)
{
	int	i;

	i = 0;
	while (i < (number_of_cmds - 1) * 2)
	{
		close(pipes[i]);
		i++;
	}	
}

void	multiple_cmd(t_list *node, char **env, int number_of_cmds)
{
	pid_t	*pids;
	int		status;
	int		*pipes;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = node;
	pids = malloc(sizeof(pid_t) * number_of_cmds);
	pipes = NULL;
	pipes = create_pipes(number_of_cmds);
	while (i < number_of_cmds)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i > 0)
				dup2(pipes[i * 2 - 2], 0);
			if (i < number_of_cmds - 1)
				dup2(pipes[i * 2 + 1], 1);
			close_pipes(pipes, number_of_cmds);
			execve(path_finder(env, tmp->commandes), tmp->commandes, env);
		}
		tmp = tmp->next;
		i++;
	}
	close_pipes(pipes, number_of_cmds);
	i = 0;
	while (i < number_of_cmds)
		waitpid(pids[i++], &status, 0);
}

void exucution(t_list *node, char **env)
{
	
	if(lst_size(node) == 1)
	{
		//printf("size \n");
		// if (node->commandes[0] == "echo")
		// 	command_echo();
		// else if (node->commandes[0] == "cd")
		// 	command_cd();
		// else
			one_cmd(node, env);
	}
	else
	{
		multiple_cmd(node, env, lst_size(node));
	}
	// while (waitpid(-1, NULL, 0) != -1)
	// 	;
	// while (i < number_of_commands)
	// 	waitpid(pids[i++], exit_status, 0);
}
int	main(int ac, char **av, char **env)
{
	(void)env;
	t_read	*readline;
	t_file *sep;
	t_list *node = NULL;
	// int sepe = 0;
	

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
			exit_function(readline);
			sep_by_spaces(readline);
			add_spaces_in_the_input(readline);
			fill_the_arr(readline);
			clean_d_quotes(readline);
			// sepe = check_syntax_error(readline);
			// if (sepe != -1)
			sep_files(readline, sep, &node);	
		// }
		// system("leaks minishell");
	
		//printf("hehe\n");
		// print_parsing(node);
		exucution(node, env);
	}
}

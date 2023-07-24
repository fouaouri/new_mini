/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:36:42 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/24 04:50:06 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_lstnew1(void *content)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->content = ft_strdup((char *)content);
	new->next = NULL;
	return (new);
}
t_data	*ft_lstlast(t_data *lst)
{
	while (lst != NULL && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back1(t_data **lst, t_data *new)
{
	t_data	*addl;

	addl = 0;
	if (*lst == NULL)
	{
		new->next = NULL;
		*lst = new;
	}
	else
	{
		addl = ft_lstlast(*lst);
		addl->next = new;
	}
}


void	convert(t_data **data, char **env)
{
	int		i;
	char	*tmp;
	char	*tmp1 = NULL;

	i = -1;
	if (!env[0])
	{
		tmp1 = getpwd();
		tmp = ft_strjoin("PWD=", tmp1);
		ft_lstadd_back1(data, ft_lstnew1(tmp));
		(free(tmp), free(tmp1));
		ft_lstadd_back1(data, ft_lstnew1("OLDPWD"));
		ft_lstadd_back1(data, ft_lstnew1("SHLVL=1"));
	}
	else
	{
		while (env[++i])
		{
			// if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			// 	usnet12(&tmp, &tmp1, &env[i]);
			ft_lstadd_back1(data, ft_lstnew1(env[i]));
		}
	}
}
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
int lst_size1(t_data *node)
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
char	*path_bring(char **env)
{
	int		i;
	char	*save;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			save = env[i] + 5;
			return (save);
		}
		i++;
	}
	return NULL;
}

char	*path_finder(char **env, char **cmd)
{
	int		i;
	char	**paths;
	char *hold;
	char	*temp;

	i = 0;
	hold = path_bring(env);
	if(!hold)
	{ 
		return NULL;
	}
	paths = ft_split(hold, ':');
	
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
char **convertto2d(t_data **d)
{
	t_data *tmp ;
	tmp = *d;
	char **newenv;
	int i = 0;
	
	newenv = malloc(sizeof(char * ) * ((lst_size1(tmp) + 1)));
	while(tmp != NULL)
	{
		newenv[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	newenv[i] = NULL;
	return newenv;
}
void	printerr2(char *s1, char *s2, char *s3)
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
	// g_globe.exit_status = 127;
}
void one_cmd(t_list *node, t_data **envp)
{

	// file = open(node->, O_RDONLY);
	// if (file == -1)
	// {
	// 	perror(av[1]);
	// 	exit(1);
	// }
	//cmd = ft_split(av[2], ' ');
	char *hold;
	char **env;
	env = convertto2d(envp);
	int pid = fork();
	if(pid == 0)
	{
		//dup2()
		if (access(node->commandes[0], X_OK) == 0)
			execve(node->commandes[0], node->commandes, NULL);
		hold = path_finder(env, node->commandes);
		if(!hold)
		{
			printerr2("bash", node->commandes[0], "No such file or directory");
			return;
		}
		if (access(hold, X_OK) == -1)
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

void	multiple_cmd(t_list *node, t_data **envp, int number_of_cmds)
{
	pid_t	*pids;
	int		status;
	int		*pipes;
	t_list	*tmp;
	char **env;
	int		i;
	char *hold;

	env = convertto2d(envp);
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
			hold = path_finder(env, node->commandes);
		if(!hold)
		{
			printerr2("bash", node->commandes[0], "No such file or directory");
			return;
		}
		if (access(hold, X_OK) == -1)
		{
			write(2, "Access failed\n", 15); 
			exit(1);
		}
			execve(hold, tmp->commandes, env);
		}
		tmp = tmp->next;
		i++;
	}
	close_pipes(pipes, number_of_cmds);
	i = 0;
	while (i < number_of_cmds)
		waitpid(pids[i++], &status, 0);
}

void exucution(t_list *node,t_data **envp,t_info *info)
{
	
	if(lst_size(node) == 1)
	{
		if( ft_strcmp(node->commandes[0] , "exit") == 0)
		{
			printf("node->commandes[0] = %s\n",node->commandes[0]);
			ft_exit(node);
		}
		else if(ft_strcmp(node->commandes[0] , "cd") == 0)
				ft_cd(node,envp);
		else if(ft_strcmp(node->commandes[0] , "pwd") == 0)
		{
			printf("%s\n",getpwd());
		}
		else if(ft_strcmp(node->commandes[0] , "export") == 0)
		{
			ft_export(node,envp,info);
		}
		else if(ft_strcmp(node->commandes[0] , "unset") == 0)		
			ft_unset(node,envp);
		//printf("size \n");
		// if (node->commandes[0] == "echo")
		// 	command_echo();
		// else if (node->commandes[0] == "cd")
		// 	command_cd();
		else
			one_cmd(node, envp);
	}
	else
	{
		multiple_cmd(node, envp, lst_size(node));
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
	t_data	*envp;
	t_info	*info;
	// int sepe = 0;
	// int		i = 0;

	(void)av;
	readline = malloc(sizeof(t_read));
	sep = malloc(sizeof(t_file));
	readline->exit_status = 0;
	convert(&envp, env);
	info = malloc(sizeof(t_info));
	while (ac == 1)
	{
		print_minishell(readline);
		if(readline->input == NULL)
			exit (1);
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
			exucution(node,&envp,info);
			printf("haha\n");
			
			
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

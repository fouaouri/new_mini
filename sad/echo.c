#include "minishell.h"

size_t	ft_strlen_int(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_for_n(char *str)
{
	int	i;
	size_t	found_n;

	i = 1;
	found_n = 0;
	if (!str || !str[0])
		return (0);
	while (str && str[i])
	{
		if (str[i] == 'n')
			found_n++;
		else
			break ;
		i++;
	}
	if (found_n == ft_strlen_int(str) - 1)
		return (0);
	return (1);
}

void	printargs_with_index(char **cmd, int index)
{
	while (cmd[index] != NULL)
	{
		printf("%s", cmd[index]);
		if (cmd[index + 1] != NULL)
			printf(" ");
		index++;
	}
	if (check_for_n(cmd[1]))
		printf("\n");
}

void	check_args_n_option(t_list *cmd, int i)
{
	if (!check_n(cmd->commandes[i]))
	{
		while (cmd->commandes[i] && !check_n(cmd->commandes[i]))
			i++;
		if (!cmd->commandes[i])
			return ;
		printargs_with_index(cmd->commandes, i);
	}
	else
		printargs_with_index(cmd->commandes, i);
}

void	__echo__(t_list *cmd)
{
	int	i;

	i = 1;
	if (!cmd->commandes[i])
	{
		printf("\n");
		return ;
	}
	while (cmd->commandes[i])
	{
		if (cmd->commandes[i][0] == '-')
		{
			check_args_option_n(cmd, i);
			break ;
		}
		else
		{
			print_args_with_index(cmd->commandes, i);
			break ;
		}
		i++;
	}
}

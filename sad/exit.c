#include "minishell.h"
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (ft_putchar_fd(0, fd));
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
void	printerr(char *s1, char *s2, char *s3)
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
}
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int	ft_atoi_fd(char *str)
{
	unsigned char	res;
	int				i;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\f' || str[i] == '\v' || str[i] == '\r'
		|| str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res += str[i] - 48;
		i++;
	}
	if (sign == -1)
		return (res = (signed char)res * sign);
	return (res * sign);
}

int	isnum(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		i++;
	}
	return (ft_atoi_fd(s));
}

void	exit_ut(char *s)
{
	printf("%s\n", s);
	write(1, "bash: ", 6);
	printerr(s, NULL, "too many arguments");
	// g_globe.exit_status = 1;
}

void	ft_exit(t_list *cmd)
{
	if (cmd->commandes[1] == NULL)
	{
		printf("%s\n", cmd->commandes[0]);
		exit(100);
	}
	if (isnum(cmd->commandes[1]) == -1)
	{
		printf("%s\n", cmd->commandes[0]);
		write(1, "bash: ", 6);
		printerr(cmd->commandes[0], cmd->commandes[1], "numeric argument required");
		exit(255);
	}
	else if (cmd->commandes[2])
		exit_ut(cmd->commandes[0]);
	else
	{
		printf("%s\n", cmd->commandes[0]);
		// g_globe.exit_status = isnum(cmd->commandes[1]);
		exit(10);
		// exit(g_globe.exit_status);

	}
}
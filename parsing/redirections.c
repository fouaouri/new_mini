#include "minishell.h"

# include <fcntl.h>
# include <sys/errno.h>

# define ENSFD ": No such file or directory\n"
# define EPD ": Permission denied\n"

static void	detect_error(char *msg, char *arg)
{
	char	*error_msg;

	if (!msg && !arg)
	{
		error_msg = ft_strjoin(ft_strdup("minishell: "), strerror(errno));
		ft_putstr_fd(error_msg, 2);
		ft_putchar_fd('\n', 2);
		free (error_msg);
	}
	else if (!msg && arg)
	{
		arg = ft_strjoin(ft_strdup("minishell: "), arg);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		free (arg);
	}
}

void	print_error(char *msg, char *arg, int status)
{
	char	*error_msg;

	if (msg && !arg)
		ft_putstr_fd(msg, 2);
	else if ((!msg && !arg) || (!msg && arg))
		detect_error(msg, arg);
	else
	{
		arg = ft_strjoin(ft_strdup("minishell: "), arg);
		error_msg = ft_strjoin(arg, msg);
		ft_putstr_fd(error_msg, 2);
		free (error_msg);
	}
	if (status != -1)
		exit(status);
}



int	input_redirection(char *infile)
{
	int	fd;

	if (access (infile, F_OK))
	{
		print_error(ENSFD, infile, -1);
		return (-1);
	}
	if (access (infile, R_OK))
	{
		print_error(EPD, infile, -1);
		return (-1);
	}
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		print_error(NULL, NULL, -1);
		return (-1);
	}
	return (fd);
}

int	output_redirection(char *outfile)
{
	int	fd;

	if (access (outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		print_error(EPD, outfile, -1);
		return (-1);
	}
	fd = open (outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(NULL, NULL, -1);
		return (-1);
	}
	return (fd);
}

int	append_output(char *outfile)
{
	int	fd;

	if (!access (outfile, F_OK) && access(outfile, W_OK))
	{
		print_error(EPD, outfile, -1);
		return (-1);
	}
	fd = open (outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(NULL, NULL, -1);
		return (-1);
	}
	return (fd);
}

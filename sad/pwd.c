#include "minishell.h"

char	*null_buffer(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	return (str);
}

char	*__pwd__(void)
{
	char	*buffer;
	char	*tmp;
	char	*pwd;
	char	str[1024];

	tmp = getcwd(str, sizeof(str));
	if (tmp)
	{
		buffer = ft_strdup(tmp);
		return (buffer);
	}
	else
	{
		pwd = getenv("PWD");
		if (pwd != NULL)
			return (pwd);
	}
	return (NULL);
}
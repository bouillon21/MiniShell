#include "minishell.h"

int	ft_pwd()
{
	char buf[1024];

	if (getcwd(buf, 1024))
	{
		printf("%s\n", buf);
		return(1);
	}
	else
		return(0);
}
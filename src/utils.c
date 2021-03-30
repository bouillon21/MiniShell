#include "minishell.h"

void	free_array(char ***mas)
{
	int	i;

	i = 0;
	while ((*mas)[i])
	{
		free((*mas)[i]);
		i++;
	}
	free(*mas);
}
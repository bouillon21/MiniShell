#include "minishell.h"

void	string_to_lower(char **mas)
{
	int i;

	i = -1;
	while (mas[0][++i] != 0)
		mas[0][i] = ft_tolower(mas[0][i]);
}

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
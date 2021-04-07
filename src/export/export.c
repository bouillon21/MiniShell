#include "minishell.h"

void	print_export(t_all *all)
{
	int	i;
	int	j;
	char	**env_sort;

	i = -1;
	env_sort = env_join(all->env);
	while (env_sort[++i])
	{
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (env_sort[i][++j] != '\0')
		{
			write(1,&env_sort[i][j], 1);
			if (env_sort[i][j] == '=')
			{
				ft_putchar('"');
				while (env_sort[i][++j] != '\0')
					write(1,&env_sort[i][j], 1);
				ft_putchar('"');
				break;
			}
		}
		write(1,"\n", 1);
	}
	free_array(&env_sort);
}

void	sort_export(char ***env_sort)
{
	char	*tmp;

	
}

void	export(t_all *all)
{
	if (all->token->args[1] == NULL)
	{
		print_export(all);
	}
}
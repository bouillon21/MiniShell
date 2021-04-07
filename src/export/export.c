#include "minishell.h"

void	print_export(t_all *all)
{
	int	i;
	int	j;
	char	**env_sort;

	i = -1;
	env_sort = sort_export(all);
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

char	**sort_export(t_all *all)
{
	char	**env_sort;
	char	*tmp;
	int	i;
	int	j;

	i = 0;
	j = -1;
	env_sort = env_join(all->env);
	while (++i < ft_lstsize(all->env))
	{
		j = -1;
		while (++j < ft_lstsize(all->env) - i)
		{
			if(ft_strcmp(env_sort[j], env_sort[j+1]) > 0)
			{
				tmp = env_sort[j];
				env_sort[j] = env_sort[j+1];
				env_sort[j+1] = tmp;
			}
		}
	}
	return(env_sort);
}

void	export(t_all *all)
{
	if (all->token->args[1] == NULL)
		print_export(all);
}
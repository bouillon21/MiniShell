#include "minishell.h"

int	check_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (1);
		i++;
	}
	return (-1);
}

void	shlvl(t_all *all, t_list *env)
{
	int		tmp;
	char	*t;

	if (check_digit(env->content->value))
	{
		tmp = ft_atoi(env->content->value);
		if (tmp == 999)
			env_add(all, "SHLVL", "");
		else if (tmp < 0)
			env_add(all, "SHLVL", "0");
		else if (tmp < 1000)
		{
			t = ft_itoa(tmp + 1);
			env_add(all, "SHLVL", t);
			free(t);
		}
		else
		{
			error_message("shell level (1000) too high, resetting to 1", all);
			env_add(all, "SHLVL", "1");
		}
	}
	else
		env_add(all, "SHLVL", "1");
}

void	shell_level(t_all *all)
{
	t_list	*env;

	env = env_srh(all, "SHLVL");
	if (!env || env->content->value == NULL)
		env_add(all, "SHLVL", "1");
	else
		shlvl(all, env);
}

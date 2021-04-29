#include "minishell.h"

int	qwe(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_all *all)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (all->token->args[1] && !ft_strncmp(all->token->args[1], "-n", 2)
		&& qwe(all->token->args[1]))
		flag = 1;
	if (flag)
		i++;
	while (all->token->args[i])
	{
		ft_putstr_fd(all->token->args[i], 1);
		if (all->token->args[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!flag)
		ft_putchar('\n');
}

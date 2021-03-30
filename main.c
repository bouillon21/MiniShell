#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*ad[3];

	ad[0] = ft_strdup("minishell");
	ad[1] = ft_strdup("uipiouiuy");
	ad[1] = NULL;

	get_save_env(&env, envp);

	char *app = ft_strdup("ls");
	exec(ad, env, app);
	sleep(1);
	while (1)
	{}
}
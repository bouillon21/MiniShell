#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
	t_list	*env;
	get_save_env(&env, envp);


	char	*ad[3];

	ad[0] = ft_strdup("minishell");
	ad[1] = ft_strdup("uipiouiuy");
	ad[1] = NULL;

	// char	*app = ft_strdup("./ls");
	// exec(ad, env, app);

	// char	**env_copy;
	// env_copy = env_join(env);

	// int i =-1;
	// while (env_copy[++i])
	// {
	// 	printf("%s\n",env_copy[i]);
	// }
	// sleep(1);
	// printf_env(env);
	cd(&env, NULL);
	cd(&env, "..");
	// cd(&env, "-");
	ft_pwd();
	sleep(2);
	// printf_env(env);
	while (1)
	{}
}
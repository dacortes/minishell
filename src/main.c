# include <minishell.h>

//char *path = getenv("lolasasddc,s knjwj"); // user // path

/* crear funcion  que combiarte el t_env en char **env */

int mini_rush_plus(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell	mini;

	ft_bzero(&mini, sizeof(t_minishell));
	mini.env = init_env(env);
	while ("The stupid evaluator is testing")
	{
		// _env(mini.env, 1);
		// _unset(&mini.env, "SHLVL");
		// ft_printf("--------------------------------------------\n");
		// _env(mini.env, 1);
		mini.get_line = readline("patata: ");
		parsing(&mini);
		printf_token(mini.token, TUR);
		if (mini.get_line)
		{
			clear_token(&mini.token);
			free(mini.get_line);
			mini.get_line = NULL;
		}
		if (mini.get_line && mini.get_line[0] == '\0')
		{
			clear_token(&mini.token);
			clear_env(&mini.env);
			free(mini.get_line);
			break ; 
		}
		ft_printf("%sstatus:%s %d\n", BLUE, END, mini.status);
	}
	clear_env(&mini.env);
	clear_token(&mini.token);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	return (mini_rush_plus(argc, argv, env));
}

# include <minishell.h>

//char *path = getenv("lolasasddc,s knjwj"); // user // path

/* crear funcion  que combiarte el t_env en char **env */

int mini_rush_plus(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell	mini;

	mini.env = init_env(env);
	if  (!mini.env)
		printf("toy aqui");
	while ("The stupid evaluator is testing")
	{
		mini.get_line.read_line = readline("patata: ");
		mini.status = parsing(&mini);
		if (mini.get_line.read_line)
		{
			clear_token(&mini.token);
			free(mini.get_line.read_line );
			mini.get_line.read_line = NULL;
		}
		if (mini.get_line.read_line && mini.get_line.read_line[0] == '\0')
		{
			clear_token(&mini.token);
			free(mini.get_line.read_line);
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
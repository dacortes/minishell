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
		if  (parsing(&mini) == 1)
		{
			ft_printf("Error: line\n");
		}
		if (mini.get_line.read_line )
			free(mini.get_line.read_line );
		if (mini.get_line.read_line[0] == '\0')
		{
			free(mini.get_line.read_line);
			break ; 
		}
	}
	clear_env(&mini.env);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	return (mini_rush_plus(argc, argv, env));
}
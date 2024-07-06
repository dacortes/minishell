# include <minishell.h>

//char *path = getenv("lolasasddc,s knjwj"); // user // path

/* crear funcion  que combiarte el t_env en char **env */

int mini_rush_plus(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_env *foo = init_env(env);
	if  (!foo)
		printf("toy aqui");
	t_env *iter = foo;
	int i = 1;
	while (iter && iter->next)
	{
		ft_printf("env #[%d] ----- \n", i);
		ft_printf("key: %d %s\n", i, iter->key);
		// ft_printf("value: %s\n", i, iter->value);
		// ft_printf("eql: %c\n", i, iter->eql);
		iter = iter->next;
		i++;
	}
	
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	return (mini_rush_plus(argc, argv, env));
}
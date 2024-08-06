/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/06 08:03:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

char	*ft_strjoin_max(char **need)
{
	char	*join;
	int		iter;
	int		len;

	if (!need || !*need)
		return (NULL);
	iter = 0;
	len = 0;
	while (need[iter])
		len += ft_strlen(need[iter++]);
	join = ft_calloc(len + 1, sizeof(char));
	if (!join)
		exit (error_msg(MALLOC, 1, "ft_strjoin_max: join"));
	iter = 0;
	while (need[iter])
	{
		ft_strlcat(join, need[iter], len + ft_strlen(need[iter]) + 1);
		iter++;
	}
	return (join);
}

int	test_heredoc(t_minishell *mini)
{
	pid_t	redir[2];
	t_basic	*iter;
	t_basic	*env;

	redir[0] = 0;
	redir[1] = 0;
	env = mini->env;
	iter = mini->token;
	while (iter && iter->data.token->type != SYN_ERROR && mini->status == 0)
	{
		is_heredoc(env, iter, redir, &mini->status);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int	init_mini_rush_plus(t_minishell *mini, char **env)
{
	term_init();
	ft_bzero(mini, sizeof(t_minishell));
	mini->env = init_env(env);
	mini->user = ft_strdup(search_env(mini->env, "USER", VALUE));
	if (!mini->user)
		exit(error_msg(MALLOC, 1, "init_mini_rush_plus: user"));
	if (mini->user && !*mini->user)
	{
		free(mini->user);
		mini->user = ft_strdup("UWU");
	}
	mini->cur_dir = get_pwd();
	mini->old_dir = ft_strdup(search_env(mini->env, "OLDPWD", VALUE));
	if (!mini->old_dir)
		exit(error_msg(MALLOC, 1, "init_mini_rush_plus: old_dir"));
	return (EXIT_SUCCESS);
}

int	prompt(t_minishell *mini)
{
	char	*need[8];
	char	*join;

	need[0] = "["TUR;
	need[1] = mini->user;
	need[2] = END"]";
	need[3] = TUR" ➜ "CYAN;
	if (!mini->cur_dir[1])
		need[4] = ft_strrchr(mini->cur_dir, '/');
	else
		need[4] = &ft_strrchr(mini->cur_dir, '/')[1];
	need[5] = BLUE" git:(aqui va la rama)";
	need[6] = TUR" 🗂"CYAN"  ᐅ "END;
	need[7] = NULL;
	join = ft_strjoin_max(need);
	mini->get_line = readline(join);
	free(join);
	return (EXIT_SUCCESS);
}

int	mini_rush_plus(int argc, char **argv, char **env)
{
	t_minishell	mini;
	
	(void)argc;
	(void)argv;

	init_mini_rush_plus(&mini, env);
	while ("The stupid evaluator is testing")
	{
		signal(SIGINT, _sigint);
		signal(SIGQUIT, SIG_IGN);
		prompt(&mini);
		parsing(&mini);
		test_heredoc(&mini);
		printf_token(mini.token);
		if (mini.get_line && *mini.get_line)
			add_history(mini.get_line);
		if (!mini.get_line)
			break ;
		if (mini.get_line)
		{
			free_list(mini.token, free_token);
			free(mini.get_line);
			mini.get_line = NULL;
		}
		ft_printf("%s [%d]\n", BLUE"status:"END, mini.status);
	}
	free_minishell(&mini, FALSE);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	return mini_rush_plus(argc, argv, env);
}

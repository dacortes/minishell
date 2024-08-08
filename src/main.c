/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/08 08:26:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	mini->user = protected(ft_strdup(search_env(mini->env, "USER", VALUE)),
		"init_mini_rush_plus: user");
	if (mini->user && !*mini->user)
	{
		free(mini->user);
		mini->user = ft_strdup("UWU");
	}
	mini->cur_dir = get_pwd();
	mini->old_dir = protected(ft_strdup(search_env(mini->env, "OLDPWD", VALUE)),
		"init_mini_rush_plus: old_dir");
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
		to_array(&mini);
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
	return (mini_rush_plus(argc, argv, env));
}

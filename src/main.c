/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/13 18:15:39 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_mini_rush_plus(t_minishell *mini, char **env)
{
	term_init();
	ft_bzero(mini, sizeof(t_minishell));
	mini->term_fd[0] = dup(0);
	mini->term_fd[1] = dup(1);
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
		get_status(TRUE, mini.status);
		signal(SIGINT, _sigint);
		signal(SIGQUIT, SIG_IGN);
		prompt(&mini);
		if (mini.get_line && *mini.get_line)
			add_history(mini.get_line);
		if (!mini.get_line)
			break ;
		if (!parsing(&mini))
			manager(&mini);
		mini.status = get_status(TRUE, mini.status);
		if (mini.get_line && *mini.get_line)
		{
			free_list(mini.token, free_token);
			ft_free(&mini.get_line, NULL);
			mini.token = NULL;
		}
		if (mini.get_line && !*mini.get_line)
			mini.status = 0;
		ft_printf("%s [%d]\n", BLUE"status:"END, mini.status);
	}
	free_minishell(&mini, FALSE);
	close(mini.term_fd[0]);
	close(mini.term_fd[1]);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	return (mini_rush_plus(argc, argv, env));
}

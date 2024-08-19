/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/19 16:37:08 by dacortes         ###   ########.fr       */
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
	mini->user = protected(ft_strdup(search_env(mini->env, "USER", VALUE)), \
												"init_mini_rush_plus: user");
	if (mini->user && !*mini->user)
	{
		free(mini->user);
		mini->user = ft_strdup("UWU");
	}
	mini->cur_dir = get_pwd();
	mini->old_dir = protected(ft_strdup(search_env(\
				mini->env, "OLDPWD", VALUE)), "init_mini_rush_plus: old_dir");
	return (EXIT_SUCCESS);
}

void	restart_mini(t_minishell *mini)
{
	add_history(mini->get_line);
	free_list(mini->token, free_token);
	ft_free(&mini->get_line, NULL);
	mini->token = NULL;
}

int	mini_rush_plus(char **env)
{
	t_minishell	mini;

	init_mini_rush_plus(&mini, env);
	while (1 == 1)
	{
		get_status(TRUE, mini.status);
		mini.status = 0;
		prompt(&mini);
		if (!mini.get_line)
			break ;
		if (!parsing(&mini))
			printf_token(mini.token);
		do_heredoc(&mini);
		if (!mini.status)
			manager(&mini);
		if (mini.get_line && *mini.get_line)
			restart_mini(&mini);
		if (mini.get_line && !*mini.get_line)
		{
			mini.status = 0;
			ft_free(&mini.get_line, NULL);
		}
	}
	free_minishell(&mini, FALSE);
	return (get_status(FALSE, mini.status));
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	return (mini_rush_plus(env));
}

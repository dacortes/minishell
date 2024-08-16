/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/16 10:09:32 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_break_it(int flag, int value)
{
	static int	_break;

	if (flag == TRUE)
		_break = value;
	return (_break);
}

void break_it(int signal)
{
	if (signal == SIGINT)
		get_break_it(TRUE, 1);
}

int	do_heredoc(t_minishell *mini)
{
	t_basic	*iter;
	t_token	*token;
	int		redir[2];

	iter = mini->token;
	get_break_it(TRUE, 0);
	signal(SIGINT, break_it);
	signal(SIGQUIT, SIG_IGN);
	while (iter)
	{
		if (get_break_it(FALSE, 0) == TRUE)
			break ;
		token = iter->data.token;
		if (token->type == R_HER)
			open_heredoc(mini, iter, redir);
		if (token->type == S_SHELL)
			do_heredoc(token->token_content.subs);
		if (token->type == SYN_ERROR)
			break ;
		iter = iter->next;
	}
	if (mini->status)
	{
		iter = mini->token;
		while (iter)
		{
			token = iter->data.token;
			if (token->type == R_HER)
			{
				if (token->token_content.redir_here[0] > 0)
					close(token->token_content.redir_here[0]);
			}
			iter = iter->next;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

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
		mini.status = 0;
		signal(SIGINT, _sigint);
		signal(SIGQUIT, SIG_IGN);
		prompt(&mini);
		if (mini.get_line && *mini.get_line)
			add_history(mini.get_line);
		if (!mini.get_line)
			break ;
		parsing(&mini);
		do_heredoc(&mini);
		if (!mini.status)
			manager(&mini);
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

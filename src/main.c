/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/04 16:12:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>


// int	prompt(t_minishell *mini)
// {
// 	return (EXIT_SUCCESS);
// }

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

// int	init_mini_rush_plus(t_minishell *mini, char **env)
// {
// 	ft_bzero(mini, sizeof(t_minishell));
// 	mini->env = init_env(env);
// 	return (EXIT_SUCCESS);
// }

void	term_init(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == ERROR)
		exit (error_msg(PERROR, 1, "term_init: term"));
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == ERROR)
		exit (error_msg(PERROR, 1, "term_init: term"));
}

void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// get_stt(TRUE, 1);
	}
}

int	mini_rush_plus(int argc, char **argv, char **env)
{
	t_minishell	mini;
	
	(void)argc;
	(void)argv;

	ft_bzero(&mini, sizeof(t_minishell));
	mini.env = init_env(env);
	term_init();
	while ("The stupid evaluator is testing")
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		mini.get_line = readline("patata: ");
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

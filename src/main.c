/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/30 14:47:42 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

//char *path = getenv("lolasasddc,s knjwj"); // user // path

int test_heredoc(t_minishell *mini)
{
	t_token	*iter = mini->token;

	while (iter && iter->type != SYN_ERROR && mini->status == 0)
	{
		mini->status = is_stdinp(iter, mini->redir, &mini->status);
		mini->status = is_stdout(iter, mini->redir, &mini->status);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int	do_heredocs(t_minishell *mini)
{
	t_token	*iter = mini->token;

	while (iter && iter->type != SYN_ERROR)
	{
		mini->status = is_heredoc(iter, mini->redir, &mini->status);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}








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
		mini.get_line = readline("patata: ");
		if (mini.get_line && *mini.get_line)
			add_history(mini.get_line);
		parsing(&mini);
		printf_token(mini.token, TUR);
		do_heredocs(mini);
		if (!mini->status)
			manager(mini);
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

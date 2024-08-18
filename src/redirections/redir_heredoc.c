/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:50 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/18 17:26:47 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	read_heredoc(t_minishell *mini, t_basic *token, int *redir)
{
	t_basic *next;
	char	*line;

	next = token->next;
	while (next && next->data.token->content)
	{
		signal(SIGINT, handle_siginth);
		line = readline(ORANGE"> "END);
		if (!line || !ft_strncmp(next->data.token->content, line, -1))
		{
			free(line);
			line = NULL;
			break;
		}
		if (*line)
			line = expansion(mini, line);
		fd_printf(redir[1], "%s\n", line);
		free(line);
		line = NULL;
	}
	if (line && !*line)
		free(line);
	close(redir[1]);
	close(redir[0]);
	signal(SIGINT, SIG_DFL);
	exit(EXIT_SUCCESS);
}

int	open_heredoc(t_minishell *mini, t_basic *token, int *redir)
{
	pid_t	heredoc;
	int		status;

	if (token && token->data.token->type == R_HER)
	{
		if (pipe(redir))
			exit (error_msg(PERROR, 1, "is_heredoc: init: pipe heredoc"));
		heredoc = fork();
		if (heredoc == ERROR)
			exit (error_msg(PERROR, 1, "is_heredoc: init: child heredoc"));
		if (heredoc == CHILD)
		{
			if (redir[0] > 0)
				close(redir[0]);
			read_heredoc(mini, token, redir);
			exit(EXIT_SUCCESS);
		}
		if (waitpid(heredoc, &status, 0) == ERROR)
		{
			close(redir[0]);
			return (EXIT_FAILURE);
		}
		close(redir[1]);
		status = WEXITSTATUS(status);
		if (status && !mini->status)
			mini->status = status;
		token->data.token->token_content.redir_here[0] = redir[0];
	}
	return (EXIT_SUCCESS);
}

int	_heredoc(t_minishell *mini, t_basic *current)
{
	(void)mini;
	if (current && current->data.token->type == R_HER)
	{
		if (dup2(current->data.token->token_content.redir_here[0], 0) == ERROR)
			return (error_msg(PERROR, 1, "Dup2"));
		close(current->data.token->token_content.redir_here[0]);
	}
	return (EXIT_SUCCESS);
}

void	close_heredocs(t_minishell *mini)
{
	t_basic	*iter;
	t_token	*token;

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
		else if (token->type == S_SHELL)
			do_heredoc(token->token_content.subs);
		else if (token->type & SYN_ERROR)
			break ;
		iter = iter->next;
	}
	if (mini->status)
		close_heredocs(mini);
	return (EXIT_SUCCESS);
}

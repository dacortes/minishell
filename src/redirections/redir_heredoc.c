/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:50 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/17 10:56:42 by frankgar         ###   ########.fr       */
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

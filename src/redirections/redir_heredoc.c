/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:50 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/08 11:30:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int	read_heredoc(t_minishell *mini, t_basic *token, pid_t *redir)
{
	t_basic *next;
	char	*line;

	line = "init heredoc";
	next = token->next;
	while (line && next && next->data.token->content)
	{
		signal(SIGINT, handle_siginth);
		line = readline(ORANGE"> "END);
		if (line && ft_strncmp(next->data.token->content, line, -1) == FOUND)
		{
			free(line);
			break ;
		}
		else
		{
			if (line && *line)
				line = expansion(mini, line);
			fd_printf(redir[1], "%s", line);
		}
		free(line);
	}
	close(redir[1]);
	close(redir[0]);
	exit (EXIT_SUCCESS);
}

int	is_heredoc(t_minishell *mini, t_basic *token, pid_t *redir, int *status)
{
	pid_t	heredoc;

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
		}
		if (waitpid(heredoc, status, 0) == ERROR)
		{
			close(redir[0]);
			return (EXIT_FAILURE);
		}
		close(redir[1]);
		*status = WEXITSTATUS(*status);
	}
	return (*status);
}

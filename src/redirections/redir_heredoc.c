/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:50 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/27 08:43:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	read_heredoc(t_token *token, pid_t *redir)
{
	t_token *next;
	char	*line;

	line = "init heredoc";
	next = token->next;
	while (line && next && next->content)
	{
		line = readline(ORANGE"> "END);
		if (ft_strncmp(next->content, line, -1) == FOUND)
		{
			free(line);
			break ;
		}
		else
		{
			//hacer expanciones dentro del heredoc
			//line = expand_heredoc(line);
			fd_printf(redir[1], "%s", line);
		}
		free(line);
	}
	close(redir[0]);
	close(redir[0]);
	exit (EXIT_SUCCESS);
}

int	is_heredoc(t_token *current, pid_t *redir, int *status)
{
	pid_t	heredoc;

	if (current && current->type == R_HER)
	{
		if (pipe(redir))
			exit (error_msg(PERROR, 1, "is_heredoc: init: pipe heredoc"));
		heredoc = fork();
		if (heredoc == ERROR)
			exit (error_msg(PERROR, 1, "is_heredoc: init: child heredoc"));
		if (heredoc == CHILD)
		{
			if (redir[0] >= 0)
				close(redir[0]);
			read_heredoc(current, redir);
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

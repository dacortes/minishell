/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:50 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/14 16:15:40 by dacortes         ###   ########.fr       */
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
		if (!line || ft_strncmp(next->data.token->content, line, -1) == 0)
		{
			free(line);
			break;
		}
		if (*line)
			line = expansion(mini, line);
		fd_printf(redir[1], "%s\n", line);
		free(line);
	}
	close(redir[1]);
	close(redir[0]);
	exit(EXIT_SUCCESS);
}

int	open_heredoc(t_minishell *mini, t_basic *token, int *redir)
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
		if (waitpid(heredoc, &mini->status, 0) == ERROR)
		{
			close(redir[0]);
			return (EXIT_FAILURE);
		}
		close(redir[1]);
		mini->status = WEXITSTATUS(mini->status);
		token->data.token->token_content.redir_here = redir[0];
		ft_printf("dst: %d src: %d\n", token->data.token->token_content.redir_here, redir[0]);
	}
	return (EXIT_SUCCESS);
}



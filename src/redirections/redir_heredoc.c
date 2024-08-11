/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:50 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/11 08:00:13 by codespace        ###   ########.fr       */
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
	exit(EXIT_SUCCESS);
}

int	_heredoc(t_minishell *mini, t_basic *current)
{
	pid_t	child;
	int		redir[2];
	int		tmp;

	(void)tmp;
	if (current->data.token->type == R_HER)
	{
		if (pipe(redir) == ERROR)
			exit(error_msg(PERROR, 1, "is_heredoc: init: pipe heredoc"));
		child = fork();
		if (child == ERROR)
			exit(error_msg(PERROR, 1, "is_heredoc: init: fork"));
		if (child == CHILD)
			tmp = close(redir[0]) + read_heredoc(mini, current, redir);
		else
		{
			close(redir[1]);
			if (dup2(redir[0], STDIN_FILENO) == ERROR)
				return (close(redir[0]), error_msg(PERROR, 1, "Dup2 failed"));
			close(redir[0]);
			waitpid(child, &mini->status, 0);
			mini->status = WEXITSTATUS(mini->status);
		}
	}
	return (EXIT_SUCCESS);
}

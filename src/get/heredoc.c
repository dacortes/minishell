/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:41:37 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/26 16:46:35 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static int	read_heredoc(t_token **tk, int *fd)
{
	char	*inp;

	inp = "";
	if ((*tk)->type[3] == T_RDHD)
	{
		while (inp && (*tk)->next && (*tk)->next->arg)
		{
			inp = readline(O"> "E);
			if (ft_strncmp((*tk)->next->arg, inp, -1) == 0)
			{
				free (inp);
				break ;
			}
			else
				fd_printf(fd[1], "%s\n", inp);
			free (inp);
		}
	}
	close(fd[0]);
	close(fd[1]);
	exit (SUCCESS);
}

int	is_heredoc(t_token **tk, int *fd, int *stt)
{
	pid_t	hd;

	if ((*tk)->type[3] == T_RDHD)
	{
		if (pipe(fd) == ERROR)
			return (msg_error(E_PRR, 1, "heredoc"));
		hd = fork();
		if (hd == ERROR)
			exit (msg_error(E_PRR, -1, "heredoc"));
		if (!hd)
		{
			if (fd[0] >= 0)
				close(fd[0]);
			read_heredoc(tk, fd);
		}
		if (waitpid(hd, stt, 0) == ERROR)
		{
			close(fd[0]);
			return (ERROR);
		}
		close(fd[1]);
		fd[1] = -2;
		*stt = WEXITSTATUS(*stt);
	}
	return (*stt);
}

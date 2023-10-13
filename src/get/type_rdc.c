/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_rdc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:49:36 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/11 18:56:59 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	parse_open(t_token **tk, int type, int *fd)
{
	char *file;

	file = (*tk)->next->arg;
	if (type == INP)
	{
		if (access(file, F_OK) == ERROR)
			return (msg_error(E_NSF, 1, file));
		if (access(file, R_OK) == ERROR)
			return (msg_error(E_PRR, 1, file));
		fd[0] = open(file, O_RDONLY);
		if (fd[0] == ERROR)
			return (1);
	}
	else if (type == OUT)
	{
		if (!access(file, F_OK) && access(file, W_OK))
			return (msg_error(E_PRM, 1, file));
		fd[1] = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (fd[1] == ERROR)
			return (1);
	}
	return (SUCCESS);
}

int read_heredoc(t_token **tk, int *fd)
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
			free (inp);
		}
	}
	if (fd[0] == ERROR || fd[1] == ERROR)
	{
		close(fd[0]);
		close(fd[1]);
	}
	exit (SUCCESS);
}

int	is_heredoc(t_token **tk, int *fd, int *stt)
{
	pid_t	hd;
	int		tb[2];

	if (pipe(tb) == ERROR)
		return (msg_error(E_PRR, 1, "heredoc"));
	hd = fork();
	if (hd == ERROR)
		exit (msg_error(E_PRR, -1, "heredoc"));
	if (!hd)
		read_heredoc(tk, tb);
	if (fd[0] == ERROR || fd[1] == ERROR)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (waitpid(hd, stt, 0) == ERROR)
	{
		close(fd[0]);
		close(fd[1]);
	}
	*stt = WEXITSTATUS(*stt);
	return (*stt);
}

int is_stdinp(t_token **tk, int *fd, int *stt)
{
	if ((*tk)->type[3] == T_SIR)
	{
		(fd[0] >= 0) && close(fd[0]);
		(fd[1] >= 0) && close(fd[1]);
		(*stt == 0) && (*stt = parse_open(tk, INP, fd));
	}
	return (*stt);
}

int	is_stdout(t_token **tk, int *fd, int *stt)
{
	if ((*tk)->type[3] == T_SOR)
	{
		(fd[0] >= 0) && close(fd[0]);
		(fd[1] >= 0) && close(fd[1]);
		parse_open(tk, OUT, fd);
	}
	return (*stt);
}

int	is_append(t_token **tk, int *fd, int *stt)
{
	char *file;

	file = (*tk)->next->arg;
	if ((*tk)->type[3] == T_RDAP)
	{
		(fd[0] >= 0) && close(fd[0]);
		(fd[1] >= 0) && close(fd[1]);
		if (!access(file, F_OK) && access(file, W_OK))
			return (msg_error(E_PRM, 1, file));
		fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd[1] == ERROR)
			return (1);
	}
	return (*stt);
}

int	test_rdc(t_token **tk, int *fd, int *stt)
{
	is_heredoc(tk, fd, stt); // no funciona
	is_append(tk, fd, stt);
	is_stdinp(tk, fd, stt);
	is_stdout(tk, fd, stt);
	return (*stt);
}

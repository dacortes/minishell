/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:41:37 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/11 18:33:54 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static void	init_aux(t_aux *a, char *inp)
{
	ft_bzero(a, sizeof(t_aux));
	a->e = ft_strdup_exit(inp);
	a->tmp = a->e;
	a->tmp = ft_strchr(a->tmp, '$');
}

static char	*expand_hdoc(char *inp)
{
	t_aux	a;

	init_aux(&a, inp);
	while (a.tmp)
	{
		a.i = a.tmp - a.e;
		a.j = a.i + 1;
		while (a.e[a.j] && (ft_isalnum(a.e[a.j]) || (a.e[a.j] == '_')
				|| (a.e[a.j] == '?')))
			a.j++;
		a._key = ft_strndup(a.e + a.i + 1, a.j - a.i -1);
		if (ft_strlen(a._key) == 1 && a._key
			&& a._key[0] && a._key[0] == '?')
			a._val = ft_itoa((get_stt(FALSE, 0)));
		else
			a._val = ft_strdup_exit(search_env(get_env(0, NULL), a._key, VAL));
		free(a._key);
		swap_val(&a, a.i, a.j);
		free(a._val);
		free(inp);
		inp = ft_strdup_exit(a.e);
		a.tmp = ft_strchr(a.tmp, '$');
	}
	free(a.e);
	return (inp);
}
void	handle_siginth(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(1);
	}
}
static int	read_heredoc(t_token **tk, int *fd)
{
	char	*inp;

	inp = "";
	signal(SIGINT, handle_siginth);
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
			{
				inp = expand_hdoc(inp);
				fd_printf(fd[1], "%s\n", inp);
			}
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

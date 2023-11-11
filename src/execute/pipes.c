/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/11 10:02:59 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/* errors */
/*bash: unset: `1a': not a valid identifier
cd ""
cd ''
echo ""''""''""''
echo ''""""a*/

int	ft_execute(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	int	stt;

	stt = 0;
	ex->stt = is_built_ins(ln, g);
	if (g && *g && !ex->stt)
		pp_rdc_built_ins(sh, ln, g, ex);
	if (ex->stt == ERROR)
	{
		ex->stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
		if (ex->stt == ERROR)
			pp_rdc_bin(g, ex, &stt);
	}
	if (!stt && g && *g && !ex->stt && ex->cmd)
	{
		rdc_stdinp(g, FTH);
		rdc_stdout(g, FTH);
		(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
		exit(127);
	}
	exit (0);
}

int	ft_dup2(int prev, int curr, int std)
{
	close(prev);
	dup2(curr, std);
	close(curr);
	return (SUCCESS);
}

int	init_pipex(t_pipex *p, t_exe *ex)
{
	p->chds = ft_calloc(ex->pipe + 1, sizeof(pid_t));
	if (!p->chds)
		exit (msg_error(E_MEM, E_MEM, NULL));
	p->i = 0;
	p->tmp[0] = dup(STDIN_FILENO);
	p->tmp[1] = dup(STDOUT_FILENO);
	return (SUCCESS);
}

int	restore_and_waitpid(t_pipex *p, t_exe *ex)
{
	dup2(p->tmp[0], STDIN_FILENO);
	close(p->tmp[0]);
	dup2(p->tmp[1], STDOUT_FILENO);
	close(p->tmp[1]);
	p->i = 0;
	while (p->i <= ex->pipe)
	{
		if (waitpid(p->chds[p->i], &ex->stt, 0) == p->last)
			ex->stt = WEXITSTATUS(ex->stt);
		p->i++;
	}
	free (p->chds);
	return (SUCCESS);
}

int	pipes(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	t_pipex	p;

	init_pipex(&p, ex);
	while (p.i <= ex->pipe)
	{
		if (p.i < ex->pipe)
			if (pipe(p.fds) == ERROR)
				exit(msg_error(E_PRR, 1, "pipe"));
		p.chds[p.i] = fork();
		(p.i == ex->pipe) && (p.last = p.chds[p.i]);
		if (p.chds[p.i] == ERROR)
			exit (msg_error(E_PRR, 1, "fork"));
		if (!p.chds[p.i])
		{
			if (p.i < ex->pipe)
				ft_dup2(p.fds[0], p.fds[1], STDOUT_FILENO);
			ft_execute(sh, ln, g, ex);
		}
		p.i++;
		((*g) && (*g)->next && ((*g) = (*g)->next));
		ft_dup2(p.fds[1], p.fds[0], STDIN_FILENO);
	}
	restore_and_waitpid(&p, ex);
	return (SUCCESS);
}

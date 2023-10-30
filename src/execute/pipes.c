/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/30 18:28:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

void init_pipes(int *fds, int n_pipes)
{
	int	i;

 	i = 0;
	while (i < n_pipes)
	{
		if (pipe(fds + i * 2) == ERROR)
			exit(msg_error(E_PRR, 1, "pipes"));
		i++;
	}
}

void clear_pipes(int *fds, int n_pipes)
{
	int i;

	i = 0;
	while (i < n_pipes * 2)
		close(fds[i++]);
}

// int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
// {
//     (void)ln;
//     int		fds[ex->pipe * 2];
//     pid_t	chds[ex->pipe + 1];
//     t_aux	a;

//     init_pipes(fds, ex->pipe);
//     ft_bzero(&a, sizeof(t_aux));
//     while (a.i <= ex->pipe)
//     {
//         chds[a.i] = fork();
//         if (chds[a.i] == ERROR)
//             exit(msg_error(E_PRR, 1, "fork"));
//         if (!chds[a.i])
//         {
//             if (a.i < ex->pipe)
//                 dup2(fds[a.i * 2 + 1], STDOUT_FILENO);
//             if (a.i > 0)
//                 dup2(fds[(a.i - 1) * 2], STDIN_FILENO);
//             clear_pipes(fds, ex->pipe);
//             ex->stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
//             ex->stt = execve(ex->cmd, (*g)->arg, ex->env);
//             exit(127);
//         }

//         a.i++;
//         (*g && (*g)->next) && ((*g) = (*g)->next);
//     }
//     clear_pipes(fds, ex->pipe);
//     while (a.c <= ex->pipe)
//     {
//         waitpid(chds[a.c], &ex->stt, 0);
// 		 ex->stt = WEXITSTATUS(ex->stt);
//         a.c++;
//     }
// 	ft_printf(B"stt error: %d\n"E, ex->stt);
//     return SUCCESS;
// }

static int	rdc_built_ins(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	rdc_stdinp(g, FTH);
	rdc_stdout(g, FTH);
	exe_built_ins(sh, ln, g, &ex->stt);
	if (dup2(fd[0], STDIN_FILENO) == ERROR)
		return (1);
	if (dup2(fd[1], STDOUT_FILENO) == ERROR)
		return (1);
	close(fd[0]);
	close(fd[1]);
	fd[0] = -2;
	fd[1] = -2;
	exit (SUCCESS);
}

static int	rdc_bin(t_get **g, t_exe *ex, int *stt)
{
	*stt = is_bin(ex);
	if (!stt)
	{
		ex->stt = *stt;
		rdc_stdinp(g, CHD);
		rdc_stdout(g, CHD);
		(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
		exit (127);
		(ex->stt != 0) && (ex->stt = msg_error(E_BADINT, E_PRM, ex->cmd));
	}
	clear_cmd(ex, 1);
	return (SUCCESS);
}

/*
	ls | ls | ls  | ls | ls|a
	error: muestra todo en la estandar outpu
	dacortes➜minishell 🗂 ᐅ Makefile
	mini: Makefile: command not found
	dacortes➜minishell 🗂 ᐅ README.md
	mini: README.md: command not found
	dacortes➜minishell 🗂 ᐅ a.test
	mini: a.test: command not found
	dacortes➜minishell 🗂 ᐅ h.test
	mini: h.test: command not found
	dacortes➜minishell 🗂 ᐅ inc
	mini: inc: command not found
	dacortes➜minishell 🗂 ᐅ lib
	mini: lib: command not found
	dacortes➜minishell 🗂 ᐅ minishell
	mini: minishell: command not found
	dacortes➜minishell 🗂 ᐅ p.test
	mini: p.test: command not found
	dacortes➜minishell 🗂 ᐅ src
	mini: src: command not found
*/
int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	int		fds[ex->pipe * 2];
	pid_t	chds[ex->pipe + 1];
	t_aux	a;

	init_pipes(fds, ex->pipe);
	ft_bzero(&a, sizeof(t_aux));
	while (a.i <= ex->pipe)
	{
		chds[a.i] = fork();
		if (chds[a.i] == ERROR)
			exit(msg_error(E_PRR, 1, "fork"));
		if (!chds[a.i])
		{
			int stt = 0;
			if (a.i < ex->pipe)
				dup2(fds[a.i * 2 + 1], STDOUT_FILENO);
			if (a.i > 0)
				dup2(fds[(a.i - 1) * 2], STDIN_FILENO);
			clear_pipes(fds, ex->pipe);
			ex->stt = is_built_ins(ln, g);
			if (g && *g && !ex->stt)
				rdc_built_ins(sh, ln, g, ex);
			if (ex->stt == ERROR)
			{
				ex->stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
				if (ex->stt == ERROR)
					rdc_bin(g, ex, &stt);
			}
			if (!stt && g && *g && !ex->stt && ex->cmd)
			{
				rdc_stdinp(g, CHD);
				rdc_stdout(g, CHD);
				(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
				exit (127);
			}
		}
		a.i++;
		(*g && (*g)->next) && ((*g) = (*g)->next);
	}
	clear_pipes(fds, ex->pipe);
	while (a.c <= ex->pipe)
	{
		waitpid(chds[a.c], &ex->stt, 0);
		 ex->stt = WEXITSTATUS(ex->stt);
		a.c++;
	}
	ft_printf(B"stt error: %d\n"E, ex->stt);
	return SUCCESS;
}
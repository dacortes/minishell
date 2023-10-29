/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/29 09:40:38 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

int	init_pipes(t_get **g, t_exe *e)
{
	t_get	*iter;
	int		num;

	num = 0;
	iter = *g;
	while (iter && num <= e->pipe)
	{
		if (pipe(iter->tb) == ERROR)
			return (msg_error(E_PRR, 1, "heredoc"));
		num++;
		iter = iter->next;
	}
	return (SUCCESS);
}

int	clear_pipes(t_get **g)
{
	t_get	*iter;
	int		num;

	num = 0;
	iter = *g;
	while (iter)
	{
		if (iter->tb[0] >= 0)
			close(iter->tb[0]);
		if (iter->tb[1] >= 0)
			close(iter->tb[1]);
		iter = iter->next;
	}
	return (SUCCESS);
}

int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	pid_t	*chds;
	t_aux	a;
	t_get	*iter;
	(void)ln;

	chds = ft_calloc(ex->pipe + 1, sizeof(pid_t));
	if (!chds)
		exit (msg_error(E_MEM, E_EXIT, NULL));
	ft_bzero(&a, sizeof(t_aux));
	iter = *g;
	init_pipes(g, ex);
	while (a.i <= ex->pipe)
	{
		chds[a.i] = fork();
		if (chds[a.i] == 0)
		{
			
			if (a.i == 0)
			{
				close(iter->tb[0]);
				close(iter->next->tb[0]);
				close(iter->next->tb[1]);
				dup2(iter->tb[1], 1);
				close(iter->tb[1]);
				ex->stt = get_path(ex, iter, search_env((*sh)->env, "PATH", VAL));
				ex->stt = execve(ex->cmd, iter->arg, ex->env);
				exit (127);
			}
			else if (a.i == 1)
			{
				close(iter->tb[1]);
				close(iter->next->tb[0]);
				close(iter->next->tb[1]);
				dup2(iter->tb[0], 0);
				close(iter->tb[0]);
				ex->stt = get_path(ex, iter->next, search_env((*sh)->env, "PATH", VAL));
				ex->stt = execve(ex->cmd, iter->next->arg, ex->env);
				exit (127);
			}
		}
		a.i++;
		// iter = iter->next;
	}
	clear_pipes(g);
	while (a.c <= ex->pipe)
	{
		waitpid(chds[a.c++], &ex->stt, 0);
		ex->stt = WEXITSTATUS(ex->stt);
	}
	free(chds);
	return (SUCCESS);
}


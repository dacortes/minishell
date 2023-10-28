/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/28 14:57:51 by dacortes         ###   ########.fr       */
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

int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	pid_t	*chds;
	t_aux	a;
	t_get	*iter;
	(void)sh;
	(void)ln;

	chds = ft_calloc(ex->pipe + 1, sizeof(pid_t));
	if (!chds)
		exit (msg_error(E_MEM, E_EXIT, NULL));
	ft_bzero(&a, sizeof(t_aux));
	iter = *g;
	pipe(iter->tb);
	pipe(iter->next->tb);
	while (a.i <= ex->pipe)
	{
		chds[a.i] = fork();
		if (chds[a.i] == 0)
		{
			/* 
				< cierras el pipe de entrada y redireciona el 0 al fd
				> cierras el pipe de entrada y redireciona el 1 al fd*		
			*/
			if (a.i == 0)
			{
				close(iter->tb[0]);
				close(iter->next->tb[0]);
				close(iter->next->tb[1]);
				dup2(1, iter->tb[1]);
				close(iter->tb[1]);
				ex->stt = get_path(ex, iter, search_env((*sh)->env, "PATH", VAL));
				ex->stt = execve(ex->cmd, iter->arg, ex->env);
				printf("Error 1: %d\n", ex->stt);
			}
			else if (a.i == 1)
			{
				close(iter->tb[1]);
				close(iter->next->tb[0]);
				close(iter->next->tb[1]);
				dup2(0, iter->tb[0]);
				close(iter->tb[0]);
				ex->stt = get_path(ex, iter->next, search_env((*sh)->env, "PATH", VAL));
				ex->stt = execve(ex->cmd, iter->next->arg, ex->env);
				printf("Error 2: %d\n", ex->stt);
			}
		}
		a.i++;
		// iter = iter->next;
	}
	/*  cerrar todos los tb */
	close(iter->tb[0]);
	close(iter->tb[1]);
	close(iter->next->tb[0]);
	close(iter->next->tb[1]);
	while (a.c <= ex->pipe)
		waitpid(chds[a.c++], NULL, 0);
	free(chds);
	return (SUCCESS);
}


// int	pipes(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
// {
// 	t_get	*iter;
// 	int		num;

// 	num = 0;
// 	iter = *g;
// 	if (!ex->stt && ex->pipe)
// 	{
// 		while (iter && num <= ex->pipe)
// 		{
			
// 			num++;
// 			iter = iter->next;
// 		}
// 	}
// 	return (SUCCESS);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/29 11:09:09 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

// int	init_pipes(t_get **g, t_exe *e)
// {
// 	t_get	*iter;
// 	int		num;

// 	num = 0;
// 	iter = *g;
// 	while (iter && num <= e->pipe)
// 	{
// 		if (pipe(iter->tb) == ERROR)
// 			return (msg_error(E_PRR, 1, "heredoc"));
// 		num++;
// 		iter = iter->next;
// 	}
// 	return (SUCCESS);
// }

// int	clear_pipes(t_get **g)
// {
// 	t_get	*iter;
// 	int		num;

// 	num = 0;
// 	iter = *g;
// 	while (iter)
// 	{
// 		if (iter->tb[0] >= 0)
// 			close(iter->tb[0]);
// 		if (iter->tb[1] >= 0)
// 			close(iter->tb[1]);
// 		iter = iter->next;
// 	}
// 	return (SUCCESS);
// }

// int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
// {
// 	pid_t	*chds;
// 	t_aux	a;
// 	t_get	*iter;
// 	(void)ln;

// 	chds = ft_calloc(ex->pipe + 1, sizeof(pid_t));
// 	if (!chds)
// 		exit (msg_error(E_MEM, E_EXIT, NULL));
// 	ft_bzero(&a, sizeof(t_aux));
// 	iter = *g;
// 	init_pipes(g, ex);
// 	while (a.i <= ex->pipe)
// 	{
// 		chds[a.i] = fork();
// 		if (chds[a.i] == 0)
// 		{
			
// 			if (a.i == 0)
// 			{
// 				close(iter->tb[0]);
// 				close(iter->next->tb[0]);
// 				close(iter->next->tb[1]);
// 				dup2(iter->tb[1], 1);
// 				close(iter->tb[1]);
// 				ex->stt = get_path(ex, iter, search_env((*sh)->env, "PATH", VAL));
// 				ex->stt = execve(ex->cmd, iter->arg, ex->env);
// 				exit (127);
// 			}
// 			else if (a.i == 1)
// 			{
// 				close(iter->tb[1]);
// 				close(iter->next->tb[0]);
// 				close(iter->next->tb[1]);
// 				dup2(iter->tb[0], 0);
// 				close(iter->tb[0]);
// 				ex->stt = get_path(ex, iter->next, search_env((*sh)->env, "PATH", VAL));
// 				ex->stt = execve(ex->cmd, iter->next->arg, ex->env);
// 				exit (127);
// 			}
// 		}
// 		a.i++;
// 		// iter = iter->next;
// 	}
// 	clear_pipes(g);
// 	while (a.c <= ex->pipe)
// 	{
// 		waitpid(chds[a.c++], &ex->stt, 0);
// 		ex->stt = WEXITSTATUS(ex->stt);
// 	}
// 	free(chds);
// 	return (SUCCESS);
// }

// int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
// {
// 	pid_t	*chds;
// 	t_aux	a;
// 	t_get	*iter;
// 	(void)ln;

// 	chds = ft_calloc(ex->pipe + 1, sizeof(pid_t));
// 	if (!chds)
// 		exit (msg_error(E_MEM, E_EXIT, NULL));
// 	ft_bzero(&a, sizeof(t_aux));
// 	iter = *g;
// 	init_pipes(g, ex);
// 	while (a.i <= ex->pipe)
// 	{
// 		chds[a.i] = fork();
// 		if (!chds[a.i])
// 		{
// 			if (!a.i)
// 			{
// 				pid_t	inp;
// 				pid_t	out;

// 				inp = -1;
// 				out = -1;
// 				(iter->next) && (inp = iter->next->tb[0]);
// 				(iter->next) && (out = iter->next->tb[1]);
// 				if (inp >= 0)
// 				{
// 					close(iter->tb[0]);
// 					close(inp);
// 					close(out);
// 					if (dup2(iter->tb[1], STDOUT_FILENO) == ERROR)
// 						exit (msg_error(E_PRR, 1, "pipes"));
// 					close(iter->tb[1]);
// 					ex->stt = get_path(ex, iter, search_env((*sh)->env, "PATH", VAL));
// 					ex->stt = execve(ex->cmd, iter->arg, ex->env);
// 					exit (127);
// 				}
// 			}
// 			if (a.i >= 1)
// 			{
// 				pid_t	inp;
// 				pid_t	out;

// 				inp = -1;
// 				out = -1;
// 				(iter->next) && (inp = iter->next->tb[0]);
// 				(iter->next) && (out = iter->next->tb[1]);
// 				if (inp >= 0)
// 				{
// 					close(iter->tb[1]);
// 					close(inp);
// 					close(out);
// 					if (dup2(iter->tb[0], STDIN_FILENO) == ERROR)
// 						exit (msg_error(E_PRR, 1, "pipes"));
// 					close(iter->tb[0]);
// 					ex->stt = get_path(ex, iter, search_env((*sh)->env, "PATH", VAL));
// 					ex->stt = execve(ex->cmd, iter->arg, ex->env);
// 					exit (127);
// 				}
// 			}
// 		}
// 		a.i++;
// 		iter = iter->next;
// 	}
// 	clear_pipes(g);
// 	while (a.c <= ex->pipe)
// 	{
// 		waitpid(chds[a.c++], &ex->stt, 0);
// 		ex->stt = WEXITSTATUS(ex->stt);
// 	}
// 	free(chds);
// 	return (SUCCESS);
// }

int	*init_pipes(int n_pipes)
{
	int	*fds;
	int	i;

	fds = ft_calloc(n_pipes * 2, sizeof(int));
	if (!fds)
		exit (msg_error(E_MEM, E_EXIT, NULL));
	i = 0;
	
	return (fds);
}

int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	(void)ln;
    int num_pipes = ex->pipe;
    pid_t chds[num_pipes + 1];
    int fds[num_pipes * 2];

    int i = 0;
    while (i < num_pipes * 2) {
        if (pipe(fds + i) == -1) {
            perror("Error al crear los pipes");
            exit(EXIT_FAILURE);
        }
        i += 2;
    }

    int child_index = 0;
    while (child_index <= num_pipes) {
        chds[child_index] = fork();
        if (chds[child_index] == -1) {
            perror("Error al crear un proceso hijo");
            exit(EXIT_FAILURE);
        }

        if (chds[child_index] == 0) {
            if (child_index < num_pipes) {
                dup2(fds[child_index * 2 + 1], STDOUT_FILENO);
            }

            if (child_index > 0) {
                dup2(fds[(child_index - 1) * 2], STDIN_FILENO);
            }

            // Cerrar todos los descriptores de archivo en el hijo
            i = 0;
            while (i < num_pipes * 2) {
                close(fds[i]);
                i++;
            }

            // Ejecutar el comando correspondiente
            ex->stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
            ex->stt = execve(ex->cmd, (*g)->arg, ex->env);
            perror("Error al ejecutar el comando"); // Esto solo se imprimirá si execve falla
            exit(EXIT_FAILURE);
        }

        child_index++;
        // Avanzar al siguiente nodo en la lista
        if (*g && (*g)->next) {
            *g = (*g)->next;
        }
    }

    // Cerrar todos los descriptores de archivo en el proceso padre
    i = 0;
    while (i < num_pipes * 2) {
        close(fds[i]);
        i++;
    }

    // Esperar a que todos los hijos terminen
    child_index = 0;
    while (child_index <= num_pipes) {
        waitpid(chds[child_index], &ex->stt, 0);
        ex->stt = WEXITSTATUS(ex->stt);
        child_index++;
    }

    return SUCCESS;
}

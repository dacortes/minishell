/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/30 16:09:15 by dacortes         ###   ########.fr       */
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
	int i = 0;
	while (i < n_pipes * 2)
		close(fds[i++]);
}

int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
    (void)ln;
    int fds[ex->pipe * 2];
    pid_t chds[ex->pipe + 1];
    t_aux a;

    init_pipes(fds, ex->pipe);
    ft_bzero(&a, sizeof(t_aux));
    while (a.i <= ex->pipe)
    {
        chds[a.i] = fork();
        if (chds[a.i] == ERROR)
            exit(msg_error(E_PRR, 1, "fork"));
        if (!chds[a.i])
        {
            if (a.i < ex->pipe)
                dup2(fds[a.i * 2 + 1], STDOUT_FILENO);
            if (a.i > 0)
                dup2(fds[(a.i - 1) * 2], STDIN_FILENO);
            clear_pipes(fds, ex->pipe);
            ex->stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
            ex->stt = execve(ex->cmd, (*g)->arg, ex->env);
            exit(127);
        }

        a.i++;
        if (*g && (*g)->next)
            (*g) = (*g)->next;
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

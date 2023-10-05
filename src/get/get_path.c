/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:47:13 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/05 09:58:00 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static int	search_path(t_exe *ex, t_get *g, t_aux *a)
{
	while (ex->pth[a->i])
	{
		a->tmp = ft_addend_char(ex->pth[a->i], '/');
		if (!a->tmp)
			exit (msg_error(E_MEM, 1, NULL));
		ex->cmd = ft_strjoin(a->tmp, g->arg[0]);
		if (!ex->cmd)
			exit (msg_error(E_MEM, 1, NULL));
		if (access(ex->cmd, 0) == SUCCESS)
		{
			free(a->tmp);
			return (SUCCESS);
		}
		free(ex->cmd);
		free(a->tmp);
		a->i++;
	}
	return (ERROR);
}

static int	is_path(t_exe *ex, t_get *g)
{
	if (!g)
		return (FALSE);
	if (g && g->arg && g->arg[0][0] == '/')
	{
		if (access(g->arg[0], 0) == SUCCESS)
		{
			ex->pth = NULL;
			ex->cmd = ft_strdup_exit(g->arg[0]);
			return (SUCCESS);
		}
		return (msg_error(E_NSF, E_CNF, g->arg[0]));
	}
	return (ERROR);
}

int	get_path(t_exe *ex, t_get *g, char *path)
{
	t_aux	a;

	if (!g || !g->arg || !*g->arg)
		return (SUCCESS);
	ft_bzero(&a, sizeof(t_aux));
	a.k = is_path(ex, g);
	if (a.k == E_CNF || a.k == SUCCESS)
		return (((a.k == E_CNF) * E_CNF) + ((a.k == 0) * 0));
	ex->pth = ft_split(path, ':');
	if (!ex->pth)
		exit (msg_error(E_MEM, 1, NULL));
	if (search_path(ex, g, &a) == SUCCESS)
		return (SUCCESS);
	ex->cmd = ft_strdup_exit(g->arg[0]);
	return (SUCCESS);
}

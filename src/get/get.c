/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:02:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/26 16:40:48 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	clear_get(t_get **g)
{
	t_get	*rm;
	t_get	*tmp;

	rm = *g;
	while (rm)
	{
		clear_dptr((void **)rm->arg);
		tmp = rm;
		rm = rm->next;
		if (tmp)
			free(tmp);
	}
	*g = NULL;
	return (SUCCESS);
}

int	add_get(t_get **g, char **arg, int len)
{
	t_get	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(t_get), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->arg = ft_calloc(sizeof(char *), len + 1);
	if (!new->arg)
		exit (msg_error(E_MEM, 1, NULL));
	while (arg[i])
		new->arg[j++] = ft_strdup_exit(arg[i++]);
	new->next = NULL;
	get_add_back(g, new);
	return (SUCCESS);
}

int	can_be_joined(t_token **tk, char **arg, int *i)
{
	if (*tk && !(*tk)->type[2])
	{
		if ((*tk)->next && !((*tk)->next->type[3] >= 3
				&& (*tk)->next->type[3] <= 6) && (*tk)->next->type[3] != T_FD)
		{
			arg[*i] = ft_strjoin((*tk)->arg, (*tk)->next->arg);
			if (!arg[*i])
				exit (msg_error(E_MEM, 1, NULL));
			if ((*tk)->next)
				*tk = (*tk)->next;
		}
		else
			arg[*i] = ft_strdup_exit((*tk)->arg);
	}
	else
		arg[*i] = ft_strdup_exit((*tk)->arg);
	(*i)++;
	return (SUCCESS);
}

int	tk_to_array(t_token **tk, t_get **g, int len, int *stt)
{
	t_aux	a;
	int		fd[2];

	fd[0] = -2;
	fd[1] = -2;
	ft_bzero(&a, sizeof(t_aux));
	a.arr = ft_calloc(sizeof(char *), len + 1);
	if (!a.arr)
		exit (msg_error(E_MEM, 1, NULL));
	while (*tk)
	{
		if (((*tk)->type[3] >= 3 && (*tk)->type[3] <= 6) || (*tk)->type[3] == 7)
		{
			open_rdc(tk, fd, stt);
			if ((*tk)->next)
				*tk = (*tk)->next;
		}
		else
			can_be_joined(tk, a.arr, &a.i);
		*tk = (*tk)->next;
	}
	a.c = add_get(g, a.arr, len) + clear_dptr((void **)a.arr);
	(*g)->fd[0] = fd[0];
	(*g)->fd[1] = fd[1];
	return (*stt);
}

int	get_init(t_line **ln, t_get **g, int *stt)
{
	t_line	*tmp;
	t_token	*tk;
	int		rdr;

	if (!*ln)
	{
		clear_get(g);
		return (SUCCESS);
	}
	tmp = *ln;
	while (tmp)
	{
		tk = tmp->tk;
		rdr = len_no_rd(tk);
		tk_to_array(&tk, g, (count_tk(tk) - rdr), stt);
		tmp = tmp->next;
	}
	return (*stt);
}

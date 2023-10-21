/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:02:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/21 16:43:18 by dacortes         ###   ########.fr       */
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

/* test */
int	tk_to_array(t_token **tk, t_get **g, int len, int *stt)
{
	int		fd[2];
	char	**arg;
	int		i;

	fd[0] = -2;
	fd[1] = -2;
	i = 0;
	arg = ft_calloc(sizeof(char *), len + 1);
	if (!arg)
		exit (msg_error(E_MEM, 1, NULL));
	while (*tk)
	{
		if (((*tk)->type[3] >= 3 && (*tk)->type[3] <= 6)
			|| (*tk)->type[3] == T_FD)
		{
			test_rdc(tk, fd, stt);
			if ((*tk)->next)
				*tk = (*tk)->next;
		}
		else
			can_be_joined(tk, arg, &i);
		*tk = (*tk)->next;
	}
	add_get(g, arg, len);
	clear_dptr((void **)arg);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:02:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/28 15:23:40 by dacortes         ###   ########.fr       */
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
	if (!(*g))
		*g = new;
	else
	{
		new->next = *g;
		*g = new;
	}
	return (SUCCESS);
}

int	get_init(t_line **ln, t_get **g)
{
	t_line	*tmp;
	t_token	*tk;
	char	**arg;
	int		rdr;
	int		i;

	if (!*ln)
		return (SUCCESS);
	tmp = *ln;
	*g = ft_calloc(sizeof(t_get), 1);
	if (!*g)
		exit (msg_error(E_MEM, 1, NULL));
	while (tmp)
	{
		tk = tmp->tk;
		rdr = len_no_rd(tk);
		while (tk)
		{
			if ((tk->type[3] >= 3 && tk->type[3] <= 6)
			|| tk->type[3] == T_FD)
			{
				if (tk->next)
					tk = tk->next;
			}
			else
			{
				arg = ft_calloc(sizeof(char *), (tmp->argc - rdr) + 1);
				if (!arg)
					exit (msg_error(E_MEM, 1, NULL));
				i = 0;
				arg[i] = ft_strdup_exit(tk->arg);
				add_get(g, arg, (tmp->argc - rdr));
				clear_dptr((void **)arg);
			}
			tk = tk->next;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:09:06 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/28 15:16:44 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

 #include <string.h>

int	search_hrdoc()
{
	return (SUCCESS);
}

int	search_cmd(t_line **ln, t_get **g)
{
	(void)ln;
	(void)g;
	// t_line	*tmp;
	// t_token	*tk;
	return (SUCCESS);
}

/* executer */
int	get_cmd(t_line **ln, t_env *env, t_get *g)
{
	(void)ln;
	(void)env;
	(void)g;
	return (SUCCESS);
}

int	clear_dptr(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		ft_printf("size the ptr %d\n", ft_double_ptr_len(ptr));
		while (ptr[i])
		{
			ft_printf(R"free token->%s\n"E, ptr[i]);
			free(ptr[i++]);
		}
		if (ptr)
			free(ptr);
	}
	return (SUCCESS);
}
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

int	len_no_rd(t_token *tk)
{
	t_token *iter;
	int num;

	num = 0;
	iter = tk;
	while (iter)
	{
		if ((iter->type[3] >= 3 && iter->type[3] <= 6)
		|| iter->type[3] == T_FD)
			num++;
		iter = iter->next;
	}
	return (num);
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
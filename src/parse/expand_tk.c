/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:39:43 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/18 11:24:41 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static void	swap_val(t_aux *a, int start, int end)
{
	char	*expd;

	if (a->_val)
	{
		expd = ft_strrep(a->e, start, end, a->_val);
		free(a->e);
		a->e = expd;
		a->tmp = a->e + start + ft_strlen(a->_val);
	}
	else
	{
		expd = ft_strrep(a->e, start, end, "");
		free(a->e);
		a->e = expd;
		a->tmp = a->e + start;
	}
}

static void	loop_val(t_aux *a, t_env *env, t_token **tk)
{
	int	start;
	int	end;

	a->tmp = ft_strchr(a->tmp, '$');
	while (a->tmp)
	{
		start = a->tmp - a->e;
		end = start + 1;
		while (a->e[end] && (ft_isalnum(a->e[end]) || a->e[end] == '_'))
			end++;
		a->_key = ft_strndup(a->e + start + 1, end - start -1);
		a->_val = search_env(env, a->_key, VAL);
		free(a->_key);
		swap_val(a, start, end);
		if ((*tk)->arg)
			free((*tk)->arg);
		(*tk)->arg = ft_strdup_exit(a->e);
		a->tmp = ft_strchr(a->tmp, '$');
	}
}

int	expand_tk(t_token **tk, t_env *env)
{
	t_token	*tmp;
	t_aux	a;

	tmp = *tk;
	ft_bzero(&a, sizeof(t_aux));
	while (tmp)
	{
		if (tmp->type[1] == T_EXP)
		{
			a.e = ft_strdup_exit(tmp->arg);
			a.tmp = a.e;
			loop_val(&a, env, &tmp);
			free(a.e);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

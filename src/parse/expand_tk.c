/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:39:43 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/03 09:18:07 by dacortes         ###   ########.fr       */
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
		ft_printf("%s\n", (a->e + start + 1));
		if (a->_key[0] != '?')
		{
			ft_printf(Y"estoy aqui\n"E);
			a->_val = ft_strdup(search_env(env, a->_key, VAL));
		}
		else
		{
			ft_printf("estoy aqui\n");
			(a->_val = ft_itoa(gett_stt(FALSE, 0)));
		}
		free(a->_key);
		swap_val(a, start, end);
		free(a->_val);
		if ((*tk)->arg)
			free((*tk)->arg);
		(*tk)->arg = ft_strdup_exit(a->e);
		a->tmp = ft_strchr(a->tmp, '$');
	}
}

static void	magic_tk(t_aux *a, t_token **tmp, t_env *env)
{
	a->e = ft_strdup_exit((*tmp)->arg);
	a->tmp = a->e;
	loop_val(a, env, tmp);
	if (a->e)
		free(a->e);
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
			if (ft_strlen(tmp->arg) == 1 && tmp->arg[0] == '$')
				;
			else
			{
				if ((tmp->type[3] == 5) && tmp->next
					&& !(tmp->next->type[3] >= 3 && tmp->next->type[3] <= 6))
					tmp->next->type[3] = T_FD;
				if (tmp->type[3] != T_FD && tmp->arg && (ft_isalnum(tmp->arg[1])
					|| (tmp->arg[1] == '?')))
					magic_tk(&a, &tmp, env);
				// if ((tmp->type[3] != T_FD && tmp->arg && tmp->arg[1] == '?'))
				// {
				// 	//ft_printf("soy el ultimo stautus jaja, %d\n", gett_stt(FALSE, 0));
				// 	epd_question_mark(&a, &tmp, gett_stt(FALSE, 0));
				// }		
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

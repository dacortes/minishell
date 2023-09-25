/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:48 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/25 10:33:05 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	add_line(t_line **ln, t_token *tk, char	*line)
{
	t_line	*new;

	new = ft_calloc(sizeof(t_line), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->tk = tk;
	new->line = ft_strdup(line);
	if (!line)
		exit (msg_error(E_MEM, 1, NULL));
	new->next = NULL;
	if (!(*ln))
		*ln = new;
	else
	{
		new->next = *ln;
		*ln = new;
	}
	return (SUCCESS);
}

static void	continue_cnt(t_line **ln, t_aux **a, t_token *tk, char *inp)
{
	char	*tmp;

	while (inp[(*a)->k] && ((inp[(*a)->k] >= 9 && inp[(*a)->k] <= 13) \
		|| inp[(*a)->k] == 32))
		(*a)->k++;
	tmp = ft_substr(inp, (*a)->k, (*a)->i - (*a)->k);
	if (!tmp)
		exit (msg_error(E_MEM, 1, NULL));
	(*a)->k = (*a)->i + 1;
	add_line(ln, tk, tmp);
	(*ln)->argc = (*a)->c;
	(*ln)->argv = convert_to_argv(*ln);
	free (tmp);
}

static int	copy_cnt(t_aux *a, t_env *env, t_token	**tk, char *inp)
{
	if (copy_quotes(inp, a, tk, env) == ERROR)
		return (clear_tk(tk) + msg_error(E_SNT, E_SNT, "`\' "));
	if (inp[a->j] && (inp[a->j] == '<') && copy_redic(inp, a, tk, '<') == E_SNT)
		return (clear_tk(tk) + E_SNT);
	else if (inp[a->j] && (inp[a->j] == '>')
		&& copy_redic(inp, a, tk, '>') == E_SNT)
		return (clear_tk(tk) + E_SNT);
	return (SUCCESS);
}

static int	continue_ln(t_line **ln, t_aux *a, t_env *env, char *inp)
{
	t_token	*tk;
	int		chk;

	tk = NULL;
	a->c = 0;
	while (inp[a->i] && inp[a->i] != '|')
	{
		while (inp[a->i] && ((inp[a->i] >= 9 \
			&& inp[a->i] <= 13) || inp[a->i] == 32))
			a->i++;
		a->in_qu = ((inp[a->i] == DQU) * DQU) + ((inp[a->i] == QUO) * QUO);
		if (a->in_qu == DQU && copy_quotes(inp, a, &tk, env) == ERROR)
			return (clear_tk(&tk) + msg_error(E_SNT, E_SNT, "`\"\'"));
		else if (a->in_qu == QUO && copy_quotes(inp, a, &tk, env) == ERROR)
			return (clear_tk(&tk) + msg_error(E_SNT, E_SNT, "`\'\'"));
		else if (inp[a->i] && inp[a->i] != '|' && !a->in_qu)
		{
			chk = copy_cnt(a, env, &tk, inp);
			if (chk == ERROR || chk == E_SNT)
				return (chk);
		}
	}
	continue_cnt(ln, &a, tk, inp);
	return (SUCCESS);
}

int	ft_line(char *inp, t_line **ln, t_env *env)
{
	t_aux	a;

	ft_bzero(&a, sizeof(t_aux));
	while (inp[a.i])
	{
		if (continue_ln(ln, &a, env, inp) == E_SNT)
			return (E_SNT);
		if (inp[a.i])
			a.i++;
	}
	return (SUCCESS);
}

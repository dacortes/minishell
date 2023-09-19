/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:48 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/19 12:12:34 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	analize_space(char *inp, t_aux *a)
{
	int	spc;
	int	start;

	spc = 0;
	start = a->j;
	while (inp[start] && inp[start] == ' ')
		(start++) && (spc++);
	// ft_printf(B"%d\n"E, spc);
	return (spc);
}

static int	copy_quotes(char *inp, t_aux *a, t_token **tk, t_env *env)
{
	int	array[3];

	if (a->in_qu == QUO || a->in_qu == DQU)
	{
		if (type_expand(inp, a, tk, a->in_qu) == ERROR)
			return (ERROR);
	}
	else
	{
		a->j = a->i;
		while (inp[a->j] && inp[a->j] != ' ' && inp[a->j] != '|' \
			&& inp[a->j] != QUO && inp[a->j] != DQU)
			a->j++;
		array[0] = FALSE;
		array[1] = T_EXP;
		array[2] = analize_space(inp, a);
		a->tmp = ft_substr(inp, a->i, a->j - a->i);
		if (!a->tmp)
			exit (msg_error(E_MEM, 1, NULL));
		a->i = a->j;
		add_token(tk, a->tmp, array, &a->c);
		free(a->tmp);
	}
	expand_tk(tk, env);
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

static int	continue_ln(t_line **ln, t_aux *a, t_env *env, char *inp)
{
	t_token	*tk;

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
			if (copy_quotes(inp, a, &tk, env) == ERROR)
				return (clear_tk(&tk) + msg_error(E_SNT, E_SNT, "`\' "));
		}
	}
	continue_cnt(ln, &a, tk, inp);
	// int	c = 0;
	// ft_printf(Y"line\n"E);
	// while ((*ln)->argv[c])
	// 	ft_printf("%s\n", (*ln)->argv[c++]);
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

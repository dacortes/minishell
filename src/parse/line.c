/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:34:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/30 18:55:56 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	clear_ln(t_line *ln)
{
	ft_printf(Y"estoy aqui\n"E);
	t_line	*rm;
	t_line	*tmp;
	t_token *del_tk;
	t_token	*tmp_tk;

	rm = ln;
	del_tk = ln->tk;
	while (rm)
	{
		ft_printf(C"estoy aqui\n"E);
		tmp = rm;
		while (del_tk)
		{
			ft_printf(F"estoy aqui\n"E);
			tmp_tk = del_tk;
			if (del_tk->arg)
				free(del_tk->arg);
			del_tk = del_tk->next;
			free(tmp_tk);
		}
		rm = rm->next;
		free(tmp);
	}
	return (SUCCESS);
}

void	show_tk(t_token *tk)
{
	t_token *tmp;

	tmp = tk;
	while (tmp)
	{
		ft_printf(G"%s\n"E, tk->arg);
		tmp = tmp->next;
	}
}
void	show_ln(t_line *ln)
{
	t_line *tmp;

	tmp = ln;
	while (tmp)
	{
		show_tk(ln->tk);
		tmp = tmp->next;
	}
}

int	add_line(t_line **ln)
{
	t_line *new;

	new = ft_calloc(sizeof(t_line), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->next = *ln;
	*ln = new;
	(*ln)->argc++;
	return (SUCCESS);
}

int	copy_quotes(char *inp, t_aux *a, t_line **ln, int type)
{
	if (type != ' ')
	{
		a->i += (inp[a->i] == QUO) + (inp[a->i] == DQU);
		a->j = ft_strchrpos(&inp[a->i], type);
		if (a->j == ERROR)
			return (ERROR);
		a->tmp = ft_substr(inp, a->i, a->j);
		ft_printf(R"%s\n"E, a->tmp);
		a->i += a->j + 1;
		add_token(&(*ln)->tk, a->tmp, 0);
		free(a->tmp);
	}
	else
	{
		a->tmp = ft_difcpy(inp, ' ', &a->i);
		ft_printf (Y"%s\n"E, a->tmp);
		add_token(&(*ln)->tk, a->tmp, 0);
		free(a->tmp);
	}
	return (SUCCESS);
}

int	continue_ln(t_line **ln, char *inp, t_aux *a)
{
	(*ln)->tk = NULL;
	while (inp[a->i] && inp[a->i] != '|')
	{
		while (inp[a->i] && ((inp[a->i] >= 9 \
			&& inp[a->i] <= 13) || inp[a->i] == 32))
			a->i++;
		a->in_qu = ((inp[a->i] == DQU) * DQU) + ((inp[a->i] == QUO) * QUO);
		if (a->in_qu == DQU && copy_quotes(inp, a, ln, DQU) == ERROR)
			return ((ft_printf(R"Error double quotes\n"E) * 0) + ERROR);
		else if (a->in_qu == QUO && copy_quotes(inp, a, ln, QUO) == ERROR)
			return ((ft_printf(R"Error quotes\n"E) * 0) + ERROR);
		else if (inp[a->i] && inp[a->i] != '|' && !a->in_qu)
		{
			if (copy_quotes(inp, a, ln, ' ') == ERROR)
				return ((ft_printf(R"Error space\n"E) * 0) + ERROR);
		}
	}
	// a->i = (inp[a->i] == '|');
	add_line(ln);
	return (SUCCESS);
}

int	init_ln(char *inp)
{
	t_aux	a;
	t_line	*ln;

	ln = ft_calloc(sizeof(t_line), 1);
	a.i = 0;
	while (inp[a.i])
	{
		ft_printf("%s -> %i\n", inp, a.i);
		if (continue_ln(&ln, inp, &a) == ERROR)
			break ;
		if (inp[a.i])
			a.i++;
	}
	show_ln(ln);
	clear_ln(ln);
	return (SUCCESS);
}

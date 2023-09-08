/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:48 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/08 13:59:28 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	copy_quotes(char *inp, t_aux *a, t_token **tk, int type)
{
	if (type == QUO || type == DQU)
	{
		a->i += (inp[a->i] == QUO) + (inp[a->i] == DQU);
		a->j = ft_strchrpos(&inp[a->i], type);
		if (a->j == ERROR)
			return (ERROR);
		a->tmp = ft_substr(inp, a->i, a->j);
		if (!a->tmp)
			exit (msg_error(E_MEM, 1, NULL));
		a->i += a->j + 1;
		add_token(tk, a->tmp, 0, &a->c);
		free(a->tmp);
	}
	else
	{
		a->j = a->i;
		while (inp[a->j] && inp[a->j] != ' ' && inp[a->j] != '|' \
			&& inp[a->j] != QUO && inp[a->j] != DQU)
			a->j++;
		a->tmp = ft_substr(inp, a->i, a->j - a->i);
		if (!a->tmp)
			exit (msg_error(E_MEM, 1, NULL));
		a->i = a->j;
		add_token(tk, a->tmp, 0, &a->c);
		free(a->tmp);
	}
	return (SUCCESS);
}

void	continue_cnt(t_line **ln, t_aux **a, t_token *tk, char *inp)
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

/*
	Da segmentation fault en el pipe cuando se le agrega un espacio | 
	Da segmentation fault despues de que un error se genere
*/
int	continue_ln(t_line **ln, t_aux *a, char *inp)
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
		if (a->in_qu == DQU && copy_quotes(inp, a, &tk, DQU) == ERROR)
			return ((ft_printf(R"Error double quotes\n"E) * 0) + ERROR);
		else if (a->in_qu == QUO && copy_quotes(inp, a, &tk, QUO) == ERROR)
			return ((ft_printf(R"Error quotes\n"E) * 0) + ERROR);
		else if (inp[a->i] && inp[a->i] != '|' && !a->in_qu)
		{
			if (copy_quotes(inp, a, &tk, ' ') == ERROR)
				return ((ft_printf(R"Error space\n"E) * 0) + ERROR);
		}
	}
	continue_cnt(ln, &a, tk, inp);
	int c = 0;
	while ((*ln)->argv[c])
		ft_printf("%s\n", (*ln)->argv[c++]);
	return (SUCCESS);
}

int	ft_line(char *inp, t_line **ln)
{
	t_aux	a;

	ft_bzero(&a, sizeof(t_aux));
	while (inp[a.i])
	{
		if (continue_ln(ln, &a, inp) == ERROR)
			break ;
		if (inp[a.i])
			a.i++;
	}
	// show_tokens(*ln);
	//show_line(*ln);
	return (SUCCESS);
}

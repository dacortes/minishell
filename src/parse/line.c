/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:15:28 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/29 18:18:17 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	add_line(t_line **ln, char *inp)
{
	t_line *new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->line = ft_strdup(inp);
	if (!new->line)
		exit (msg_error(E_MEM, 1, NULL));
	new->next = *ln;
	*ln = new;
	return (SUCCESS);
}

int	clear_ln(t_line *ln)
{
	t_line	*rm;
	t_line	*tmp;

	rm = ln;
	while (rm)
	{
		tmp = rm;
		if (rm->line)
			free(rm->line);
		rm = rm->next;
		free(tmp);
	}
	return (SUCCESS);
}

void	show_ln(t_line *ln)
{
	t_line	*tmp;

	tmp = ln;
	while (tmp)
	{
		ft_printf(R"*%s*\n"E, tmp->line);
		tmp = tmp->next;
	}
}

// int	init_ln(char *inp)
// {
// 	t_line	*ln;
// 	char	*tmp;
// 	int		i;
// 	int		in_qu;
// 	int		x;

// 	ln = NULL;
// 	i = 0;
// 	x = 0;
// 	in_qu = 0;
// 	tmp = NULL;
// 	while (inp[i] && ((inp[i] >= 9 && inp[i] <= 13) || inp[i] == 32))
// 		i++;
// 	while (inp[i])
// 	{
// 		tmp = ft_calloc(1000, 1);
// 		x = 0;
// 		while (inp[i] && inp[i] != '|')			
// 		{
// 			in_qu = ((inp[i] == DQU) * DQU) + ((inp[i] == QUO) * QUO);
// 			if (in_qu == DQU)
// 			{
// 				while (inp[i])
// 				{
// 					tmp[i] = inp[i];
// 					i++;
// 					if (inp[i] == DQU)
// 						break;
// 				}
// 				tmp[i] = DQU;
// 				in_qu = 0;
// 			}
// 			tmp[x] = inp[i];
// 			i++;
// 			x++;
// 		}
// 		add_line(&ln, tmp);
// 		i += (inp[i] == '|');
// 		while (inp[i] && ((inp[i] >= 9 && inp[i] <= 13) || inp[i] == 32))
// 			i++;
// 		if (tmp)
// 			free(tmp);
// 	}
// 	show_ln(ln);
//     clear_ln(ln);
// 	return (SUCCESS);
// }

int	cpy_qu(t_aux *a, char *inp, int type)
{
	while (inp[a->i])
	{
		a->tmp[a->j++] = inp[a->i++];
		if (inp[a->i] == type)
			break;
	}
	a->tmp[a->j] = type;
	a->in_qu = 0;
	return (SUCCESS);
}

char *cpy_quotes(t_aux *a, char *inp, int type)
{
	// char	*new;
	int		i;

	i = a->i;
	// i += ft_strchrpos(&inp[i++], type);
	if (ft_strchrpos(&inp[i++], type) == ERROR)
		return ( NULL);
	ft_printf(Y"%s\n"E, &inp[a->i]);
	// new = ft_substr(inp, a->i, );
	return (NULL);
}

int	init_ln(char *inp)
{
	t_line	*ln;
	t_aux	a;

	ln = NULL;
	a.i = 0;
	a.tmp = NULL;
	while (inp[a.i])
	{
		a.j = 0;
		while (inp[a.i] && ((inp[a.i] >= 9 && inp[a.i] <= 13) || inp[a.i] == 32))
			a.i++;
		a.tmp = ft_calloc(ft_strlen(inp) + 1, sizeof(char));
		if (!a.tmp)
			exit (msg_error(E_MEM, 1, NULL));
		while (inp[a.i] && inp[a.i] != '|')
		{
			a.in_qu = ((inp[a.i] == DQU) * DQU) + ((inp[a.i] == QUO) * QUO);
			if (a.in_qu == DQU)
			{
				cpy_quotes(&a, inp, DQU);
				//cpy_qu(&a, inp, DQU);
			}
			else if (a.in_qu == QUO)
				cpy_qu(&a, inp, QUO);
			else
				a.tmp[a.j++] = inp[a.i++];
		}
		add_line(&ln, a.tmp);
		a.i += (inp[a.i] == '|');
		if (a.tmp)
			free(a.tmp);
	}
	show_ln(ln);
    clear_ln(ln);
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:10:44 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/26 15:14:50 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	identify(t_token **tk)
{
	(ft_strlen((*tk)->arg) == 1 && (*tk)->type[0] == FALSE
		&& (*tk)->arg[0] == '<' && ((*tk)->type[3] = T_SIR));
	(ft_strlen((*tk)->arg) == 1 && (*tk)->type[0] == FALSE
		&& (*tk)->arg[0] == '>' && ((*tk)->type[3] = T_SOR));
	(ft_strlen((*tk)->arg) == 2 && (*tk)->type[0] == FALSE
		&& ft_strncmp((*tk)->arg, "<<", 2) == 0 && ((*tk)->type[3] = T_RDHD));
	(ft_strlen((*tk)->arg) == 2 && (*tk)->type[0] == FALSE
		&& ft_strncmp((*tk)->arg, ">>", 2) == 0 && ((*tk)->type[3] = T_RDAP));
	return ((*tk)->type[3]);
}

int	analize_space(char *inp, int count)
{
	int	spc;
	int	start;

	spc = 0;
	start = count;
	start += (inp[start] == DQU) + (inp[start] == QUO);
	while (inp[start] && inp[start] == ' ')
		(start++) && (spc++);
	return (spc);
}

int	error_unexpected(int rep, char cut, char **fr)
{
	char	*err;

	(rep % 2 == 0) && cut == '>' && (err = "`>>\'");
	(rep % 2 == 0) && cut == '<' && (err = "`<<\'");
	(rep % 2 == 1) && cut == '>' && (err = "`>\'");
	(rep % 2 == 1) && cut == '<' && (err = "`<\'");
	if (fr && *fr)
		free(*fr);
	return (msg_error(E_SNT, E_SNT, err));
}

int	type_expand(char *inp, t_aux *a, t_token **tk, int type)
{
	int	array[4];

	a->i += (inp[a->i] == QUO) + (inp[a->i] == DQU);
	a->j = ft_strchrpos(&inp[a->i], type);
	if (a->j == ERROR)
		return (ERROR);
	a->tmp = ft_substr(inp, a->i, a->j);
	if (!a->tmp)
		exit (msg_error(E_MEM, 1, NULL));
	a->i += a->j + 1;
	array[0] = type;
	array[1] = ((type == QUO) * T_TXT) + ((type == DQU) * T_EXP);
	array[2] = analize_space(inp, a->i);
	array[3] = T_TXT;
	add_token(tk, a->tmp, array, &a->c);
	free(a->tmp);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:19:26 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/25 10:21:48 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	copy_unquo(char	*inp, t_aux *a, t_token **tk)
{
	int	array[4];

	a->j = a->i;
	while (inp[a->j] && inp[a->j] != ' ' && inp[a->j] != '|' \
		&& inp[a->j] != QUO && inp[a->j] != DQU
		&& inp[a->j] != '<' && inp[a->j] != '>')
		a->j++;
	array[0] = FALSE;
	array[1] = T_EXP;
	array[2] = analize_space(inp, a->j);
	array[3] = T_TXT;
	a->tmp = ft_substr(inp, a->i, a->j - a->i);
	if (!a->tmp)
		exit (msg_error(E_MEM, 1, NULL));
	a->i = a->j;
	if (a->tmp && *a->tmp)
		add_token(tk, a->tmp, array, &a->c);
	free(a->tmp);
	return (SUCCESS);
}

int	copy_redic(char *inp, t_aux *a, t_token **tk, char rdc)
{
	int	array[4];
	int	num;
	int	start;

	num = 0;
	start = a->j;
	while (inp[start] && inp[start] == rdc)
		(num++) && (start++);
	num -= (inp[start] != rdc);
	if (num > 2)
		return (error_unexpected(num, rdc, NULL));
	a->tmp = ft_strndup(&inp[a->j], num);
	array[0] = FALSE;
	array[1] = T_EXP;
	array[2] = analize_space(inp, start);
	array[3] = FALSE;
	add_token(tk, a->tmp, array, &a->c);
	identify(tk);
	free(a->tmp);
	a->j += num;
	a->i = a->j;
	return (SUCCESS);
}

int	copy_quotes(char *inp, t_aux *a, t_token **tk, t_env *env)
{
	if (a->in_qu == QUO || a->in_qu == DQU)
	{
		if (type_expand(inp, a, tk, a->in_qu) == ERROR)
			return (ERROR);
	}
	else
		copy_unquo(inp, a, tk);
	expand_tk(tk, env);
	return (SUCCESS);
}

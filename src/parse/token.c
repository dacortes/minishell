/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:02 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/28 11:52:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/* test */

int	add_token(t_token *tk, char *arg, int type)
{
	t_token *new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->arg = ft_strdup(arg);
	if (!new->arg)
		exit (msg_error(E_MEM, 1, NULL));
	new->type = type;
	new->next = tk;
	tk = new;
	return (SUCCESS);
}

// int	token(char *inp)
// {
// 	t_token	tk;
// 	char	del;

// 	del = ' ';
// 	int i = 0;
// 	int	e = 0;
// 	while (inp[i] && inp[i] == ' ')
// 		i++;
// 	del = ' ' + ((inp[i] == D_QUOTES) * 2) + ((inp[i] == QUOTES) * 7);
// 	i += (inp[i] == D_QUOTES) || (inp[i] == QUOTES);
// 	e = i;
// 	while(inp[e] && inp[e] != del)
// 	{
// 		if (inp[e] == D_QUOTES || inp[e] == QUOTES)
// 			break ;
// 		e++;
// 	}
// 	e -= (inp[e] == del);
// 	ft_printf(Y"la e:%i, %c\n"E, e, del, inp[e] == del);
// 	tk.arg = ft_substr(inp, i, e);
// 	ft_printf(R"del=%i arg=%s# init=%i end=%i \n"E, del, tk.arg, i, e);
// 	free(tk.arg);
// 	return (SUCCESS);
// }

int	token(char *inp)
{
	int	dq;
	int	qu;
	int	i;

	1 && (i = -1) && (dq = 0) && (qu = 0);
	while(inp[++i])
	{
		if (inp[i] == DQU)
		{
			ft_printf(R"estoy qui\n"E);
			dq++;
		}
		else if (inp[i] == QUO)
		{
			ft_printf(B"estoy qui\n"E);
			qu++;
		}
	}
	ft_printf("%d\n", i);
	return (((dq % 2 == 1) * DQU) + ((qu % 2 == 1) * QUO));
}
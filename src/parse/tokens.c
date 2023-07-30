/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:50:50 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/30 12:39:03 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

int	init_parse(t_parse **ps)
{
	*ps = (t_parse*)ft_calloc(sizeof(t_parse), 1);
	if (!ps)
		exit (msg_error(E_MEM, 1, NULL));
	(*ps)->size = 0;
	(*ps)->tk = NULL;
	return (SUCCESS);
}

int	new_node_tk(t_parse *ps, t_token *new)
{
	if (!ps || !new)
		return (ERROR);
	if (ps->size > 0)
	{
		new->next = ps->tk;
		ps->tk = new;
	}
	ps->size++;
	return (SUCCESS);
}
/* parse input y despues un parse par los comandos */
/* un token es todo aquell separado por un espacio pipe o algun tipo de redireccion siempre
y cuando estos no se encuentren entre comillas dobles o simples*/
/*ls       "$a| echo -a"$USER-a"'-a$USER' |ls -la .|grep*/

/* test token*/
int	token(/*t_token *tk, */char *inp)
{
	int	i;
	int len;
	char	*tk;
	t_parse *ps;

	init_parse(&ps);
	i = ignore_sp(inp);
	while (inp[i])
	{
		if (inp[i] == D_QUOTES)
		{
			//ft_printf("Estoy aqui\n");
			ps->tk->t_dq = 1;
		}
		else if (inp[i] == QUOTES)
		{
			ps->tk->t_qu = 1;
		}
		i++;
	}
	while (inp[i])
	{ 
		if (!ps->tk->t_dq && !ps->tk->t_qu && inp[i] != '|' && !ft_is_space(inp[i]))
		{
			ft_printf("Estoy aqui\n");
			break ;
		}
		i++;
	}
	tk = ft_calloc(sizeof(char), i + 1);
	if (!tk)
		exit (msg_error(E_MEM, 1, NULL));
	len = i - ignore_sp(inp);
	if (len)
		ft_strlcpy(tk, &inp[ignore_sp(inp)], len + 1);
	ft_printf(R"%s\n"E, tk);
	if (tk)
		free(tk);
	free(ps);
	return (SUCCESS);
}
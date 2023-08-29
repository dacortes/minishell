/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:02 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/29 18:22:23 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

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

/* test token txt*/
int	init_tk(/*t_token **tk,*/ char *inp)
{
	int i;
	char	*txt;
	char	*cmd;

	i = 0;
	while (inp[i])
	{
		if (inp[i] == DQU)
		{
			i++;
			ft_printf("soy una comilla\n");
			txt = ft_difcpy(inp, DQU, &i);
			i += (inp[i] == DQU);
			ft_printf(Y"->%s<-\n"E, txt);
			free(txt);
		}
		else if (inp[i] == QUO)
		{
			i++;
			ft_printf("soy una comilla\n");
			txt = ft_difcpy(inp, QUO, &i);
			i += (inp[i] == QUO);
			ft_printf(F"->%s<-\n"E, txt);
			free(txt);
		}
		else
		{
			cmd = ft_difcpy(inp, ' ', &i);
			ft_printf(C"->%s<-\n"E, cmd);
			free(cmd);
		}
		ft_printf(B"%i\n"E, i);
		i++;
	}
	return (SUCCESS);
}
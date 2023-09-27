/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:20:32 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/27 10:14:14 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	parse(t_line **ln)
{
	t_line	*tmp;
	t_token	*tk;

	if (!*ln)
		return (SUCCESS);
	tmp = *ln;
	ft_printf("Estoy aqui\n");
	while (tmp)
	{
		tk = tmp->tk;
		while (tk)
		{
			if (tk->type[3] >= 3 && tk->type[3] <= 6 && !tk->next)
				return (msg_error(E_SNT, E_SNT, "`newline\'"));
			if (tk->type[3] >= 3 && tk->type[3] <= 6 && tk->next)
				tk->next->type[3] = T_FD;
			tk = tk->next;
		}
		tmp = tmp->next;
	}
	show_tokens(*ln);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:20:32 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/06 16:49:26 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static int	double_redic(t_token *tk)
{
	if ((tk->type[3] == 3 || tk->type[3] == 4) && tk->next
		&& (tk->next->type[3] == 3 || tk->next->type[3] == 4) \
		&& tk->next->next && (tk->next->next->type[3] == 3 \
		|| tk->next->next->type[3] == 4) && tk->next->next->next \
		&& (tk->next->next->next->type[3] == 3 \
		|| tk->next->next->next->type[3] == 4))
		return (TRUE);
	return (FALSE);
}

int	parse(t_line **ln)
{
	t_line	*tmp;
	t_token	*tk;

	if (!*ln)
		return (SUCCESS);
	tmp = *ln;
	while (tmp)
	{
		tk = tmp->tk;
		while (tk)
		{
			if (tk->type[3] >= 3 && tk->type[3] <= 6 && !tk->next)
				return (msg_error(E_SNT, E_SNT, "`newline\'"));
			if (double_redic(tk))
				return (msg_error(E_SNT, E_SNT, "`<>\'"));
			if ((tk->type[3] >= 3 && tk->type[3] <= 6) && tk->next
				&& !(tk->next->type[3] >= 3 && tk->next->type[3] <= 6))
				tk->next->type[3] = T_FD;
			tk = tk->next;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

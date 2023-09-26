/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:20:32 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/26 16:46:18 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	parse(t_line **ln)
{
	t_line	*tmp;
	t_token	*tk;

	tmp = *ln;
	while (tmp)
	{
		tk = tmp->tk;
		ft_printf(Y"parse line\n"E);
		while (tk)
		{
			ft_printf(Y"token: "E"%s\n"E, tk->arg);
			ft_printf("%p\n", tk->next);
			if (tk->type[3] >= 3 && tk->type[3] <= 6 && !tk->next)
				return (msg_error(E_SNT, E_SNT, "`newline\'"));
			tk = tk->next;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

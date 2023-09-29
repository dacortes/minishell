/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:24:00 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/29 17:32:16 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	clear_dptr(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			free(ptr[i++]);
		if (ptr)
			free(ptr);
	}
	return (SUCCESS);
}

int	len_no_rd(t_token *tk)
{
	t_token *iter;
	int		num;

	num = 0;
	iter = tk;
	while (iter)
	{
		if ((iter->type[3] >= 3 && iter->type[3] <= 6)
		|| iter->type[3] == T_FD)
			num++;
		iter = iter->next;
	}
	return (num);
}

void	show_arg(t_get *g)
{
	t_get	*iter;
	int		num;
	int		i;

	iter = g;
	num = 1;
	while (iter)
	{
		if (iter->arg)
		{
			i = -1;
			while (iter->arg[++i])
			{
				(i == 0) && ft_printf(F"["E"%d"F"] COMMAND\n"E, num);
				ft_printf(F"["E"%d"F"]"O" *argument:"E" %s\n", i, iter->arg[i]);
			}
		}
		num++;
		iter = iter->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/27 12:34:11 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

static int child()
{

}

int	pipes(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	t_get	*iter;
	int		num;

	num = 0;
	iter = *g;
	if (!ex->stt && ex->pipe)
	{
		while (iter && num <= ex->pipe)
		{
			
			num++;
			iter = iter->next;
		}
	}
	return (SUCCESS);
}

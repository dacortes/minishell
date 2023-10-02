/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:49:36 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/02 11:33:31 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	is_heredoc(t_token **tk)
{
	char	*inp;

	inp = "";
	if ((*tk)->type[3] == 5)
	{
		while (inp && (*tk)->next && (*tk)->next->arg
			&& ft_strncmp((*tk)->next->arg, inp, -1) != 0)
		{
			inp = readline(O"> "E);
			free (inp);
		}
	}
	return (SUCCESS);
}

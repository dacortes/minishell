/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:49:36 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/29 14:32:51 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

int	is_heredoc(t_token **tk)
{
	if ((*tk)->type[3] == 5)
	{
		char *inp = "";
		while (inp && (*tk)->next && (*tk)->next->arg
			&& ft_strncmp((*tk)->next->arg, inp, -1) != 0)
		{
			inp = readline(O"> "E);
			free (inp);
		}
	}
	return (SUCCESS);
}

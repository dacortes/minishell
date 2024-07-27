/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:11:11 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/27 09:28:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_stdinp(t_token *current, int *redir, int *status)
{
	if (current && current->type == R_IN)
	{
		if (redir[0] >= STDIN_FILENO)
			close(redir[0]);
		parse_open(current, R_IN, redir);
	}
	return (*status);
}

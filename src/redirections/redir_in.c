/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:11:11 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/27 14:50:37 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_stdinp(t_token *current, int *redir, int *status)
{
	if (current && current->type == R_IN)
	{
		if (redir[0] > 0)
			close(redir[0]);
		*status = parse_open(current, R_IN, redir);
	}
	return (*status);
}

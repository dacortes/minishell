/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:28 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/27 14:51:02 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_stdout(t_token *current, int *redir, int	*status)
{
	if (current && current->type == R_OUT)
	{
		if (redir[1] > 0)
			close (redir[1]);
		*status = parse_open(current, R_OUT, redir);
	}
	return (*status);
}

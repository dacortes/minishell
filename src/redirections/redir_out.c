/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:28 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/07 17:04:23 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	_stdout(t_minishell *mini, t_basic *current)
{
	int	fd;

	if (current->data.token->type == R_OUT)
	{
		mini->status = parse_open(current);
		if (mini->status)
			return (FAILURE);
		fd = open(current->data.token->content, O_WRONLY | O_CREAT);
		if (fd == ERROR)
			return (error_msg(PERROR, 1, current->data.token->content));
		if (dup2(fd, 1) == FAILURE)
			return (error_msg(PERROR, 1, "Dup2")); 
		close(fd);
	}
	return (EXIT_SUCCESS);
}

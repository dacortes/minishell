/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:11:11 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/09 18:44:32 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	_stdinp(t_minishell *mini, t_basic *current)
{
	int	fd;

	if (current->data.token->type == R_IN)
	{
		mini->status = parse_open(current);
		if (mini->status)
			return (EXIT_FAILURE);
		fd = open(current->next->data.token->content, O_RDONLY);
		if (fd == ERROR)
			return (error_msg(PERROR, 1, current->next->data.token->content));
		if (dup2(fd, 0) == ERROR)
			return (error_msg(PERROR, 1, "Dup2")); 
		close(fd);
	}
	return (EXIT_SUCCESS);
}

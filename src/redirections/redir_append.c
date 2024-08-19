/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:14:08 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/19 20:05:54 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	_append(t_minishell *mini, t_basic *current)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_APPEND;
	if (current->data.token->type == R_APP)
	{
		mini->status = parse_open(current);
		if (mini->status)
			return (EXIT_FAILURE);
		fd = open(current->next->data.token->content, flags, 0666);
		if (fd == ERROR)
			return (error_msg(PERROR, 1, current->next->data.token->content));
		if (dup2(fd, 1) == ERROR)
			return (error_msg(PERROR, 1, "Dup2"));
		close(fd);
	}
	return (EXIT_SUCCESS);
}

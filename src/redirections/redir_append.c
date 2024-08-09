/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:14:08 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/09 16:00:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	is_append(t_token *token, int *redir, int *status)
// {
// 	t_token *next;
// 	char	*file;

// 	next = token->next;
// 	if (next && next->type == R_APP)
// 	{
// 		file = next->content;
// 		if (redir[1] >= 0)
// 			close(redir[1]);
// 		if (!access(file, F_OK) && access(file, W_OK))
// 			return (error_msg(PERROR, 1, file));
// 		redir[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
// 		if (redir[1] == ERROR)
// 			return (error_msg(PERROR, 1, file));
// 	}
// 	return (*status);
// }

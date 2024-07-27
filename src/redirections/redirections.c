/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:14:27 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/27 09:34:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//se asume que la token next existe
int	parse_open(t_token *current, int type, int *redir)
{
	char	*file;

	file = current->next->content;
	if (type == R_IN)
	{
		if (access(file, F_OK) == ERROR)
			return (error_msg(PERROR, 1, file));
		if (access(file, R_OK) == ERROR)
			return (error_msg(PERROR, 1, file));
		redir[0] = open(file, O_RDONLY);
		if (redir[0] == ERROR)
			return (error_msg(PERROR, 1, file));
	}
	if (type == R_OUT)
	{
		if (!access(file, F_OK) && access(file, W_OK))
			return (error_msg(PERROR, 1, file));
		redir[1] = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (redir[1] == ERROR)
			return (error_msg(PERROR, 1, file));
	}
	return (EXIT_SUCCESS);
}

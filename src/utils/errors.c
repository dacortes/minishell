/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:55:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/10/17 18:36:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_msg(int error, int code_exit, char *input)
{
	int	e;

	(void)e;
	e = error & MALLOC && fd_printf(2, ERR_MALLOC, MINI, input);
	e = error & SYNTAX && fd_printf(2, ERR_SYNTAX, MINI, input);
	e = error & ARGUMENT && fd_printf(2, ERR_ARGUMENT, MINI, input);
	e = error & EXPORT && fd_printf(2, ERR_EXPORT, MINI, input);
	e = error & AMBIGUOUS && fd_printf(2, ERR_AMBIGUOUS, MINI, input);
	e = error & NO_FOUND && fd_printf(2, ERR_NO_FOUND, MINI, input);
	e = error & IS_DIR && fd_printf(2, ERR_IS_DIR, MINI, input);
	e = error & NUMERIC_ARG && fd_printf(2, ERR_NUMERIC, MINI, input);
	if (error == PERROR)
	{
		fd_printf(2, "%s%s: ", MINI, input);
		perror("");
	}
	return (code_exit);
}

void	*protected(void *memory, char *error_str)
{
	if (!memory)
		exit(error_msg(MALLOC, 1, error_str));
	return (memory);
}

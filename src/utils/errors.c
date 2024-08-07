/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:55:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/07 13:04:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_msg(int error, int code_exit, char *input)
{
	int	e;

	e = error & MALLOC && fd_printf(2, "%s%s `%s'\n", MINI, ERR_MALLOC, input);
	e = error & SYNTAX && fd_printf(2, "%s%s `%s'\n", MINI, ERR_SYNTAX, input);
	e = error & ARGUMENT && fd_printf(2, "%s%s `%s'\n", MINI, ERR_ARGUMENT, input);
	e = error & EXPORT && fd_printf(2, "%s%s `%s'\n", MINI, ERR_EXPORT, input);
	if (error == PERROR)
	{
		fd_printf(2, "%s%s: ", MINI, input);
		perror("");
	}
	(void)e;/*QUITAR AL ENTREGAR*/
	return (code_exit);
}

void	*protected(void *memory, char *error_str)
{
	if (!memory)
		exit(error_msg(MALLOC, 1, error_str));
	return (memory);
}
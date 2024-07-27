/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:55:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/27 12:01:32 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*error_normalization(char *input)
{
	char	*result;

	result = input;
	if (!input)
		return (NULL);
	if ((input[0] == DOUBLE_QUOTES) || (input[0] == SIMP_QUOTES))
		return (result);
	if (input[0] == '(')
		result = ")\0";
	return (result);
}

int	error_msg(int error, int code_exit, char *input)
{
	int	e;

	e = error & MALLOC && fd_printf(2, "%s%s `%s'\n", MINI, ERR_MALLOC, input);
	e = error & SYNTAX && fd_printf(2, "%s%s `%s'\n", MINI, ERR_SYNTAX, input);
	e = error & ARGUMENT && fd_printf(2, "%s%s `%s'\n", MINI, ERR_ARGUMENT, input);
	if (error == PERROR)
	{
		fd_printf(2, "%s%s: ", MINI, input);
		perror("");
	}
	(void)e;/*QUITAR AL ENTREGAR*/
	return (code_exit);
}

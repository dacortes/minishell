/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:55:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/11 13:39:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

char	*error_normalization(char *input)
{
	if (!input)
		return (NULL);
	if ((input[0] == DOUBLE_QUOTES) || (input[0] == SIMP_QUOTES))
		return (input);
	if ((input[0] == 40))
		input[0] = 41;
	return (input);
}

int	error_msg(int error, int code_exit, char *input)
{
	int	i;

	i = (error == SYNTAX) && fd_printf(2, "%s%s %s\n", MINI, ERR_SYNTAX, input);
	
	(void)i;
	return (code_exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:51:17 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/11 14:55:29 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	get_stt(int flag, int val)
{
	static int	var;

	if (flag == TRUE)
		var = val;
	return (var);
}

void	print_line(t_line *ln)
{
	t_line	*iter;

	if (!ln)
		return ;
	iter = ln;
	while (iter)
	{
		show_tokens(iter);
		iter = iter->next;
	}
}

int	msg_error(int e, int exit_, char *cm)
{
	e == E_NSF && fd_printf(2, "mini: %s: No such file or directory\n", cm);
	e == E_MEM && fd_printf(2, "mini: error trying to allocate memory\n", cm);
	e == E_EXP && fd_printf(2, "mini: export: `%s\': not a valid identifier\n" \
		, cm);
	e == E_ISD && fd_printf(2, "mini: %s: is a directory\n", cm);
	e == E_PRM && fd_printf(2, "mini: %s: Permission denied\n", cm);
	e == E_CNF && fd_printf(2, "mini: %s: command not found\n", cm);
	e == EX && fd_printf(2, "mini: exit: %s: numeric argument required\n", cm);
	e == E_ARG && fd_printf(2, "mini: %s: too many arguments\n", cm);
	e == E_SNT && fd_printf(2, "mini: syntax error near unexpected token %s\n", \
		cm);
	e == E_BADINT && fd_printf(2, "mini: %s: bad interpreter: No such file"\
		"or directory\n", cm);
	if (e == E_PRR)
		perror("mini");
	return (exit_);
}

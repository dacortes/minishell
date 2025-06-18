/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:48:38 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/18 16:48:53 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_break_it(int flag, int value)
{
	static int	_break;

	if (flag == TRUE)
		_break = value;
	return (_break);
}

void	break_it(int signal)
{
	if (signal == SIGINT)
		get_break_it(TRUE, 1);
}

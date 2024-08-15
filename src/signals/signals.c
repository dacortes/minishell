/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:51:47 by codespace         #+#    #+#             */
/*   Updated: 2024/08/15 19:25:24 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_status(int flag, int value)
{
	static int	var;

	if (flag == TRUE)
		var = value;
	return (var);
}

void	term_init(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == ERROR)
		exit (error_msg(PERROR, 1, "term_init: term"));
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == ERROR)
		exit (error_msg(PERROR, 1, "term_init: term"));
}

void	_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_status(TRUE, 130);
	}
}

void	handle_siginth(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		exit(130);
	}
}

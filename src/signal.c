/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:21:06 by fcespede          #+#    #+#             */
/*   Updated: 2023/11/12 18:54:03 by fcespede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

void	term_init(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_stt(TRUE, 1);
	}
}

void	handle_siginth(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		exit(1);
	}
}

void	handle_signaled(int *status, int signal)
{
	if (signal == 2)
		ft_printf("^C\n");
	else if (signal == 3)
		ft_printf("^\\Quit: 3\n");
	*status = 128 + signal;
}

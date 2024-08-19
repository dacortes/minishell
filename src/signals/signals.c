/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:51:47 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/19 21:07:35 by frankgar         ###   ########.fr       */
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
		ft_printf("%s>%sX%s\n", ORANGE, RED, END);
		exit(130);
	}
}

void	handle_signaled(int *status, int signal)
{
	if (signal == 2)
		ft_printf("^C\n");
	else if (signal == 3)
		ft_printf("Quit: (core dumped)\n");
	*status = 128 + signal;
}

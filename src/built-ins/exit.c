/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:41:31 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/16 17:50:41 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_loop(t_minishell *mini, char **command)
{
	int	i;

	if (ft_strlen(command[1]) > 18)
		exit (error_msg(NUMERIC_ARG, 2, command[1]));
	if (command[1][0] && (command[1][0] == '-' || command[1][0] == '+') \
		&& (!command[1][1]))
		exit (error_msg(NUMERIC_ARG, 2, command[1]));
	else if (command[1][0] && (command[1][0] == '-' || command[1][0] == '+') \
		&& command[1][1] && !ft_isdigit(command[1][1]))
		exit (error_msg(NUMERIC_ARG, 2, command[1]));
	i = 0;
	while (command[1][i])
	{
		if (!ft_isdigit(command[1][i]) && command[1][i] != '-' \
			&& command[1][i] != '+')
		{
			free_minishell(mini, FALSE);
			exit (error_msg(NUMERIC_ARG, 2, command[1]));
		}
		i++;
	}
}

int	_exit_(t_minishell *mini, char **command, int num_arg)
{
	if (num_arg == 1)
	{
		free_minishell(mini, FALSE);
		exit(mini->prev_status);
	}
	else if (num_arg >= 2)
	{
		exit_loop(mini, command);
		if (num_arg > 2)
			return (error_msg(ARGUMENT, 1, "exit"));
		exit(ft_atoi(command[1]));
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:41:31 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/08 19:03:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_loop(t_minishell *mini, char **command)
{
	int	i;

	if (command[1][0] && (command[1][0] == '-' || command[1][0] == '+') \
		&& (!command[1][1]))
		exit (error_msg(EXIT, 255, command[1]));
	else if (command[1][0] && (command[1][0] == '-' || command[1][0] == '+') \
		&& command[1][1] && !ft_isdigit(command[1][1]))
		exit (error_msg(EXIT, 255, command[1]));
	i = 0;
	while (command[1][i])
	{
		if (!ft_isdigit(command[1][i]) && command[1][i] != '-' \
			&& command[1][i] != '+')
		{
			free_minishell(mini, FALSE);
			exit (error_msg(EXIT, 255, command[1]));
		}
		i++;
	}
}

int	_exit_(t_minishell *mini, char **command, int num_arg)
{
	if (num_arg == 1)
		free_minishell(mini, FALSE);//puede tener problemas cuando esta dentro de un hijo
	else if (num_arg >= 2)
	{
		exit_loop(mini, command);
		if (num_arg > 2)
			return (error_msg(ARGUMENT, 1, "exit"));
		//puede que tengamos que limpiar la memoria
		exit(ft_atoi(command[1]));
	}
	return (EXIT_SUCCESS);
}
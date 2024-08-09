/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:04:09 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/09 10:27:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *cmd)
{
	static char	**builtins = {"echo", "cd", "pwd", "export", "unset", "env", \
								"exit"};
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(cmd);
	while (builtins[i])
	{
		if (ft_strncmp(builtins[i], cmd, len))
			return (TRUE)
	}
	return (FALSE);
}

int	do_builtin(t_minishell *mini, char **cmd)
{
	static char	**builtins = {"echo", "cd", "pwd", "export", "unset", "env", \
		"exit"};
	if (ft_strncmp(builtins[0], cmd[0], -1) == EXIT_SUCCESS)
		_echo();
	return (EXIT_SUCCESS);
}

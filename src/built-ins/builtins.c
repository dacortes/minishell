/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:04:09 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/07 20:53:47 by frankgar         ###   ########.fr       */
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
}

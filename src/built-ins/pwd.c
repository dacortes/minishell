/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:37:30 by codespace         #+#    #+#             */
/*   Updated: 2024/07/24 12:42:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	_pwd(void)
{
	char	*dir;

	dir = get_pwd();
	ft_printf("%s\n", dir);
	if (dir)
	{
		free(dir);
		dir = NULL;
	}
	return (EXIT_SUCCESS);
}

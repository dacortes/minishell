/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:52:18 by codespace         #+#    #+#             */
/*   Updated: 2024/07/21 15:26:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_pwd(void)
{
	char	*dir;

	dir = ft_calloc(PATH_MAX, 1);
	if (!dir)
		exit(error_msg(MALLOC, 1, "get_pwd: dir"));
	if (getcwd(dir, PATH_MAX) == NULL)
	{
		error_msg(PERROR, 1, "getcwd");
		return (NULL);
	}
	return (dir);
}

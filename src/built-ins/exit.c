/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:10:46 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/26 12:05:09 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int ft_exit(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		free(input);
		exit (SUCCESS);
	}
	return (ERROR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:45:40 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/10 18:14:00 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int pwd(void)
{
	char	dir[PATH_MAX];
	
	if (getcwd(dir, sizeof(dir)) == NULL)
		return(msg_error(E_PRR, E_EXIT, "getcwd"));
	printf("%s\n", dir);
	return (SUCCESS);
}

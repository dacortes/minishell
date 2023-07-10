/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:07:55 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/10 17:06:45 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/* si el home no tiene nada */
/* tenemos que guardar la ubicacion del pwd el actual y el old */
/* hay que crear un getenv propio para saber puntualmente donde se encuentra*/
int	cd(char *path)
{
	char	dir[PATH_MAX];
	int		chek;

	if (sizeof(path) >= PATH_MAX)
		return (msg_error(E_NSF, E_EXIT, "chdir"));
	if (!path)
	{
		chdir(getenv("HOME"));
		/* esto hay que cambiarlo hay 
		que actualizar el olpwd al new*/
		if (getcwd(dir, sizeof(dir)) == NULL)
			return(msg_error(E_FTN, E_EXIT, "getcwd"));
		printf("%s\n", dir);
	}
	chek = chdir(path);
	if (path && chek < SUCCESS)
		return (msg_error(E_NSF, E_EXIT, "chdir"));
	else if (path && chek == SUCCESS)
	{
		if (getcwd(dir, sizeof(dir)) == NULL)
			return(msg_error(E_FTN, E_EXIT, "getcwd"));
		printf("%s\n", dir);
	}
	return (SUCCESS);
}

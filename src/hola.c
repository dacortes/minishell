/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hola.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/10 15:42:32 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	msg_error(int e, int exit_, char *cm)
{
	e == E_NSF && fd_printf(2, "mini: %s: No such file or directory\n", cm);
	return (exit_);	
}

/* si el home no tiene nada */
/* tenemos que guardar la ubicacion del pwd el actual y el old */
/* hay que crear un getenv propio para saber puntualmente donde se encuentra*/
int	cd(char *path)
{
	char dir[4096];

	if (sizeof(path) >= 4096)
		return (msg_error(E_NSF, E_EXIT, "chdir"));
	if (!path)
	{
		chdir(getenv("HOME")); /* esto hay que cambiarlo hay que actualizar el olpwd al new*/
		printf("%s\n", getcwd(dir, sizeof(dir)));
	}
	if (path && chdir(path) < SUCCESS)
		return (msg_error(E_NSF, E_EXIT, "chdir"));
	else
		printf("Cambio de dic %s", getcwd(dir, sizeof(dir)));
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	cd(NULL);
	return (0);	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/23 15:41:08 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	msg_error(int e, int exit_, char *cm)
{
	e == E_NSF && fd_printf(2, "mini: %s: No such file or directory\n", cm);
	e == E_MEM && fd_printf(2, "mini: error trying to allocate memory\n", cm);
	e == E_EXP && fd_printf(2, "mini: export: not an identifier:%s\n", cm);
	if (e == E_PRR)
		perror("mini");
	return (exit_);	
}
/*
	funcion para limpiar el env temporalmente 
	hay que hacer una funcion que limpie y imprima los msg de error cuando falla
*/
int	clear(t_mini *sh)
{
	t_env	*rm;
	t_env	*tmp;

	rm = sh->env;
	while (rm)
	{
		tmp = rm;
		if (rm->key)
			free(rm->key);
		if (rm->val)
			free(rm->val);
		rm = rm->next;
		free(tmp);
	}
	free(sh);
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_mini *sh;

	char *input = NULL;
	sh = ft_calloc(sizeof(t_mini), 1);
	if (!sh)
		exit (msg_error(E_MEM, 1, NULL));
	sh->env = NULL;
	init_env(sh, env);
	while (TRUE)
	{
		input = readline(O"ᐅ"E);
		ft_printf(R"input"E"=%p\n", input);
		if (ft_strncmp(input, "export", 6) == 0)
		{
			ft_printf(R"input"E"=%s\n", input);
			_export(sh, ft_strchr(input, 'a'));
			_env(sh->env);
		}
		if (ft_strncmp(input, "exit", -1) == 0)
		{
			free(input);
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		free(input);
	}
	clear(sh);
	return (SUCCESS);
}
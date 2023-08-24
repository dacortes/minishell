/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/24 10:55:05 by dacortes         ###   ########.fr       */
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
	if (sh->dir)
		free(sh->dir);
	if (sh->old)
		free(sh->old);
	free(sh);
	return (SUCCESS);
}

int	mini_init(t_mini **sh, char **env)
{
	*sh = (t_mini *)ft_calloc(sizeof(t_mini), 1);
	if (!sh)
		exit (msg_error(E_MEM, 1, NULL));
	(*sh)->size = 0;
	(*sh)->env = NULL;
	init_env(*sh, env);
	(*sh)->user = search_env((*sh)->env, "USER", VAL);
	(*sh)->dir = ft_strdup(search_env((*sh)->env, "PWD", VAL));
	(*sh)->old = ft_strdup(search_env((*sh)->env, "OLDPWD", VAL));
	return (SUCCESS);
}

int	prompt(t_mini **sh, char **input)
{
	(*sh)->user = search_env((*sh)->env, "USER", VAL);
	if (!(*sh)->dir[1])
		ft_printf(F"%s➜ "C"%s 🗂 ", (*sh)->user, ft_strrchr((*sh)->dir, '/'));
	else
		ft_printf(F"%s➜ "C"%s 🗂 ", (*sh)->user, &ft_strrchr((*sh)->dir, '/')[1]);
	*input = readline(O" ᐅ "E);
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_mini *sh;

	char *input = NULL;
	mini_init(&sh, env);
	while (TRUE)
	{
		prompt(&sh, &input);
		if (ft_strncmp(input, "export", 6) == 0)
		{
			ft_printf(R"input"E"=%s\n", input);
			_export(sh, "f_a=20"/*ft_strchr(input, 'a')*/);
			show_export(sh->env);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/29 15:31:44 by fcespede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	msg_error(int e, int exit_, char *cm)
{
	e == E_NSF && fd_printf(2, "mini: %s: No such file or directory\n", cm);
	e == E_MEM && fd_printf(2, "mini: error trying to allocate memory\n", cm);
	e == E_EXP && fd_printf(2, "mini: export: not an identifier:%s\n", cm);
	e == E_CNF && fd_printf(2, "mini: %s: command not found\n", cm);
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

int	init_tk(/*t_token **tk,*/ char *inp)
{
	int end;

	end = -1;
	// *tk = NULL;
	// while (inp[++end])
	// 	token(inp, &end);
	ft_printf("Estamos con comillas ? %i\n", token(inp));
	return (SUCCESS);
}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_mini *sh;
//	t_token *tk;

	char *inp = NULL;
	mini_init(&sh, env);
	while (TRUE)
	{
		prompt(&sh, &inp);
		init_tk(inp);
		if (ft_strncmp(inp, "unset", -1) == 0)
			unset(&sh->size, &sh->env, inp);
		if (ft_strncmp(inp, "pwd", 3) == 0)
			pwd();
		if (ft_strncmp(inp, "env", 3) == 0)
			_env(sh->env);
		if (ft_strncmp(inp, "cd", 2) == 0)
			cd(inp + 3, &sh);
		if (ft_strncmp(inp, "exit", 4) == 0)
			ft_exit(inp);
		if (inp[0] != '\0')
			add_history(inp);
		free(inp);
	}
	clear(sh);
	return (SUCCESS);
}
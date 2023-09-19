/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/19 18:28:17 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	msg_error(int e, int exit_, char *cm)
{
	e == E_NSF && fd_printf(2, "mini: %s: No such file or directory\n", cm);
	e == E_MEM && fd_printf(2, "mini: error trying to allocate memory\n", cm);
	e == E_EXP && fd_printf(2, "mini: export: not an identifier:%s\n", cm);
	e == E_CNF && fd_printf(2, "mini: %s: command not found\n", cm);
	e == EX && fd_printf(2, "mini: exit: %s: numeric argument required\n", cm);
	e == E_ARG && fd_printf(2, "mini: %s: too many arguments\n", cm);
	e == E_SNT && fd_printf(2, "mini: syntax error near unexpected token %s\n", \
		cm);
	if (e == E_PRR)
		perror("mini");
	return (exit_);
}

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

/*
	hay que actualizar el oldpwd cuado es nuevo y sino exite agregarlo
*/
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
	if (!search_env((*sh)->env, "OLDPWD", VAL))
		(*sh)->old = ft_strdup("");
	else
		(*sh)->old = ft_strdup(search_env((*sh)->env, "OLDPWD", VAL));
	return (SUCCESS);
}

int	prompt(t_mini **sh, char **input)
{
	(*sh)->user = search_env((*sh)->env, "USER", VAL);
	if (!(*sh)->dir[1])
		ft_printf(F"%s➜ "C"%s 🗂 ", (*sh)->user, ft_strrchr((*sh)->dir, '/'));
	else
		ft_printf(F"%s➜ "C"%s 🗂 ", (*sh)->user, \
			&ft_strrchr((*sh)->dir, '/')[1]);
	*input = readline(O" ᐅ "E);
	return (SUCCESS);
}

/* hay que construir los argumentos con un join ya se implemento la funcion de saber si hay espacios*/
int	main(int ac, char **av, char **env)
{
	t_mini	*sh;
	t_line	*ln;
	char	*inp;
	int		chk;

	inp = NULL;
	(void)ac;
	(void)av;
	mini_init(&sh, env);
	while (TRUE)
	{
		ln = NULL;
		prompt(&sh, &inp);
		if (!inp)
			exit (0);
		chk = ft_line(inp, &ln, sh->env);
		if (chk != E_SNT)
			chk = ft_parse(&ln);
		ft_printf(O"Content\n"E);
		show_line(ln);
		if (inp[0] && chk != E_SNT)
		{
			if (ln->argv[0] && ft_strncmp(ln->argv[0], "unset", ft_strlen(ln->argv[0])) == 0)
				unset(&sh->size, &sh->env, inp);
			else if (ln->argv[0] && ft_strncmp(ln->argv[0], "pwd", ft_strlen(ln->argv[0])) == 0)
				pwd();
			else if (ln->argv[0] && ft_strncmp(ln->argv[0], "env", ft_strlen(ln->argv[0])) == 0)
				_env(sh->env);
			else if (ln->argv[0] && ft_strncmp(ln->argv[0], "cd", ft_strlen(ln->argv[0])) == 0)
				ft_cd(ln, &sh);
			else if (ln->argv[0] && ft_strncmp(ln->argv[0], "exit", ft_strlen(ln->argv[0])) == 0)
				ft_exit(&ln, sh, ln->argv, ln->argc);
			else if (ln->argv[0] && ft_strncmp(ln->argv[0], "echo", ft_strlen(ln->argv[0])) == 0)
				ft_echo(ln->argv, ln->argc);
		}
		if (inp[0] != '\0')
			add_history(inp);
		clear_ln(&ln);
		free(inp);
	}
	return (SUCCESS);
}

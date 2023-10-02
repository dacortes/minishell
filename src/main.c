/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/02 18:51:44 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	msg_error(int e, int exit_, char *cm)
{
	e == E_NSF && fd_printf(2, "mini: %s: No such file or directory\n", cm);
	e == E_MEM && fd_printf(2, "mini: error trying to allocate memory\n", cm);
	e == E_EXP && fd_printf(2, "mini: export: `%s\': not a valid identifier\n" \
		, cm);
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

int	main(int ac, char **av, char **env)
{
	t_mini	*sh;
	t_line	*ln;
	t_get	*g;
	char	*inp;
	int		chk;
	int		pipe;

	(void)ac;
	(void)av;
	chk = 0;
	pipe = 0;
	g = NULL;
	inp = NULL;
	mini_init(&sh, env);
	while (TRUE)
	{
		ln = NULL;
		prompt(&sh, &inp);
		if (!inp)
			exit (0);
		chk = ft_line(inp, &ln, sh->env, &pipe);
		if (chk != E_SNT)
			chk = parse(&ln);
		if (chk != E_SNT)
			get_init(&ln, &g);
		/* antes de ejecutar validar los pipes */
		if (!pipe)
		{
			if (is_built_ins(&sh, &ln, &g, &chk) == ERROR)
				ft_printf(R"not buit-ins\n"E);
		}
		else
		{
			t_get *iter;

			iter = g;
			while (iter)
			{
				if (is_built_ins(&sh, &ln, &iter, &chk) == ERROR)
					ft_printf(R"not buit-ins\n"E);
				iter = iter->next;
			}
		}
		pipe = 0;
		if (inp[0] != '\0')
			add_history(inp);
		clear_get(&g);
		clear_ln(&ln);
		free(inp);
	}
	return (SUCCESS);
}

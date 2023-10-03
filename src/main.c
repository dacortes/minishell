/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/03 18:54:25 by dacortes         ###   ########.fr       */
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

int	mini_init(t_mini **sh, t_get **g, t_exe *ex, char **env)
{
	*g = NULL;
	ft_bzero(ex, sizeof(t_exe));
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
	t_exe	ex;

	(void)av;
	if (ac > 1)
		exit (TRUE);
	mini_init(&sh, &g, &ex, env);
	while (TRUE)
	{
		ln = NULL;
		prompt(&sh, &ex.inp);
		ex.stt = ft_line(ex.inp, &ln, sh->env, &ex.pipe);
		(ex.stt != E_SNT) && (ex.stt = parse(&ln));
		(ex.stt != E_SNT) && (ex.stt = get_init(&ln, &g));
		(ex.stt != E_SNT) && (ex.stt = get_path(&ex, g, search_env(sh->env, "PATH", VAL)));
		ex.env = env_to_array(sh);
		if (ex.stt != E_SNT && !ex.pipe)
		{
			if (is_built_ins(&sh, &ln, &g, &ex.stt) == ERROR)
			{
				ft_printf(R"not buit-ins\n"E);
			}
		}
		else if (ex.stt != E_SNT && ex.pipe)
		{
			t_get *iter;

			iter = g;
			while (iter)
			{
				if (is_built_ins(&sh, &ln, &iter, &ex.stt) == ERROR)
					ft_printf(R"not buit-ins\n"E);
				iter = iter->next;
			}
		}
		ex.pipe = 0;
		//free del cmd hay que hacerlo mejor
		if (ex.cmd && *ex.cmd)
			free(ex.cmd);
		clear_dptr((void **)ex.pht);
		clear_dptr((void **)ex.env);
		if (ex.inp[0] != '\0')
			add_history(ex.inp);
		clear_get(&g);
		clear_ln(&ln);
		free(ex.inp);
	}
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/05 11:32:23 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	msg_error(int e, int exit_, char *cm)
{
	e == E_NSF && fd_printf(2, "mini: %s: No such file or directory\n", cm);
	e == E_MEM && fd_printf(2, "mini: error trying to allocate memory\n", cm);
	e == E_EXP && fd_printf(2, "mini: export: `%s\': not a valid identifier\n" \
		, cm);
	e == E_ISD && fd_printf(2, "mini: %s: is a directory\n", cm);
	e == E_PRM && fd_printf(2, "mini: %s: Permission denied\n", cm);
	e == E_CNF && fd_printf(2, "mini: %s: command not found\n", cm);
	e == EX && fd_printf(2, "mini: exit: %s: numeric argument required\n", cm);
	e == E_ARG && fd_printf(2, "mini: %s: too many arguments\n", cm);
	e == E_SNT && fd_printf(2, "mini: syntax error near unexpected token %s\n", \
		cm);
	e == E_BADINT && fd_printf(2, "mini: %s: bad interpreter: No such file"\
		"or directory\n", cm);
	if (e == E_PRR)
		perror("mini");
	return (exit_);
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
	char	*need[9];
	char	*join;

	(*sh)->user = search_env((*sh)->env, "USER", VAL);
	need[0] = F;
	need[1] = (*sh)->user;
	need[2] = "➜";
	need[3] = C;
	need[5] = O;
	need[6] = " 🗂 ᐅ ";
	need[7] = E;
	need[8] = NULL;
	if (!(*sh)->dir[1])
		need[4] = ft_strrchr((*sh)->dir, '/');
	else
		need[4] = &ft_strrchr((*sh)->dir, '/')[1];
	join = ft_strjoin_max(need);
	*input = readline(join);
	if (join)
		free(join);
	return (SUCCESS);
}

void print_line(t_line *ln)
{
	t_line	*iter;

	if (!ln)
		return;
	iter = ln;
	while (iter)
	{
		show_tokens(iter);
		iter = iter->next;
	}
}

int get_stt(int flag, int val)
{
	static int	var;

	if (flag == TRUE)
		var = val;
	return (var);	
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
		get_env(TRUE, sh->env);
		ln = NULL;
		prompt(&sh, &ex.inp);
		is_null(&sh, &ln, &g, ex.inp);
		ex.stt = ft_line(ex.inp, &ln, sh->env, &ex.pipe);
		(ex.stt == 0) && (ex.stt = parse(&ln));
		(ex.stt == 0) && (ex.stt = get_init(&ln, &g, &ex.stt));
		ex.env = env_to_array(sh);
		if (!ex.pipe)
			no_pipe(&sh, &ln, &g, &ex);
		if (!ex.stt && ex.pipe)
			pipes(&sh, &ln, &g, &ex);
		// 	create_childs(&sh, &ln, &g, &ex);
		get_stt(TRUE , ex.stt);
		ex.pipe = 0;
		clear_pross(&ln, &g, ex);
	}
	return (SUCCESS);
}
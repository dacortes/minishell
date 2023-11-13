/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/13 15:16:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

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

void	init_exec(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	get_env(TRUE, (*sh)->env);
	ex->stt = prompt(sh, &ex->inp) + is_null(sh, ln, g, ex->inp);
	signal(SIGINT, SIG_IGN);
	ex->stt = ft_line(ex->inp, ln, (*sh)->env, &ex->pipe);
	(ex->stt == 0) && (ex->stt = parse(ln));
	(ex->stt == 0) && (ex->stt = get_init(ln, g, &ex->stt));
	ex->env = env_to_array(*sh);
	(!ex->pipe) && (no_pipe(sh, ln, g, ex));
	(!ex->stt && ex->pipe) && (pipes(sh, ln, g, ex));
	get_stt(TRUE, ex->stt);
	ex->pipe = 0;
	clear_pross(ln, g, *ex);
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
	term_init();
	while (TRUE)
	{
		ln = NULL;
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		ex.stt = get_stt(FALSE, 0);
		init_exec(&sh, &ln, &g, &ex);
	}
	return (SUCCESS);
}

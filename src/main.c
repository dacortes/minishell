/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/25 11:32:27 by dacortes         ###   ########.fr       */
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

// int	test(char *inp)
// {
// 	t_cmd	cmd;
// 	int 	i;
// 	int		e;
	
// 	i = 0;
// 	while (inp[i] && inp[i] == ' ')
// 		i++;
// 	cmd.type = (inp[i] == D_QUOTES);
// 	cmd.type = (inp[i] == QUOTES) + 1;
// 	i += (inp[i] == D_QUOTES) || (inp[i] == QUOTES);
// 	e = i;
// 	while (inp[e] && inp[e] != QUOTES && inp[e] != D_QUOTES)
// 		e++;
// 	e -= (inp[e] == D_QUOTES) || (inp[e] == QUOTES);
// 	cmd.cmd = ft_substr(inp, i, e);
// 	while (inp[e] && inp[i] == ' ')
// 		e++;
// 	cmd.arg = ft_substr(inp, i, e);
// 	ft_printf(B"cmmd:%s arg:%sla i: %d, la e:%d\n"E, cmd.cmd, i, e);
// 	free(cmd.cmd);
// 	free(cmd.arg);
// 	return (SUCCESS);
// }

/* test token */
int	token(char *inp)
{
	t_token	tk;
	char	del;

	del = ' ';
	int i = 0;
	int	e = 0;
	while (inp[i] && inp[i] == ' ')
		i++;
	del = ' ' + ((inp[i] == D_QUOTES) * 2) + ((inp[i] == QUOTES) * 7);
	i += (inp[i] == D_QUOTES) || (inp[i] == QUOTES);
	e = i;
	ft_printf(B"del=%i\n"E, del);
	while(inp[e] && inp[e] != del)
	{
		if (inp[e] == D_QUOTES || inp[e] == QUOTES)
			break ;
		e++;
	}
	e -= (inp[e] == D_QUOTES) || (inp[e] == QUOTES);
	e += ((inp[e + 1] != D_QUOTES) * (inp[e + 1] != QUOTES) * (inp[e + 1] != ' '));
	//ft_printf("oper=%i\n", ((inp[e] != D_QUOTES) * (inp[e] != QUOTES) * (inp[e] != ' ')));
	tk.arg = ft_substr(inp, i, e);
	ft_printf(R"del=%i arg=%s# init=%i end=%i \n"E, del, tk.arg, i, e);
	free(tk.arg);
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_mini *sh;

	char *inp = NULL;
	mini_init(&sh, env);
	while (TRUE)
	{
		prompt(&sh, &inp);
		// test(inp);
		token(inp);
		if (ft_strncmp(inp, "exit", -1) == 0)
		{
			free(inp);
			break ;
		}
		if (inp[0] != '\0')
			add_history(inp);
		free(inp);
	}
	clear(sh);
	return (SUCCESS);
}
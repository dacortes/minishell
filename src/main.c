/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/28 13:40:59 by dacortes         ###   ########.fr       */
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

int mini_init(t_mini **sh, char **env)
{
	int	i;

	i = ft_double_ptr_len((void **)env) - 1;
	*sh = (t_mini *)ft_calloc(sizeof(t_mini), 1);
	if (!sh)
		exit (msg_error(E_MEM, 1, NULL));
	(*sh)->e_size = 0;
	(*sh)->env = NULL;
	while (env[i])
		new_var_env(*sh, env[i--]);
	(*sh)->user = find_var_env((*sh)->env, "USER", KEY);
	(*sh)->dir = ft_strdup(find_var_env((*sh)->env, "PWD", KEY));
	(*sh)->old = ft_strdup(find_var_env((*sh)->env, "OLDPWD", KEY));
	return (SUCCESS);
}

int	prompt(t_mini **sh, char **input)
{
	(*sh)->user = find_var_env((*sh)->env, "USER", KEY);
	ft_printf(R"%p\n"E, (*sh)->dir);
	ft_printf(C"%s\n", (*sh)->old);
	if (!(*sh)->dir[1])
		ft_printf(F"%s➜ "C"%s 🗂", (*sh)->user, ft_strrchr((*sh)->dir, '/'));
	else
		ft_printf(F"%s➜ "C"%s 🗂", (*sh)->user, &ft_strrchr((*sh)->dir, '/')[1]);
	*input = readline(O" ᐅ "E);
	return (SUCCESS);
}

/* test con cd export env exit*/
/* falta el unset pwd*/
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*input = NULL;
	t_mini	*sh;

	mini_init(&sh, env);
	while (TRUE)
	{
		prompt(&sh, &input);
		if (ft_strncmp(input, "env", -1) == 0)
		{
			printf_env(sh->env);
			print_export(sh->env);
			magic_node(sh);
		}
		if (ft_strncmp(input, "unset", -1) == 0)
		{
			unset(&sh->e_size, &sh->env, "a");
			unset(&sh->e_size, &sh->env, "h");
			magic_node(sh);
		}
		//pwd();
		if (input[0] != '\0')
			add_history(input);
		ft_exit(input);
		free(input);
	}
	return (SUCCESS);
}
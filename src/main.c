/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/19 17:58:31 by dacortes         ###   ########.fr       */
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
	ft_printf(F"%s➜ "C"%s 🗂", (*sh)->user, &ft_strrchr((*sh)->dir, '/')[1]);
	*input = readline(O" ᐅ "E);
	return (SUCCESS);
}

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
		// cd(input, &sh);
		export(sh, input);
		printf_env(sh->env);
		if (input[0] != '\0')
			add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit (SUCCESS);
		}
		free(input);
	}
	return (SUCCESS);
}
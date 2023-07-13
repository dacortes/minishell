/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/13 12:22:07 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	msg_error(int e, int exit_, char *cm)
{
	e == E_NSF && fd_printf(2, "mini: %s: No such file or directory\n", cm);
	e == E_MEM && fd_printf(2, "mini: error trying to allocate memory\n", cm);
	if (e == E_PRR)
		perror("mini");
	return (exit_);	
}

int mini_init(t_mini **shell, char **env)
{
	int	i;

	i = ft_double_ptr_len((void **)env) - 1;
	*shell = (t_mini *)ft_calloc(sizeof(t_mini), 1);
	if (!shell)
		exit (msg_error(E_MEM, 1, NULL));
	(*shell)->e_size = 0;
	(*shell)->env = NULL;
	while (env[i])
		new_var_env(*shell, env[i--]);
	(*shell)->user = find_var_env((*shell)->env, "USER", KEY);
	(*shell)->dir = find_var_env((*shell)->env, "PWD", KEY);
	(*shell)->dir = &(ft_strrchr((*shell)->dir, '/'))[1];
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*input = NULL;
	t_mini *shell;

	mini_init(&shell, env);
	while (TRUE)
	{
		ft_printf (F"%s➜ "E, shell->user);
		ft_printf (C"%s 🗂"E, shell->dir);
		input = readline(O" ᐅ "E);
		printf("%s\n", input);
		if (input[0] != '\0')
			add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit(SUCCESS);
		}
		free(input);
	}
	return (SUCCESS);
}
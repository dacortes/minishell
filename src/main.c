/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/11 18:26:21 by dacortes         ###   ########.fr       */
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

int mini_init(t_mini **shell)
{
	*shell = (t_mini *)ft_calloc(sizeof(t_mini), 1);
	if (!shell)
		exit (msg_error(E_MEM, 1, NULL));
	(*shell)->e_size = 0;
	(*shell)->env = NULL;
	return (SUCCESS);
}

int	new_var_env(t_mini *shell, char *var)
{
	t_env	*new;
	int		len_r;
	int		len_l;

	len_r = ft_strchrpos(var, '=');
	len_l = (ft_strlen(var) - len_r);
	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->var = ft_substr(var, 0, len_r);
	if (!new->var)
		exit (msg_error(E_MEM, 1, NULL));
	new->val = ft_substr(var, len_r + 1, len_l);
	if (!new->val)
		exit (msg_error(E_MEM, 1, NULL));
	new->next = NULL;
	if (shell->e_size == 0)
		shell->env = new;
	else
	{
		new->next = shell->env;
		shell->env = new;
	}
	shell->e_size++;
	return (SUCCESS);
}

void printf_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*input = NULL;
	t_mini *shell;

	mini_init(&shell);
	int i = ft_double_ptr_len((void **)env) - 1;
	while (env[i])
		new_var_env(shell, env[i--]);
	printf("%d\n", shell->e_size);
	printf_env(shell->env);
	while (TRUE)
	{
		input = readline("hola ᐅ ");
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
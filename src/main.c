/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:40:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/11 15:14:57 by dacortes         ###   ########.fr       */
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

int	add_env(char *s_env, t_env *env)
{
	t_env *new;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		exit (msg_error(E_MEM, 1, "env"));
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, "new"));
	new->var = ft_calloc(ft_strchrpos(s_env, '=') + 1, sizeof(char));
	if (!new->var)
		exit (msg_error(E_MEM, 1, "var"));
	ft_strlcpy(new->var, s_env, ft_strchrpos(s_env, '='));
	new->val = ft_calloc(((int)ft_strlen(s_env) - ft_strchrpos(s_env, '=') + 1), sizeof(char));
	if (!new->val)
		exit (msg_error(E_MEM, 1, "var"));
	ft_strlcpy(new->val, &s_env[ft_strchrpos(s_env, '=') + 1], ft_strlen(s_env));
	printf(B"%s=%s\n"E, new->var, new->val);
	new->next = env;
	env = new;
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*input = NULL;
	t_env	ev;
	
	int i = 0;
	while(env[i])
		add_env(env[i++], &ev);
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
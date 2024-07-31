/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/31 19:40:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

int	iter_list_list_content(t_basic_list *node, void (*f)(void *))
{
	t_basic_list	*iter;


	if (!node)
		return (EXIT_SUCCESS);
	iter = node;
	while(iter)
	{
		f(&(iter->list_content));
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int	mini_rush_plus(int argc, char **argv, char **env)
{
	t_minishell	mini;
	
	(void)argc;
	(void)argv;

	ft_bzero(&mini, sizeof(t_minishell));
	mini.env = init_env(env);
	_env(mini.env, 1);
	free_list(mini.env, free_env);
	return (EXIT_SUCCESS);
}
int main(int argc, char **argv, char **env)
{
	return mini_rush_plus(argc, argv, env);
}
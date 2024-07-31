/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/31 18:44:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

int	iter_list(t_basic_list *node, void (*f)(t_type_list))
{
	t_basic_list	*iter;
	
	if (!node)
		return (EXIT_SUCCESS);
	iter = node;
	while(iter)
	{
		f(iter->list_content);
		printf("algo\n");
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
	return (EXIT_SUCCESS);
}
int main(int argc, char **argv, char **env)
{
	return mini_rush_plus(argc, argv, env);
}
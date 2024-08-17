/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:33:00 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/10 09:55:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	_unset(t_basic **env, char *key)
{
	t_basic	*rm;
	t_basic	*prev;
	t_basic	*next;

	rm = bool_loop(*env, key_compare, key);
	if (!rm)
		return (EXIT_SUCCESS);
	if (rm == *env)
		*env = rm->next;
	ft_free(&rm->data.env->key, &rm->data.env->value);
	prev = rm->prev;
	next = rm->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(rm->data.env);
	free(rm);
	_export(*env);
	return (EXIT_SUCCESS);
}

int	unset_loop(t_basic **env, char **command, int num_arg)
{
	int	i;

	if (num_arg == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (command[i])
		_unset(env, command[i++]);
	return (EXIT_SUCCESS);
}

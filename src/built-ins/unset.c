/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:33:00 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/03 08:55:44 by codespace        ###   ########.fr       */
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
	ft_free(&rm->data.env->key, &rm->data.env->value);
	prev = rm->prev;
	if (prev)
	{
		next = rm->next;
		if (next)
			prev->next = next;
		free(rm);
	}
	return (EXIT_SUCCESS);
}

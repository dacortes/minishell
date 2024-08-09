/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:42:48 by codespace         #+#    #+#             */
/*   Updated: 2024/08/09 14:50:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	content_loop(t_basic *node, void (*f)(void *))
{
	t_basic	*iter;


	if (!node)
		return (EXIT_SUCCESS);
	iter = node;
	while(iter)
	{
		f(&(iter->data));
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

t_basic *bool_loop(t_basic *node, int (*cmp)(t_data_type *, void *), void *arg)
{
    while (node)
	{
        if (cmp(&node->data, arg))
            return (node);
        node = node->next;
    }
    return (NULL);
}

t_basic *bool_loop_void(t_basic *node, int (*cmp)(void *, void *), void *arg)
{
    while (node)
	{
        if (cmp(node, arg))
            return (node);
        node = node->next;
    }
    return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:18:48 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/20 18:33:33 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_child(int mod_flag, int value)
{
	static int	child = FALSE;

	if (mod_flag == TRUE)
		child = value;
	return (child);
}

void	set_skip(t_minishell *mini, t_basic *end, int	*skip)
{
	if ((end->data.token->type == AND && !mini->status)
		|| (end->data.token->type == OR && mini->status))
	{
		*skip = 0;
		mini->prev_status = mini->status;
		get_status(TRUE, mini->status);
		mini->status = 0;
	}
	else
		*skip = 1;
}

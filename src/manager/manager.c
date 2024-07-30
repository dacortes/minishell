/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:51:44 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/30 14:43:01 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



int	manager(t_minishell *mini)
{
	t_token	*start;
	t_token	*end
	int		skip;

	skip = 0;
	start = mini->token;
	end = mini->token;
	while(end && end->next)
	{
		if (end->type == PIPE && !skip)
			execute_cmd(mini, start, end->prev); // NO EXISTE
		else if (end->type & L_OPERAND)
		{
			if (!skip)
				execute_cmd(mini, start, end->prev); // NO EXISTE
			reset_redirs(mini); // NO EXISTE
			start = end;
			if ((start->type & AND && !mini->status)
				|| (start->type & OR && mini->status))
				skip = 0;
			else if (start->type & L_OPPERAND)
				skip = 1;
		}
		end = end->next;
	}
	if (!skip)
		execute_cmd(mini, start, end->prev); // NO EXISTE
	return (mini->status);
}

















			/*
			if (end->type & S_SHELL && !skip)
			{
				pid_t	subshell;

				subshell = fork();
				if (subshell == CHILD)
				{
					mini->status = manager(&end->subs);
					exit(end->subs->status);
				}
				if (waitpid(subshell, mini->status, 0) == ERROR)
				{
					//reset_redir();
					return (EXIT_FAILURE);
				}
				mini->status = WEXITSTATUS(end->subs->status);
			} ESTO VA EN EL EJECUTOR*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:14:27 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/07 17:05:57 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redirections(t_minishell *mini, t_basic *start, t_basic *end)
{
	t_basic *tmp;

	tmp = start;
	while (tmp && tmp != end && !mini->status)
	{
		if (tmp->data.token->type & REDIR)
		{
			_stdin(mini, tmp->next);
			_stdout(mini, tmp->next);
			_heredoc(mini, tmp->next);
			_append(mini, tmp->next);
		}
		tmp = tmp->next;
	}
	if (mini->status)
		return(ERROR);
	return(EXIT_SUCCESS)
}

int	reset_redirs(t_minishell *mini)
{
	if (dup2(mini->term_fd[0], 0) == FAILURE)
		return (error_msg(PERROR, 1, "Dup2"));
	if (dup2(mini->term_fd[1], 1) == FAILURE)
		return (error_msg(PERROR, 1, "Dup2"));
	return(EXIT_SUCCESS);
}

int	parse_open(t_basic *current)
{
	char	*file;

	file = current->data.token->content;
	if (current->data.token->type & R_IN)
	{
		if (access(file, F_OK) == ERROR)
			return (error_msg(PERROR, 1, file));
		else if (access(file, R_OK) == ERROR)
			return (error_msg(PERROR, 1, file));
	}
	if (current->data.token->type & R_OUT)
	{
		if (access(file, F_OK) == FOUND && access(file, W_OK) == ERROR)
			return (error_msg(PERROR, 1, file));
	}
	return (EXIT_SUCCESS);
}

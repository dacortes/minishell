/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:14:27 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/07 11:45:16 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redirections(t_minishell *mini, t_basic *start, t_basic *end)
{
	t_basic *tmp;

	tmp = start;
	while (tmp != end)
	{
		
		tmp = tmp->next;
	}
}

int	reset_redirs(t_minishell *mini)
{
	if (dup2(mini->term_fd[0], mini->redir[0]) == FAILURE)
		return (error_msg(PERROR, 1, "Dup2"));
	if (dup2(mini->term_fd[1], mini->redir[1]) == FAILURE)
		return (error_msg(PERROR, 1, "Dup2"));
	return(EXIT_SUCCESS);
}

//se asume que la token next existe
int	parse_open(t_token *current, int type, int *redir)
{
	char	*file;

	file = current->next->content;
	if (type == R_IN)
	{
		if (access(file, F_OK) == ERROR)
			return (error_msg(PERROR, 1, file));
		if (access(file, R_OK) == ERROR)
			return (error_msg(PERROR, 1, file));
		redir[0] = open(file, O_RDONLY);
		if (redir[0] == ERROR)
			return (error_msg(PERROR, 1, file));
	}
	if (type == R_OUT)
	{
		if (!access(file, F_OK) && access(file, W_OK))
			return (error_msg(PERROR, 1, file));
		redir[1] = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (redir[1] == ERROR)
			return (error_msg(PERROR, 1, file));
	}
	return (EXIT_SUCCESS);
}

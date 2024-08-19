/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:51:44 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/19 18:19:34 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_child_status(t_minishell *mini)
{
	handle_signaled(&mini->status, WTERMSIG(mini->status));
	if (WIFEXITED(mini->status))
		mini->status = WEXITSTATUS(mini->status);
}

int	exec_cmd(t_minishell *mini, t_basic *start, t_basic *end, int is_child)
{
	pid_t	child;

	set_child(TRUE, FALSE);
	expand_token(mini, &start, end);
	if (start->data.token->type == S_SHELL)
		child = _subshell(mini, start, end);
	else if (is_builtin(start, end))
		child = _builtin(mini, start, end, is_child);
	else
	{
		if (is_child == NO_CHILD)
			child = _execute_no_child(mini, start, end);
		else
			_execute(mini, start, end);
	}
	if (set_child(FALSE, TRUE) && is_child == NO_CHILD)
	{
		reset_redirs(mini);
		waitpid(child, &mini->status, 0);
		while (wait(NULL) != -1)
			;
	}
	get_child_status(mini);
	reset_redirs(mini);
	return (EXIT_SUCCESS);
}

int	do_pipe(t_minishell *mini, t_basic *start, t_basic *end)
{
	pid_t	child;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == ERROR)
		exit(error_msg(PERROR, 1, "do_pipe: pipe"));
	child = fork();
	if (child == ERROR)
		exit(error_msg(PERROR, 1, "do_pipe: child"));
	else if (child == CHILD)
	{
		signal(SIGINT, exit);
		signal(SIGQUIT, exit);
		if (dup2(pipe_fd[1], 1) == ERROR)
			exit(error_msg(PERROR, 1, "do_pipe: dup2"));
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exec_cmd(mini, start, end, CHILD);
		exit(mini->status);
	}
	if (dup2(pipe_fd[0], 0) == ERROR)
		exit(error_msg(PERROR, 1, "do_pipe: dup2"));
	mini->redir[0] = pipe_fd[0];
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (EXIT_SUCCESS);
}

void	manager(t_minishell *mini)
{
	t_basic	*end;
	t_basic	*start;
	int		skip;

	skip = 0;
	end = mini->token;
	start = mini->token;
	while (end)
	{
		if (end->data.token->type == PIPE && !skip)
		{
			do_pipe(mini, start, end);
			start = end->next;
		}
		else if (end->data.token->type & L_OPERAND)
		{
			if (!skip)
				exec_cmd(mini, start, end, NO_CHILD);
			set_skip(mini, end, &skip);
			start = end->next;
		}
		end = end->next;
	}
	if (!skip)
		exec_cmd(mini, start, end, NO_CHILD);
}

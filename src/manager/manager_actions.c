/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:17:03 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/20 15:54:12 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	_subshell(t_minishell *mini, t_basic *start, t_basic *end)
{
	pid_t	child;

	if (redirections(mini, start, end))
		return (EXIT_FAILURE);
	child = fork();
	if (child == ERROR)
		return (error_msg(PERROR, 1, "fork"));
	if (child == CHILD)
	{
		signal(SIGINT, exit);
		signal(SIGQUIT, exit);
		start->data.token->token_content.subs->term_fd[0] = dup(0);
		start->data.token->token_content.subs->term_fd[1] = dup(1);
		manager(start->data.token->token_content.subs);
		exit(start->data.token->token_content.subs->status);
	}
	set_child(TRUE, TRUE);
	return (child);
}

pid_t	_builtin(t_minishell *mini, t_basic *start, t_basic *end, int is_child)
{
	pid_t	child;
	char	**cmd;
	t_basic	*tmp;

	child = 1;
	tmp = union_token(start, end);
	cmd = get_cmds(tmp, end);
	free_list(tmp, free_token);
	if (is_child == NO_CHILD && mini->redir[0])
	{
		child = _child_builtin(mini, start, end, cmd);
		if (child)
			return (free_double_ptr(cmd), child);
	}
	else
	{
		if (redirections(mini, start, end))
			return (free_double_ptr(cmd), ERROR);
		do_builtin(mini, cmd);
	}
	free_double_ptr(cmd);
	return (child);
}

void	_execute(t_minishell *mini, t_basic *start, t_basic *end)
{
	char	**cmd;
	char	**env;
	char	*path;
	t_basic	*tmp;

	tmp = union_token(start, end);
	cmd = get_cmds(tmp, end);
	free_list(tmp, free_token);
	if (redirections(mini, start, end))
		exit (EXIT_FAILURE);
	path = get_path(mini, cmd[0]);
	env = substract_env(mini);
	execve(path, cmd, env);
	exit(error_msg(PERROR, 1, cmd[0]));
}

pid_t	_child_builtin(
			t_minishell *mini, t_basic *start, t_basic *end, char **cmd)
{
	pid_t	child;

	child = fork();
	if (child == ERROR)
		return (error_msg(PERROR, 1, "fork"));
	if (child == CHILD)
	{
		signal(SIGINT, exit);
		signal(SIGQUIT, exit);
		if (redirections(mini, start, end))
			exit (EXIT_FAILURE);
		do_builtin(mini, cmd);
		exit(mini->status);
	}
	set_child(TRUE, TRUE);
	return (child);
}

pid_t	_execute_no_child(
			t_minishell *mini, t_basic *start, t_basic *end)
{
	pid_t	child;

	child = fork();
	if (child == ERROR)
		return (error_msg(PERROR, 1, "fork"));
	if (child == CHILD)
	{
		signal(SIGINT, exit);
		signal(SIGQUIT, exit);
		_execute(mini, start, end);
	}
	set_child(TRUE, TRUE);
	return (child);
}

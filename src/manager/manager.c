/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:51:44 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/17 17:09:49 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int exec_cmd(t_minishell *mini, t_basic *start, t_basic *end, int is_child)
{
	pid_t	child;
	//t_basic	*token_union;
	int		child_created;
	char	**cmd;
	char	**env;
	char	*path;

	child_created = 0;
	env = NULL;
	path = NULL;
	expand_token(mini, &start, end);
	t_basic *tmp = union_token(start, end);
	cmd = get_cmds(tmp, end);
	//printf_token(tmp);
	free_list(tmp, free_token);
	//token_union = expand_wild_cards(NULL);
	if (start->data.token->type == S_SHELL)
	{
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
			exit(mini->status);
		}
		child_created = 1;
	}
	else if ((cmd && is_builtin(cmd[0])) || !cmd)
	{
		if (is_child == NO_CHILD && mini->redir[0])
		{
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
			child_created = 1;
		}
		else
		{
			if (redirections(mini, start, end))
				return (ERROR);
			do_builtin(mini, cmd);
		}
	}
	else
	{
		if (is_child == NO_CHILD)
		{
			child = fork();
			if (child == ERROR)
				return (error_msg(PERROR, 1, "fork"));
			if (child == CHILD)
			{
				signal(SIGINT, exit);
				signal(SIGQUIT, exit);
				if (redirections(mini, start, end))
					exit (EXIT_FAILURE);
				path = get_path(mini, cmd[0]);
				env = substract_env(mini);
				execve(path, cmd, env);
				exit(error_msg(PERROR, 1, cmd[0]));
			}
			child_created = 1;
		}
		else
		{
			if (redirections(mini, start, end))
				exit (EXIT_FAILURE);
			path = get_path(mini, cmd[0]);
			env = substract_env(mini);
			execve(path, cmd, env);
			exit(error_msg(PERROR, 1, cmd[0]));
		}

	}
	if (child_created && is_child == NO_CHILD)
	{
		reset_redirs(mini);
		waitpid(child, &mini->status, 0);
		while (wait(NULL) != -1)
			;
		mini->status = WEXITSTATUS(mini->status); 
	}
	free_double_ptr(env);
	free_double_ptr(cmd);
	if (path)
		ft_free(&path, NULL);	
	return(EXIT_SUCCESS);
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
	if(dup2(pipe_fd[0], 0) == ERROR)
		exit(error_msg(PERROR, 1, "do_pipe: dup2"));
	mini->redir[0] = pipe_fd[0];
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (EXIT_SUCCESS);
}

int	manager(t_minishell *mini)
{
	t_basic	*end;
	t_basic	*start;
	int		skip;

	skip = 0;
	end = mini->token;
	start = mini->token;
	while (end)
	{
	//	signal(SIGINT, SIG_IGN);
	//	signal(SIGQUIT, SIG_IGN);
		if 	(end->data.token->type == PIPE && !skip)
		{
			do_pipe(mini, start, end);
			start = end->next;
		}
		else if (end->data.token->type & L_OPERAND)
		{
			if (!skip)
			{
				exec_cmd(mini, start, end, NO_CHILD);
				reset_redirs(mini);
			}
			if ((end->data.token->type == AND && !mini->status)
				|| (end->data.token->type == OR && mini->status))
			{
				skip = 0;
				get_status(TRUE, mini->status);
				mini->status = 0;
			}
			else 
				skip = 1;
			start = end->next;
		}
		end = end->next;
	}
	if (!skip)
		exec_cmd(mini, start, end, NO_CHILD);
	reset_redirs(mini);
	return (mini->status);
}

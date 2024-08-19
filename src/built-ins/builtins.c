/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:04:09 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/19 19:19:06 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(t_basic *start, t_basic *end)
{
	static char	*builtins[8] = {"echo", "cd", "pwd", "export", "unset", "env", \
								"exit"};
	int			i;
	t_basic		*tmp;
	char		**cmd;

	i = 0;
	tmp = union_token(start, end);
	cmd = get_cmds(tmp, end);
	free_list(tmp, free_token);
	if (!cmd)
		return (free_double_ptr(cmd), TRUE);
	while (builtins[i])
	{
		if (!ft_strncmp(builtins[i], cmd[0], -1))
			return (free_double_ptr(cmd), TRUE);
		i++;
	}
	free_double_ptr(cmd);
	return (FALSE);
}

int	do_builtin(t_minishell *mini, char **cmd)
{
	int	num_arg;

	if (!cmd || !*cmd)
		return (EXIT_SUCCESS);
	num_arg = ft_double_ptr_len((void **)cmd);
	if (ft_strncmp("cd", cmd[0], -1) == EXIT_SUCCESS)
		mini->status = _cd(mini, cmd, num_arg);
	else if (ft_strncmp("echo", cmd[0], -1) == EXIT_SUCCESS)
		mini->status = _echo(cmd, num_arg);
	else if (ft_strncmp("env", cmd[0], -1) == EXIT_SUCCESS)
		mini->status = _env(mini->env, num_arg);
	else if (ft_strncmp("exit", cmd[0], -1) == EXIT_SUCCESS)
		mini->status = _exit_(mini, cmd, num_arg);
	else if (ft_strncmp("export", cmd[0], -1) == EXIT_SUCCESS)
	{
		if (num_arg > 1)
			mini->status = export_loop(&mini->env, cmd);
		else
			mini->status = _export(mini->env);
	}
	else if (ft_strncmp("unset", cmd[0], -1) == EXIT_SUCCESS)
		mini->status = unset_loop(&mini->env, cmd, num_arg);
	else if (ft_strncmp("pwd", cmd[0], -1) == EXIT_SUCCESS)
		mini->status = _pwd();
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/13 18:05:10 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	basic_checker(t_basic **token, char *line, int end)
{
	int i = 0;
	int	status = 0;

	*token = NULL;
	if (!end || !line[0])
		return (EXIT_SUCCESS);
	while (i <= end && line[i])
	{
		while(line[i] == ' ')
			i++;
		if (line[i] == DOUBLE_QUOTES)
		{
			status = metacharacters(token, line, "\"zz", &i);
			if (status)
				return (status);
		}
		else if (line[i] == SIMP_QUOTES)
		{
			status = metacharacters(token, line, "\'zz", &i);
			if (status)
				return (status);
		}
		else if (line[i] == '&' || line[i] == '|')
		{
			status =  metacharacters(token, line, " &|", &i);
			if (status)
				return (status);
		}
		else if (line[i] == '<' || line[i] == '>')
		{
			status =  metacharacters(token, line, " <>", &i);
			if (status)
				return (status);
		}
		else if (line[i] == '(')
		{
			status = check_subshell(token, line, &i, end);
			if (status)
				return (status);
		}
		else if (line[i] == ')')
            return(error_msg(SYNTAX, 2, ")"));
		else if (line[i])
			status = not_metacharacters(token, line, " zz", &i);
	}
	return (EXIT_SUCCESS);
}


t_basic	*coppy_env(t_basic *src_env)
{
	t_basic	*res;
	t_basic	*new;
	t_basic	*iter;
	t_env	*env;

	iter = src_env;
	res = NULL;
	while (iter)
	{
		env = iter->data.env;
		new = protected(ft_calloc(sizeof(t_basic), 1), "coppy: new");
		new->data.env = protected(ft_calloc(sizeof(t_env), 1), "coppy: new");
		new->data.env->key = protected(ft_strdup(env->key), "coppy: key");
		new->data.env->value = protected(ft_strdup(env->value), "coppy: value");
		new->data.env->eql = env->eql;
		add_back(&res, new);
		iter = iter->next;
	}
	add_prev(&res);
	return (res);
}


int	get_subshell(t_minishell *subs)
{
	t_basic	*iter;
	t_token			*token;

	iter = subs->token;
	while (iter)
	{
		token = iter->data.token;
		if (token->type == S_SHELL)
		{
			token->token_content.subs->get_line = ft_strdup(token->content);
			if (!token->token_content.subs->get_line)
				exit (error_msg(MALLOC, 1, "get_subshell: get_line"));
			token->token_content.subs->status = parsing(token->token_content.subs);
			if (token->token_content.subs->status)
				return (token->token_content.subs->status);
			if (subs->env)
				token->token_content.subs->env = coppy_env(subs->env);
		}
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int parsing(t_minishell *mini)
{
	char	*line;
	int		len;
	int		status;

	line = mini->get_line;
	if (!line)
		exit (EXIT_SUCCESS);
	len = ft_strlen(line);
 	status = get_status(FALSE, 1);
	ft_printf("satus patata %d\n", status);
	mini->status = basic_checker(&mini->token, line, len);
	if (mini->status)
		return (mini->status);
	if (mini->token)
		add_prev(&mini->token);
	mini->status = syntax_error(&mini->token);
	if (mini->status)
		return (mini->status);
	mini->status = get_subshell(mini);
	if (mini->status)
	 	return (mini->status);
	if (status && !mini->status)
		mini->status = status;
	return (EXIT_SUCCESS);
}

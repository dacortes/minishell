/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:41:31 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/08 12:41:37 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*free_double_ptr(char **ptr)
{
	int	i;

	i = -1;
	if (!ptr)
		return (NULL);
	while (ptr[++i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
	}
	free(ptr);
	return (NULL);
}

void free_env(void *content)
{
    t_env *env;

	env = ((t_data_type *)content)->env;
    if (env)
	{
		ft_free(&env->key, &env->value);
        free(env);
    }
	env = NULL;
}

void free_minishell(t_minishell *mini, int flag)
{
	ft_free(&mini->get_line, &mini->user);
	ft_free(&mini->cur_dir, &mini->old_dir);
	if (mini->env)
		free_list(mini->env, free_env);
	if (mini->token)
		free_list(mini->token, free_token);
	if (flag)
	{
		free(mini);
		mini = NULL;
	}
}

void free_token(void *content)
{
	t_basic	*basic;
	t_token			*token;

	basic = ((t_basic *)content);
	if (basic)
	{
		token = basic->data.token;
		if (token && token->content)
			free(token->content);
		if (token && token->type == S_SHELL)
			free_minishell(token->token_content.subs, TRUE);
		else if (token && token->type & WILD_CARD)
			free_list(token->token_content.expand, free_token);
		free(token);
	}
	token = NULL;
	basic = NULL;
}

void free_list(t_basic *node, void (*f)(void *))
{
    t_basic *iter;
    t_basic *tmp;

    iter = node;
    while (iter)
	{
        tmp = iter->next;
        f(&(iter->data));
        free(iter);
        iter = tmp;
    }
	iter = NULL;
}

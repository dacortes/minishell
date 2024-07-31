/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:41:31 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/31 20:15:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**free_double_ptr(char **ptr)
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
	return (NULL);
}

void free_env(void *content)
{
    t_env *env;

	env = ((t_type_list *)content)->env;
    if (env)
	{
        free(env->key);
        free(env->value);
        free(env);
    }
}

void free_minishell(t_minishell *mini)
{
	free(mini->get_line);
	free_list(mini->env, free_env);
	free_list(mini->token, free_token);
	free(mini);
}

void free_token(void *content)
{
	t_basic_list	*basic;
	t_token			*token;

	basic = ((t_basic_list *)content);
	if (basic)
	{
		token = basic->list_content.token;
		free(token->content);
		if (token->type == S_SHELL)
			free_minishell(token->token_content.subs);
		else if (token->type & EXPAN)
			free_list(token->token_content.expand, free_token);
	}
}

void free_list(t_basic_list *node, void (*f)(void *))
{
    t_basic_list *iter;
    t_basic_list *tmp;

    iter = node;
    while (iter)
	{
        tmp = iter->next;
        f(&(iter->list_content));
        free(iter);
        iter = tmp;
    }
}

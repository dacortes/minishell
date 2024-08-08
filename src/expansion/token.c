/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:57:10 by codespace         #+#    #+#             */
/*   Updated: 2024/08/08 15:58:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_basic	*connect_lists(t_minishell *mini, t_basic *node, t_basic *new)
{
	t_basic *last;

	if (mini->token == node)
		mini->token = new;
	else
	{
		new->prev = node->prev;
		node->prev->next = new;
		new->data.token->has_space = node->data.token->has_space;
	}
	last = get_last(new);
	last->next = node->next;
	if (last->next)
		node->next->prev = last;
	//free(node->data.token->token_content.expand);
	free(node->data.token->content);
    free(node->data.token);
    free(node);
	return (last);
}

t_basic	*wordspliting(t_minishell *mini, t_basic *node)
{
	char	*line;
	int		end;
	int		i;
	t_basic	*new;

	line = protected(ft_strdup(node->data.token->content), "line");
	line = expansion(mini, line);
	end = ft_strlen(line);
	i = 0;
	new = NULL;
	while (i <= end && line[i])
	{
		while (line[i] == ' ')
			i++;
		mini->status = not_metacharacters(&new, line, " zz", &i);
	}
	free(line);
	return (connect_lists(mini, node, new));
	
}

int	expand_token(t_minishell *mini, t_basic *start, t_basic *end)
{
	t_token	*token;

	while (start != end)
	{
		token = start->data.token;
		if (token->type == EXPAN && token->is_quote == DOUBLE_QUOTES)
			token->content = expansion(mini, token->content);
		else if (token->type == EXPAN && token->is_quote == FALSE)
		{
			ft_printf("soy una patata\n");
			start = wordspliting(mini, start);
		}
		start = start->next;
	}
	return (0);
}

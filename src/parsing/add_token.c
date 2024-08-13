/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:28:08 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/13 10:36:09 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_token_content(t_content *token_content, char *content, int type)
{
	if (type == S_SHELL)
	{
		token_content->subs = ft_calloc(sizeof(t_minishell), 1);
		if (!token_content->subs)
			exit (error_msg(MALLOC, 1, "get_token_content: subs"));
		token_content->subs->get_line = content;
		if (!token_content->subs->get_line)
			exit (error_msg(MALLOC, 1, "get_token_content: get_line"));
	}
	else if (type == R_HER)
		ft_bzero(token_content->redir_here, sizeof(int));
	/*else if (type & WILD_CARD)
	{
		token_content->expand = ft_calloc(sizeof(t_basic), 1);
		if (!token_content->expand)
			exit (error_msg(MALLOC, 1, "get_token_content: expand"));
	}*/
	return (EXIT_SUCCESS);
}

t_token	*new_token(char *content, char *del, int space)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (error_msg(MALLOC, 1, "new_token: new"));
	if (*del == SIMP_QUOTES)
		new->is_quote = SIMP_QUOTES;
	if (*del == DOUBLE_QUOTES)
		new->is_quote = DOUBLE_QUOTES;
	new->type = get_type(del, content);
	new->content = NULL;
	if (new->type != S_SHELL)
		new->content = content;
	get_token_content(&new->token_content, content, new->type);
	if (ft_strchrpos(content, '*') != NOT_FOUND && *del != SIMP_QUOTES
		&& *del != DOUBLE_QUOTES && *del != ')')
		new->type = WILD_CARD;
	if (ft_strchrpos(content, '$') != NOT_FOUND 
		&& del[0] != SIMP_QUOTES && del[0] != ')')
		new->type = EXPAN;
	new->has_space = space;
	return (new);
}

int	init_token(t_basic **token, char *content, char *del, int space)
{
	t_basic	*new;
	t_token	*tmp;

	if (!content)
		exit (error_msg(MALLOC, 1, "init_token: content"));
	new = ft_calloc(sizeof(t_basic), 1);
	if (!new)
		exit (error_msg(MALLOC, 1, "init_token: new"));
	tmp = new_token(content, del, space);
	new->data.token = tmp;
	new->next = NULL;
	add_back(token, new);
	if (tmp->type == ARG &&  ft_strlen(content) == 1 && *content == '&')
		return(error_msg(SYNTAX, 2, "&"));
	return (EXIT_SUCCESS);
}

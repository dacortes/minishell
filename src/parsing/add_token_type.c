/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:28:08 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/01 10:54:39 by codespace        ###   ########.fr       */
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
		token_content->subs->get_line = ft_strdup(content);
		if (!token_content->subs->get_line)
			exit (error_msg(MALLOC, 1, "get_token_content: get_line"));
	}
	else if (type == R_HER)
		ft_bzero(token_content->redir_here, sizeof(int));
	else if (type & WILD_CARD)
	{
		token_content->expand = ft_calloc(sizeof(t_basic_list), 1);
		if (!token_content->expand)
			exit (error_msg(MALLOC, 1, "get_token_content: expand"));
	}
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

int	init_token(t_basic_list **token, char *content, char *del, int space)
{
	t_basic_list	*new;
	t_token			*tmp;

	if (!content)
		exit (error_msg(MALLOC, 1, "init_token: content"));
	new = ft_calloc(sizeof(t_basic_list), 1);
	if (!new)
		exit (error_msg(MALLOC, 1, "init_token: new"));
	tmp = new_token(content, del, space);
	new->list_content.token = tmp;
	new->next = NULL;
	add_back(token, new);
	if (tmp->type == ARG &&  ft_strlen(content) == 1 && *content == '&')
		return(error_msg(SYNTAX, 2, "&"));
	return (EXIT_SUCCESS);
}

int	metacharacters(t_basic_list **token, char *line, char *del, int *pos)
{
	int		end;
	int		len;
	int		space;
	char	delimiter[1];
	int		status;

	space = 0;
	delimiter[0] = del[0];
	len = ft_strlen(del);
	if (line[*pos] && del[0] != ' ' && len > 1)
		(*pos)++;
	end = ft_strchrpos(&line[*pos], del[0]);
	if (end == ERROR && del[0] != ' ')
		return (error_msg(SYNTAX, 2, delimiter));
	space = set_space(line, pos, del);
	if (end == ERROR)
		end = get_end_token(line, del, pos, len);
	status = init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	if (del[0] != ' ' && line[*pos] == del[0])
		++(*pos);
	if (status)
		return (status);
	return (EXIT_SUCCESS);
}

int	not_metacharacters(t_basic_list **token, char *line, char *del, int *pos)
{
	int	end;
	int	space;

	end = get_end_not_metacharacters(&line[*pos]);
	space = set_space(line, pos, del);
	init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	return (EXIT_SUCCESS);
}

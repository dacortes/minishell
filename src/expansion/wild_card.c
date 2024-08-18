/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:40:33 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/18 13:00:50 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	dir_len(void)
{
	DIR				*dir;
	struct dirent	*file;
	int				len;

	len = 0;
	dir = opendir("./");
	if (!dir)
		exit(error_msg(PERROR, 1, "opendir"));
	file = readdir(dir);
	while (file != NULL)
	{
		len++;
		file = readdir(dir);
	}
	closedir(dir);
	return (len + 1);
}

char	**get_posibilites(void)
{
	char			**posibilities;
	DIR				*dir;
	struct dirent	*file;
	int				i;

	posibilities = protected(ft_calloc(dir_len(), sizeof(char *)), "get_posib");
	dir  = opendir("./");
	file = readdir(dir);
	i = 0;
	if (!file)
		return (error_msg(PERROR, 1, "readdir"), NULL);
	while (file != NULL)
	{
		posibilities[i] = protected(ft_strdup(file->d_name), "strdup");
		file = readdir(dir);
		i++;
	}
	closedir(dir);
	return (posibilities);
}

int search_middle_str(char *target, char *src, int start_t, int start_s)
{
	int	i;

	if (src[start_s] == '*')
		return (start_t);
	while (target[start_t])
	{
		if (target[start_t] == src[start_s])
		{
			i = 0;
			while (target && src && target[start_t + i] == src[start_s + i])
				i++;
			if (!src[start_s + i] || src[start_s = i] == '*')
				return (start_t + i);
		}
		start_t++;
	}
	return (ERROR);
}

int	valid_wildcard(char *src, char	*target)
{
/*	int	start_t;
	int	start_s;

	start_t = 0;
	start_s = 0;
	while (src[start_s])
	{
		if ()
	}*/
	(void)src;
	(void)target;
	return (TRUE);
}

t_basic	*get_expansion(t_basic *token)
{
	t_basic	*expanded;
	t_basic *new;
	char	**posibilities;
	int		i;

	i = 0;
	expanded = NULL;
	posibilities = get_posibilites();
	while (posibilities[i])
	{
		if (valid_wildcard(posibilities[i], token->data.token->content))
		{
			new = coppy_token(token, FALSE);
			new->data.token->content = \
				protected(ft_strdup(posibilities[i]), "ft_strdup");
			add_back(&expanded, new);
		}
		i++;
	}
	free_double_ptr(posibilities);
	return (expanded);
}

t_basic	*expand_wild_cards(t_basic *token)
{
	t_basic *iter;
	t_basic	*new;

	iter = token;
	new = NULL;
	get_expansion(NULL);
	while (iter)
	{
		if (iter->data.token->type == WILD_CARD)
		{
			new = get_expansion(iter);
			if (new == NULL)
				continue ;
			new->prev = iter->prev;
			while(new->next)
				new = new->next;
			new->next = iter->next;
			free(iter);
			iter = new;
		}
		iter = iter->next;
	}
	return (new);
}

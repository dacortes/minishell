/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:40:33 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/18 20:37:05 by frankgar         ###   ########.fr       */
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
	dir = opendir("./");
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

t_basic	*get_expansion(t_basic *token)
{
	t_basic	*expanded;
	char	**posibilities;
	int		i;

	expanded = NULL;
	i = 0;
	(void)token;
	posibilities = get_posibilites();
	while (posibilities[i])
	{
		printf("%s\n", posibilities[i]);
		i++;
	}
	free_double_ptr(posibilities);
	return (expanded);
}

t_basic	*expand_wild_cards(t_basic *token)
{
	t_basic	*iter;
	t_basic	*new;

	iter = token;
	new = NULL;
	get_expansion(NULL);
	while (iter)
	{
		if (iter->data.token->type == WILD_CARD)
		{
			new = get_expansion(iter);
			new->prev = iter->prev;
			while (new->next)
				new = new->next;
			new->next = iter->next;
			free(iter);
			iter = new;
		}
		iter = iter->next;
	}
	return (new);
}

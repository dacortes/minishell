/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:41:31 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/28 16:31:29 by frankgar         ###   ########.fr       */
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

int	clear_env(t_env **env)
{
	t_env	*clear;

	while (*env)
	{
		clear = *env;
		*env = (*env)->next;
		ft_free(&clear->key, &clear->value);
		free(clear);
	}
	return (EXIT_SUCCESS);
}

int	clear_token(t_token **token)
{
	t_token	*clear;

	while (*token)
	{
		clear = *token;
		*token = (*token)->next;
		ft_free(&clear->content, NULL);
		free(clear);
	}
	return (EXIT_SUCCESS);
}

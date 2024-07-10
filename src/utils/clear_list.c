/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:41:31 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/10 16:46:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

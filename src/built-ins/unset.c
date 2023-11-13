/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:04:55 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/13 09:09:38 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	unset(int *size, t_env **env, char *key)
{
	t_env	*rm;
	t_env	*prev;

	rm = *env;
	prev = NULL;
	while (rm)
	{
		if (check_key(key))
			return (msg_error(E_EXP, 1, key));
		if (ft_strncmp(rm->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = rm->next;
			else
				*env = rm->next;
			free(rm->key);
			free(rm->val);
			free(rm);
			(*size)--;
			return (SUCCESS);
		}
		prev = rm;
		rm = rm->next;
	}
	return (TRUE);
}

int	magic_unset(t_mini **sh, t_get **g, int n_cmd)
{
	int	stt;
	int	i;

	i = 0;
	stt = 0;
	if (n_cmd >= 2)
	{
		while ((*g)->arg[i])
			(unset(&(*sh)->size, &(*sh)->env, (*g)->arg[i++])) && (stt = 1);
	}
	return (stt);
}

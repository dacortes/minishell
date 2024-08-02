/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:21:04 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/02 15:32:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_key(char *key)
{
	int	i;

	if (!key)
		return (FALSE);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (FALSE);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && !ft_isalpha(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

//el replace sirve para cambiar el valor
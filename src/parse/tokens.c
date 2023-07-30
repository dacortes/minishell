/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:50:50 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/30 10:54:20 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

/* parse input y despues un parse par los comandos */
/* un token es todo aquell separado por un espacio pipe o algun tipo de redireccion siempre
y cuando estos no se encuentren entre comillas dobles o simples*/
/*ls       "$a| echo -a"$USER-a"'-a$USER' |ls -la .|grep*/
int	token(/*t_token *tk, */char *inp)
{
	int	i = 0;
	int len;
	char	*tk;

	i = ignore_sp(inp);
	while (inp[i] && inp[i] != '|' && !ft_is_space(inp[i]))
		i++;
	tk = ft_calloc(sizeof(char), i + 1);
	if (!tk)
		exit (msg_error(E_MEM, 1, NULL));
	len = i - ignore_sp(inp);
	ft_strlcpy(tk, &inp[ignore_sp(inp)], len + 1);
	free(tk);
	ft_printf(R"%s\n"E, tk);
	return (SUCCESS);
}
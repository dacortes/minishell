/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:21:30 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/16 14:03:41 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//ACEPTABLE DESPUES DE $: -ALPHANUMERICO O '_'
//						  -PRIMERO CARACTER HA DE SER ALPHA O '_'
//						  -CASO A TRATAR "$?"
//						  -EN CASO DE QUE NO SE CUMPLA, EL ARGUMENTO ES "$+content"
int inside_quotes_tokenizer(t_token **token)
{
	t_token	*iter;
	t_token *prev;

	iter = *token;
	while(iter)
	{

		



		if (iter == *token)
			prev = iter;
		prev = prev->next;
		iter = iter->next;
	}

}

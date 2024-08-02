/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:57:10 by codespace         #+#    #+#             */
/*   Updated: 2024/08/02 14:06:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_str_replace(const char *inp, size_t start, size_t end, char *rep)
{
	char	*new;
	size_t	org_len;
	size_t	rep_len;
	size_t	new_len;

	org_len = ft_strlen(inp);
	rep_len = ft_strlen(rep);
	new_len = org_len - (end - start) + rep_len;
	new = ft_calloc(new_len + 1, sizeof(char));
	if (!new)
		exit (error_msg(MALLOC, 1, "ft_str_relpace: new"));
	ft_strncpy(new, inp, start);
	ft_strcpy(&new[start], rep);
	ft_strcpy(&new[start + rep_len], &inp[end]);
	return (new);
}

char *expand_token(t_basic *env, char *content, int start, int end)
{
	char *aux;
	char *key;
	char *value;

	if (content[end] == '?')
		aux = ft_str_replace(content, start, end, "0");
	else
	{
		key = ft_strndup(&content[start], end - start);
		value = ft_strdup(search_env(env, key, VALUE));
		free(key);
		if (value)
		{
			aux = ft_str_replace(content, start - 1, end, value);
			free (value);
		}
		else
			aux = ft_str_replace(content, start, end, "");
	}
	if (!aux)
		exit(error_msg(MALLOC, 1, "expand_token: aux"));
	free(content);
	return (aux);
}

char	*expansion(t_basic *env, char *content)
{
	int	end;
	int	start;

	end = 0;
	start = -1;
	while (content[++start])
	{
		if (content[start] == '$')
		{
			++start;
			if ((ft_isalpha(content[start]) || content[start] == '_'))
			{
				end = start;
				while (content[end] && (ft_isalnum(content[end]) || content[end] == '_'))
					++end;
				content = expand_token(env, content, start, end);
			}
			else if (content[start] && content[start] == '?')
			{	
				end = start;
				content = expand_token(env, content, start - 1, end + 1);
			}
		}
	}
	return (content);
}
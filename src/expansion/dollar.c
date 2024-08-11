/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:57:10 by codespace         #+#    #+#             */
/*   Updated: 2024/08/08 19:32:00 by codespace        ###   ########.fr       */
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

char *expand_str(t_minishell *mini, char *content, int start, int end)
{
	char	*aux;
	char	*key;
	char	*value;
	char	*status;

	status = protected(ft_itoa(mini->status), "expand: status");
	if (content[end] == '?')
		aux = ft_str_replace(content, start -1, end + 1, status);
	else
	{
		key = protected(ft_strndup(&content[start], end - start), "key");
		value = protected(ft_strdup(search_env(mini->env, key, VALUE)), "val");
		free(key);
		if (value && *value)
		{
			aux = ft_str_replace(content, start - 1, end, value);
			free (value);
		}
		else
		{
			aux = ft_str_replace(content, start - 1, end, "");
			free (value);
		}
	}
	protected(aux, "expand_token: aux");
	return (ft_free(&content, &status), aux);
}

char	*expansion(t_minishell *mini, char *content)
{
	int	end;
	int	start;

	end = 0;
	start = 0;
	while (content[start])
	{
		if (content[start] == '$')
		{
			++start;
			if ((ft_isalpha(content[start]) || content[start] == '_'))
			{
				end = start;
				while (content[end] && (ft_isalnum(content[end]) || content[end] == '_'))
					++end;
				content = expand_str(mini, content, start, end);
			}
			else if (content[start] && content[start] == '?')
			{	
				end = start;
				content = expand_str(mini, content, start, end);
			}
		}
		else
			++start;
		if ((int)ft_strlen(content) < start)
			break ;
	}
	return (content);
}
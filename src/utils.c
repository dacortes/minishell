/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:25:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/26 16:27:47 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

char	*search_env(t_env *env, char *key, int type)
{
	t_env	*search;

	search = env;
	if (type == KEY)
	{
		while (search)
		{
			if (ft_strncmp(search->key, key, -1) == 0)
				return (search->key);
			search = search->next;
		}
	}
	else if (type == VAL)
	{
		while (search)
		{
			if (ft_strncmp(search->key, key, -1) == 0)
				return (search->val);
			search = search->next;
		}
	}
	return (NOT);
}

char	*ft_strdup_exit(const char *s1)
{
	char	*cp;

	cp = (char *)malloc(ft_strlen(s1) + 1);
	if (!cp)
		exit (msg_error(E_MEM, E_EXIT, NULL));
	ft_memcpy(cp, s1, ft_strlen(s1) + 1);
	return (cp);
}

char	*ft_strrep(const char *inp, size_t start, size_t end, char *rep)
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
		exit (msg_error(E_MEM, E_EXIT, NULL));
	ft_strncpy(new, inp, start);
	ft_strcpy(&new[start], rep);
	ft_strcpy(&new[start + rep_len], &inp[end]);
	return (new);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(src);
	if (n < len)
		len = n;
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		exit (msg_error(E_MEM, E_EXIT, NULL));
	if (dst)
		ft_memcpy(dst, src, len);
	return (dst);
}

char	*ft_strjoin_max(char **need)
{
	char	*join;
	int		iter;
	int		len;

	if (!need || !*need)
		return (NULL);
	iter = 0;
	len = 0;
	while (need[iter])
		len += ft_strlen(need[iter++]);
	join = ft_calloc(len + 1, sizeof(char));
	if (!join)
		exit (msg_error(E_MEM, E_EXIT, NULL));
	iter = 0;
	while (need[iter])
	{
		ft_strlcat(join, need[iter], len + ft_strlen(need[iter]) + 1);
		iter++;
	}
	return (join);
}

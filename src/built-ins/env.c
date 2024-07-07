/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:49:47 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/07 11:58:55 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

static t_env	*init_basic_env(void)
{
	t_env	*result;
	t_env	*new;

	result = NULL;
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit(-1);
	new->key = ft_strdup("PWD");
	new->value = ft_strdup("funcion que verifique el path actual");
	new->eql = TRUE;
	add_back((void **)&result, new, sizeof(t_env));
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit(-1);//code status
	new->key = ft_strdup("SHLVL");
	new->value = ft_strdup("1");
	new->eql = TRUE;
	add_back((void **)&result, new, sizeof(t_env));
	return (result);
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

t_env	*init_env(char **env)
{
	t_env	*result;
	t_env	*new;
	int		pos;
	int		i;

	if (!env)
		return (init_basic_env());
	i = -1;
	result = NULL;
	while (env[++i])
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			exit (-1);
		int tmp = 0;
		pos = ft_strchrpos(env[i], '=');
		if (pos ==  -1)
		{
			new->key = ft_cutdel(env[i], 0, '\0', &tmp); //PROTEGER
			new->value = ft_cutdel(env[i], ft_strchrpos(env[i], '='), '\0', &tmp);
			new->eql = FALSE;
		}
		else
		{
			new->key = ft_cutdel(env[i], 0, '=', &tmp); //PROTEGER ESTO TMB
			new->value = ft_cutdel(env[i], ft_strchrpos(env[i], '=') + 1, '\0', &tmp); //NO SE TE OLVIDE PROTEGER ESTA
			new->eql = TRUE;
		}
		add_back((void **)&result, new, sizeof(t_env));
	}
	return (result);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:07:51 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/19 21:06:40 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		exit (error_msg(MALLOC, 1, "ft_strjoin_max: join"));
	iter = 0;
	while (need[iter])
	{
		ft_strlcat(join, need[iter], len + ft_strlen(need[iter]) + 1);
		iter++;
	}
	return (join);
}

char	*get_dir_branch(void)
{
	char	*dir;
	int		dif;

	dir = get_pwd();
	while (dir && *dir)
	{
		dif = ft_strrchr(dir, '/') - dir;
		ft_memmove(&dir[ft_strlen(dir)], "/.git/HEAD", ft_strlen(dir) + 1);
		if (!access(dir, F_OK | R_OK))
			break ;
		ft_memmove(&dir[dif], "/.git/HEAD", ft_strlen(&dir[dif]) + 1);
		if (!ft_strncmp(dir, "/.git/HEAD", -1))
			break ;
		ft_memmove(&dir[dif], "\0", ft_strlen(&dir[dif]));
	}
	return (dir);
}

char	*get_branch(void)
{
	char	*branch;
	char	*dir;
	int		fd;

	dir = get_dir_branch();
	if (!*dir)
		return (ft_strdup("UWU"));
	fd = open(dir, O_RDONLY);
	if (fd == ERROR)
		return (free(dir), ft_strdup("-\\/UWU\\/-"));
	branch = "UWU";
	while (branch)
	{
		branch = get_next_line(fd);
		if (branch && !ft_strncmp(branch, "ref: refs/heads/", 16))
			break ;
		free(branch);
	}
	if (!branch)
		return (free(dir), close(fd), ft_strdup("UWU"));
	branch[ft_strlen(branch) - 1] = '\0';
	ft_memmove(branch, &branch[16], ft_strlen(&branch[16]) + 1);
	return (free(dir), close(fd), branch);
}

int	prompt(t_minishell *mini)
{
	char	*need[9];
	char	*join;

	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
	need[0] = "["TUR;
	need[1] = mini->user;
	need[2] = END"]";
	need[3] = TUR" 🗂 "CYAN;
	if (mini->cur_dir && !mini->cur_dir[1])
		need[4] = ft_strrchr(mini->cur_dir, '/');
	else
		need[4] = &ft_strrchr(mini->cur_dir, '/')[1];
	need[5] = BLUE" git:("TUR;
	need[6] = get_branch();
	if (!need[6])
		exit(error_msg(MALLOC, 1, "prompt: need[6]"));
	need[7] = END""BLUE")"CYAN"ᐅ "END;
	need[8] = NULL;
	join = ft_strjoin_max(need);
	mini->get_line = readline(join);
	ft_free(&need[6], &join);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (EXIT_SUCCESS);
}

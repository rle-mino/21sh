/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 12:06:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/04 18:21:59 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"
#include "minishell.h"

t_line					*to_line(char *cmd)
{
	int		i;
	t_line	*old_line;
	t_line	*tmp;

	i = -1;
	old_line = ft_memalloc(sizeof(t_line));
	old_line->next = ft_memalloc(sizeof(t_line));
	old_line->next->prev = old_line;
	old_line = old_line->next;
	old_line->c = cmd[++i];
	tmp = old_line;
	while (cmd[++i] && i < 300)
	{
		tmp->next = ft_memalloc(sizeof(t_line));
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->c = cmd[i];
	}
	return (old_line);
}

void					*clear_hist(t_hist *hist)
{
	t_hist	*tmp;
	t_line	*tmp2;

	while (hist->prev)
		hist = hist->prev;
	while (hist)
	{
		while (hist->old_line->prev)
			hist->old_line = hist->old_line->prev;
		while (hist->old_line)
		{
			tmp2 = hist->old_line;
			hist->old_line = hist->old_line->next;
			free(tmp2);
		}
		tmp = hist;
		hist = hist->next;
		free(tmp);
	}
	return (NULL);
}

t_hist					*add_hist(t_line *cmd, t_hist *next, t_hist *prev)
{
	t_hist		*new;

	new = ft_memalloc(sizeof(t_hist));
	new->old_line = cmd;
	new->next = next;
	new->prev = prev;
	return (new);
}

t_hist					*read_history(t_env *env)
{
	t_hist		*history;
	t_hist		*tmp_hist;
	char		*tmp;
	t_data		*data;
	int			fd;

	history = ft_memalloc(sizeof(t_hist));
	tmp_hist = history;
	if (!(data = get_anything(env, "HOME")))
		tmp = "";
	else
		tmp = ft_strjoin(data->content, "/.history");
	if ((fd = open(tmp, O_RDONLY)) == -1)
	{
		ft_putstr_fd("history unavailable\n", 2);
		return (history);
	}
	while (get_next_line(fd, &tmp) == 1)
	{
		tmp_hist->prev = add_hist(to_line(tmp), tmp_hist, NULL);
		tmp_hist = tmp_hist->prev;
	}
	close(fd);
	return (history);
}

void					write_history(t_hist *hist, t_env *env)
{
	int		fd;
	char	*tmp;
	char	*tmp2;
	t_data	*data;

	if (!(data = get_anything(env, "HOME")))
		tmp = "";
	else
		tmp = ft_strjoin(data->content, "/.history");
	if ((fd = open(tmp, O_WRONLY | O_TRUNC | O_CREAT)) == -1)
		ft_putstr_fd("history unavailable\n", 2);
	while (hist)
	{
		tmp = to_string(get_first(hist->old_line));
		tmp2 = tmp;
		tmp = ft_strjoin(tmp, "\n");
		free(tmp2);
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		hist = hist->prev;
	}
}

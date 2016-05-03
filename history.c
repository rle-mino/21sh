/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 12:06:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/02 19:56:04 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

static t_line			*to_line(char *cmd, t_le *le)
{
	int		i;
	t_line	*old_line;
	t_line	*tmp;

	i = -1;
	le->pos_x = 0;
	old_line = ft_memalloc(sizeof(t_line));
	old_line->next = ft_memalloc(sizeof(t_line));
	old_line->next->prev = old_line;
	old_line = old_line->next;
	old_line->c = cmd[++i];
	tmp = old_line;
	le->pos_x++;
	while (cmd[++i] && i < 300)
	{
		le->pos_x++;
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

	while (hist)
		hist = hist->prev;
	while (hist)
	{
		while (hist->old_line)
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

t_hist					*add_hist(t_line *cmd, t_hist *prev)
{
	t_hist		*new;

	new = ft_memalloc(sizeof(t_hist));
	new->old_line = cmd;
	new->prev = prev;
	return (new);
}

void					select_old_line(int dir, t_hist **history, t_le *le)
{
	char				*cmd;

	if (dir == 2)
	{
		if ((*history)->prev)
			(*history) = (*history)->prev;
		else if (get_next_line(le->fd_hist, &cmd) == 1)
		{
			(*history)->prev = add_hist(to_line(cmd, le), (*history));
			(*history) = (*history)->prev;
			free(cmd);
		}
		le->line = (*history)->old_line;
	}
	else if (dir == 3)
	{
		if ((*history)->next)
		{
			(*history) = (*history)->next;
			le->line = (*history)->old_line;
		}
	}
}

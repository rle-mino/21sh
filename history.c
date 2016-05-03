/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 12:06:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/03 23:17:36 by rle-mino         ###   ########.fr       */
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

static t_hist			*add_hist(t_line *cmd, t_hist *next)
{
	t_hist		*new;

	new = ft_memalloc(sizeof(t_hist));
	new->old_line = cmd;
	new->next = next;
	return (new);
}

void					select_old_line(int dir, t_hist **history, t_le *le)
{
	if (dir == 2)
	{
		if ((*history)->prev)
		{
			(*history) = (*history)->prev;
			le->line = (*history)->old_line;
		}
	}
	else if (dir == 3)
	{
		if ((*history)->next)
		{
			(*history) = (*history)->next;
			le->line = (*history)->old_line;
		}
	}
	add_hist(NULL, NULL);
	to_line(NULL, NULL);
}

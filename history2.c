/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 21:09:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/05 22:15:41 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"
#include "minishell.h"

t_hist		*generate_hist(t_line *cmd, t_hist *next, t_hist *prev)
{
	t_hist		*new;

	new = ft_memalloc(sizeof(t_hist));
	new->old_line = cmd;
	new->next = next;
	new->prev = prev;
	return (new);
}

t_hist		*get_first_hist(t_hist *hist)
{
	t_hist	*a;

	a = hist;
	while (a->next)
		a = a->next;
	return (a);
}

void		create_new_hist(t_hist **history, t_line *line)
{
	if (linelen(line) > 1)
	{
		(*history)->prev = generate_hist(line, *history, (*history)->prev);
		*history = (*history)->prev;
		if ((*history)->prev->prev)
			(*history)->prev->next = *history;
	}
}

int			get_hist_fd(t_env *env)
{
	t_data		*data;
	char		*tmp;
	int			fd;

	if (!(data = get_anything(env, "HOME")))
		tmp = "";
	else
		tmp = ft_strjoin(data->content, "/.history");
	if ((fd = open(tmp, O_RDONLY)) == -1)
		ft_putstr_fd("history unavailable\n", 2);
	return (fd);
}

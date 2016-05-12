/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 02:45:11 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/12 20:32:56 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

/*
***		Gestion complete de l'edition de line
*/

char			*to_string(t_line *line)
{
	char	buffer[2];
	char	*string;
	char	*tmp;

	string = ft_memalloc(1);
	while (line)
	{
		ft_bzero(buffer, sizeof(buffer));
		buffer[0] = line->c;
		tmp = string;
		string = ft_strjoin(string, buffer);
		free(tmp);
		line = line->next;
	}
	return (string);
}

/*
***		Changement interne de l'edition de ligne
*/

void			add_to_line(t_le *le, t_line **line, char n)
{
	t_line	*new;

	new = ft_memalloc(sizeof(t_line));
	new->x = le->pos_x + 1;
	new->y = le->pos_y;
	new->c = n;
	new->next = (*line)->next;
	new->prev = *line;
	if ((*line)->next)
		(*line)->next->prev = new;
	(*line)->next = new;
	*line = (*line)->next;
	add_to_line_display(le, line);
}

void			delete_char(t_le *le, t_line **line, char c)
{
	t_line		*tmp;

	tmp = *line;
	if (!*line || !(*line)->prev || (*line)->is_orig)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp && tmp->next == NULL && c != 127)
		move_cursor(le, LEFT, line);
	if (tmp)
		free(tmp);
	tmp = NULL;
	if (c == 127)
		move_cursor(le, LEFT, line);
	else if (*line && (*line)->next)
		*line = (*line)->next;
	delete_char_display(&((*line)->next), le);
}

/*
***		Fonction principale de l'edition de ligne
***		Retourne le commande finale sous forme de liste chainee
*/

t_line			*edit_line(t_le *le)
{
	char	buffer[6];

	le->pos_x = 4;
	le->line = ft_memalloc(sizeof(t_line));
	le->line->is_orig = 1;
	history(SAVE_LINE, le->line);
	history(FIRST_HIST, NULL);
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer(buffer, le);
		if (buffer[0] == '\n' && buffer[1] == 0)
		{
			move_to_last(le, &(le->line));
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	if ((le->prompt = missing_pair(get_first_line(le->line))))
		edit_line_pairing(le, le->prompt);
	return (get_first_line(le->line));
}

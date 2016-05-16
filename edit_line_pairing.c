/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_pairing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 19:04:52 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/16 23:10:47 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

/*
***		gere l'appairage de certains caracteres recursivement
*/

static void			create_first_line(t_le *le, int bsn)
{
	if (!bsn || !le->line)
		le->line = ft_memalloc(sizeof(t_line));
	else
	{
		le->line->next = ft_memalloc(sizeof(t_line));
		le->line->next->prev = le->line;
		le->line = le->line->next;
	}
	le->line->c = bsn ? '\n' : 0;
	le->line->is_orig = 1;
}

static void			prepare_here_doc(t_line **line)
{
	t_line		*tmp;

	tmp = *line;
	*line = (*line)->prev;
	clear_line(tmp);
	(*line)->next = NULL;
}

void				edit_line_pairing(t_le *le, char *prompt)
{
	char	buffer[6];

	le->pos_x = ft_strlen(prompt);
	ft_putstr_fd(prompt, get_fd(-1));
	create_first_line(le, 1);
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer(buffer, le, PAIRING);
		if (buffer[0] == '\n' && buffer[1] == 0)
		{
			move_to_last(le, &(le->line));
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	if ((le->prompt = missing_pair(get_first_line(le->line), 0)))
		edit_line_pairing(le, le->prompt);
}

char				*edit_line_heredoc(t_le *le, char *end)
{
	char			buffer[6];
	static int		bsn = 0;

	ft_putstr_fd("heredoc> ", get_fd(-1));
	le->pos_x = ft_strlen("heredoc> ");
	create_first_line(le, bsn);
	bsn = !bsn ? 1 : bsn;
	while (42)
	{

		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer(buffer, le, PAIRING);
		if ((buffer[0] == 0) || (buffer[0] == '\n' && buffer[1] == 0))
		{
			move_to_last(le, &(le->line));
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	if (buffer[0] != 0 && ft_strcmp(to_string(get_orig_line(le->line), NORMAL), end))
		edit_line_heredoc(le, end);
	else if (buffer[0] != 0)
	{
		le->line = get_orig_line(le->line);
		prepare_here_doc(&(le->line));
	}
	fpf("buffer[0] = %d\n", buffer[0]);
	return (to_string(get_first_line(le->line), NORMAL));
}

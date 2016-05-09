/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_pairing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 19:04:52 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/09 17:46:15 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

/*
***		gere l'appairage de certains caracteres recursivement
*/

static void			create_first_line(t_le *le)
{
	le->line->next = ft_memalloc(sizeof(t_line));
	le->line->next->prev = le->line;
	le->line = le->line->next;
	le->line->c = '\n';
	le->line->is_orig = 1;
}

t_line				*edit_line_pairing(t_le *le, char *prompt)
{
	char	buffer[6];

	le->pos_x = ft_strlen(prompt);
	ft_putstr_fd(prompt, get_fd(-1));
	create_first_line(le);
	while (42)
	{
		margin(le);
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer_pairing(buffer, le);
		if (buffer[0] == '\n' && buffer[1] == 0)
		{
			le->pos_x = 0;
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	if ((le->prompt = missing_pair(get_first_line(le->line))))
		edit_line_pairing(le, le->prompt);
	return (get_first_line(le->line));
}

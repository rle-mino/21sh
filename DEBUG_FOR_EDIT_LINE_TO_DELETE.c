/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEBUG_FOR_EDIT_LINE_TO_DELETE.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 19:04:30 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/09 19:05:17 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void			show_me_cursor(t_le *le)
{
	tputs(tgetstr("sc", NULL), 1, ft_putint);
	tputs(tgoto(tgetstr("cm", NULL), 1, 1), 1, ft_putint);
	fpf("le->pos_x = %d", le->pos_x);
	tputs(tgetstr("rc", NULL), 1, ft_putint);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:02:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/12 20:28:14 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

t_env		*get_t_env(t_env *env)
{
	static t_env	*ori_env = NULL;

	if (!ori_env)
		ori_env = env;
	return (ori_env);
}

t_line		*get_orig_line(t_line *line)
{
	while (line && line->is_orig == 0)
		line = line->prev;
	return (line->next);
}

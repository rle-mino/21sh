/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:02:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/04 17:02:12 by rle-mino         ###   ########.fr       */
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

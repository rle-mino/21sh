/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 17:35:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/02 12:06:41 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

static int	get_val(char *to_find, char **in)
{
	int		i;

	i = 0;
	while (in[i])
	{
		if (ft_strstr(in[i], to_find))
			break ;
		i++;
	}
	return (i);
}

char		*get_from_env(char **env, char *to_find)
{
	static		char	**ori_env = NULL;
	char				*tmp;

	if (!ori_env)
	{
		ori_env = ft_cpy_tab(env);
		return (*ori_env);
	}
	if (!(tmp = ori_env[get_val(to_find, ori_env)]))
		return (NULL);
	tmp = ft_strchr(tmp, '=');
	return (tmp ? tmp + 1 : NULL);
}

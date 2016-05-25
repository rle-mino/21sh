/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:42:14 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:43:49 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_before_exec(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

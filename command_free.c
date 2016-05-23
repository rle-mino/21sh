/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie  <ishafie @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 22:30:38 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/23 14:26:30 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_first_cmd(char ***str, int i)
{
	int		a;
	int		closing;

	closing = 0;
	if (str && *str && *str + 1 && ft_strcmp((*str)[0] + 1, ">&-") == 0)
		closing = 1;
	if (!str || !*str || !(*str)[1] || (!(*str)[2] && closing != 1))
		return ;
	free((*str)[0]);
	if (closing == 0)
		free((*str)[1]);
	a = 0;
	if (closing == 1)
		i = 1;
	else
		i = 2;
	while ((*str)[i])
	{
		(*str)[a] = (*str)[i];
		a++;
		i++;
	}
	(*str)[a] = NULL;
}

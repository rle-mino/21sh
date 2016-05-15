/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 22:30:38 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/15 17:09:48 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_first_cmd(char ***str, int i)
{
	int		a;
	int		closing;

	if (!str || !*str || !(*str)[1] || !(*str)[2])
		return ;
	closing = 0;
	if (ft_strcmp((*str)[0] + 1, ">&-") == 0)
		closing = 1;
	free((*str)[0]);
	if (closing == 0)
		free((*str)[1]);
	a = 0;
	i = 2 - closing;
	while ((*str)[i])
	{
		(*str)[a] = (*str)[i];
		a++;
		i++;
	}
	(*str)[a] = NULL;
}

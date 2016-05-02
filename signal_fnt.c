/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fnt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 13:38:26 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/03 02:43:43 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		seg_exit(void)
{
	ft_putstr("minishell: segmentation fault  ");
	ft_putendl(g_name_prog);
}

void			safe_exit(int a)
{
	char	c;

	c = 0;
	if (a == SIGINT)
	{
		write(1, "\b \b", 3);
		write(1, "\b \b", 3);
		write(1, &c, 1);
	}
	if (a == SIGSEGV)
		seg_exit();
}

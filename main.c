/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:37:31 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/26 04:55:57 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

int		main(int ac, char **av, char **env)
{
	char	*instruction;

	(void)ac;
	(void)av;
	(void)env;
	env_sw();
	while (42)
	{
		instruction = edit_line();
		fpf("\n%s\n", instruction);
	}
	env_sw();
	return (0);
}

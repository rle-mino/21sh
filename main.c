/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:37:31 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/26 05:21:02 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

int		main(int ac, char **av, char **env)
{
	char				*instruction;
	struct termios		reset;
	t_le				le;

	(void)ac;
	(void)av;
	(void)env;
	if (tcgetattr(0, &reset) == -1)
		message_handling();
	if (init_term() == 0)
		message_handling();
	init_env(&le);
	while (42)
	{
		instruction = edit_line(&le);
		fpf("\n%s\n", instruction);
	}
	reset_term(reset);
	return (0);
}

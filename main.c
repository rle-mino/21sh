/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:37:31 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/01 18:45:56 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

int		main(int ac, char **av, char **env)
{
	char				*instruction;
	struct termios		reset;
	t_le				*le;

	(void)ac;
	(void)av;
	get_from_env(env, 0);
	if (tcgetattr(0, &reset) == -1)
		message_handling();
	if (init_term() == 0)
		message_handling();
	le = ft_memalloc(sizeof(t_le));
	init_env(le);
	while (42)
	{
		instruction = edit_line(le);
		fpf("\n%s\n", instruction);
	}
	reset_term(reset);
	return (0);
}

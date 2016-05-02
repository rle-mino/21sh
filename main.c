/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:37:31 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/02 15:15:21 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"
#include "minishell.h"

int		main(int ac, char **av, char **env)
{
//	char				*instruction;
	struct termios		reset;
	t_le				le;
	t_env				*data_env;

	if (ac && av)
		;
	signal(SIGINT, safe_exit);
	if (tcgetattr(0, &reset) == -1)
		message_handling();
/*	while (42)
	{
		instruction = edit_line(&le);
		fpf("\n%s\n", instruction);
		}*/
	g_name_prog = NULL;
	data_env = create_env(env);
	fill_env(&data_env, env);
	if (init_term(data_env) == 0)
		message_handling();
	init_env(&le, data_env);
	data_env->le = le;
	loop_prompt(data_env);
	free_env(&data_env);
	reset_term(reset);
	return (0);
}

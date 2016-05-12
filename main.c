/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:37:31 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/12 18:29:22 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"
#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	struct termios		reset;
	t_le				le;
	t_env				*data_env;

	if (ac && av)
		;
	if (tcgetattr(0, &reset) == -1)
		message_handling();
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

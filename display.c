/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 17:18:45 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/02 16:55:15 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_putstr_path_color(char *str)
{
	int			i;
	int			save;

	i = 0;
	save = get_name(str);
	while (str[i])
	{
		if (i == save)
			ft_putstr(C_RED);
		write(1, &str[i], 1);
		i++;
	}
	ft_putstr(STOP);
}

int				display_env(t_env *env)
{
	t_data		*tmp;

	if (!env || !(env->data))
		return (0);
	tmp = (env)->data;
	while (tmp)
	{
		ft_putstr(tmp->prefix);
		ft_putstr("=");
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

static void		display_time(void)
{
	time_t		rawtime;
	char		*tim;
	struct tm	*timeinfo;

	ft_putstr(C_CYAN);
	ft_putchar('[');
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	tim = asctime(timeinfo);
	ft_strclr(&tim[16]);
	ft_putstr(&tim[11]);
	ft_putstr("] ");
	ft_putstr(STOP);
}

void			display_prompt(t_env *e)
{
	t_data		*tmp;

	display_time();
	tmp = get_usr(e);
	ft_putstr(C_BLUE);
	if (tmp)
		ft_putstr(tmp->content);
	ft_putstr(C_CYAN);
	ft_putstr(" ➪ ");
	ft_putstr(STOP);
	tmp = get_pwd(e);
	ft_putstr(CL_CYAN);
	if (tmp)
		ft_putstr_path_color(&(tmp->content)[e->end_path]);
	ft_putstr(CYAN);
	ft_putstr("\n❯❯❯ ");
	ft_putstr(STOP);
}

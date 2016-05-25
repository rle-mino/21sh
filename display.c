/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:35:42 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:36:05 by rle-mino         ###   ########.fr       */
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
			ft_putstr_fd(C_RED, get_fd(-1));
		write(get_fd(-1), &str[i], 1);
		i++;
	}
	ft_putstr_fd(STOP, get_fd(-1));
}

int				display_env(t_env *env)
{
	t_data		*tmp;

	if (!env || !(env->data))
		return (0);
	tmp = (env)->data;
	while (tmp)
	{
		ft_putstr_fd(tmp->prefix, env->fd);
		ft_putstr_fd("=", env->fd);
		ft_putendl_fd(tmp->content, env->fd);
		tmp = tmp->next;
	}
	return (1);
}

static void		display_time(void)
{
	time_t		rawtime;
	char		*tim;
	struct tm	*timeinfo;

	ft_putstr_fd(C_CYAN, get_fd(-1));
	ft_putchar_fd('[', get_fd(-1));
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	tim = asctime(timeinfo);
	ft_strclr(&tim[16]);
	ft_putstr_fd(&tim[11], get_fd(-1));
	ft_putstr_fd("] ", get_fd(-1));
	ft_putstr_fd(STOP, get_fd(-1));
}

void			display_prompt(t_env *e)
{
	t_data		*tmp;

	display_time();
	tmp = get_usr(e);
	ft_putstr_fd(C_BLUE, e->fd);
	if (tmp)
		ft_putstr_fd(tmp->content, e->fd);
	ft_putstr_fd(C_CYAN, e->fd);
	ft_putstr_fd(" ➪ ", e->fd);
	ft_putstr_fd(STOP, e->fd);
	tmp = get_pwd(e);
	ft_putstr_fd(CL_CYAN, e->fd);
	if (tmp)
		ft_putstr_path_color(&(tmp->content)[e->end_path]);
	ft_putstr_fd(CYAN, e->fd);
	ft_putstr_fd("\n❯❯❯ ", e->fd);
	ft_putstr_fd(STOP, e->fd);
}

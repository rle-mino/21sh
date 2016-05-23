/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory_action.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie  <ishafie @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 00:27:30 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/23 14:23:58 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*change_to_home(t_env *e, char *str)
{
	t_data	*tmp;
	char	*final;

	tmp = get_anything(e, "HOME");
	if (!tmp)
		return (str);
	if (!str)
		return (tmp->content);
	if (ft_strcmp(str + 1, "rle-mino") == 0)
		return (ft_strdup(tmp->content));
	if (str + 1)
		final = ft_strjoin(tmp->content, str + 1);
	else
		final = ft_strdup(tmp->content);
	return (final);
}

static char		*concat_args(char **args, int i, t_env *e)
{
	int		len;
	char	*str;
	int		id;

	id = i;
	str = NULL;
	len = 0;
	if (args[i] == NULL)
		return (NULL);
	while (args[id])
		len += ft_strlen(args[id++]);
	str = (char*)malloc(sizeof(str) * (len + 1 + id));
	if (!str)
		malloc_handling();
	if (args[i][0] == '~')
		args[i] = change_to_home(e, args[i]);
	ft_strcpy(str, args[i++]);
	while (args[i])
	{
		ft_strcat(str, " ");
		ft_strcat(str, args[i++]);
	}
	return (str);
}

int				cd_physical(t_env *e, char **args, int i)
{
	char	*final;

	final = concat_args(args, i, e);
	if (!final)
		return (go_to_home(e, args));
	if (chdir(final) == -1)
		return (cd_error(final));
	if (ft_strcmp(final, ".") != 0)
		actualise_anything(e, "PWD", final);
	free(final);
	return (0);
}

int				cd_default(t_env *e, char **args, int i)
{
	char	*final;

	final = concat_args(args, i, e);
	if (!final)
		return (go_to_home(e, args));
	if (chdir(final) == -1)
		return (cd_error(final));
	if (ft_strcmp(final, ".") != 0)
		actualise_anything(e, "PWD", final);
	free(final);
	return (0);
}

int				cd_back(t_env *e)
{
	change_back(e);
	return (0);
}

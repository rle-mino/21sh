/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 05:01:44 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/03 03:29:59 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				count_env(char **env)
{
	int		i;

	i = 0;
	if (env && *env)
	{
		while (env[i] != NULL)
		{
			i++;
		}
	}
	return (i);
}

static char		*get_prefix_env(char *env)
{
	char	*prefix;
	int		len;

	len = 0;
	while (env[len] != '=' && env[len] != '\0')
		len++;
	prefix = (char*)malloc(sizeof(char) * (len + 1));
	if (!prefix)
		malloc_handling();
	ft_bzero(prefix, len + 1);
	ft_strncpy(prefix, env, len);
	return (prefix);
}

static char		*get_suffix_env(char *env)
{
	char	*suffix;
	int		len;

	len = ft_strlen(env);
	suffix = (char*)malloc(sizeof(char) * (len + 1));
	if (!suffix)
		malloc_handling();
	ft_bzero(suffix, len + 1);
	len = 0;
	while (env[len] != '=' && env[len] != '\0')
		len++;
	ft_strcpy(suffix, &env[len + 1]);
	return (suffix);
}

int				fill_path(t_env **e, char *path)
{
	int		i;

	i = 0;
	if (!e || !(*e))
		return (0);
	if (!path)
		(*e)->path = NULL;
	if (!path)
		return (0);
	(*e)->path = ft_strsplit(path, ':');
	if (!((*e)->path) || !(*((*e)->path)))
		malloc_handling();
	return (1);
}

int				fill_env(t_env **e, char **env)
{
	int		i;
	char	*prefix;
	char	*suffix;

	i = 0;
	while (env[i] != NULL)
	{
		prefix = get_prefix_env(env[i]);
		suffix = get_suffix_env(env[i++]);
		if (ft_strcmp(prefix, "SHLVL") == 0)
			shlvl(&suffix);
		if (ft_strcmp(prefix, "PATH") == 0)
			fill_path(e, suffix);
		add_back_data(e, suffix, prefix);
		free(prefix);
		free(suffix);
		prefix = NULL;
		suffix = NULL;
	}
	actualise_env_tab(e, env);
	return (0);
}

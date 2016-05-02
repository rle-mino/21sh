/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actualise_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 04:07:36 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/02 21:38:39 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		actualise_env_tab(t_env **e, char **env)
{
	int		i;
	char	**str;
	t_data	*tmp;

	if (!e || !(*e) || !env || !(*env) || !(*e)->data)
		return ;
	i = 0;
	tmp = (*e)->data;
	str = (char**)malloc(sizeof(char*) * (*e)->nb_env);
	if (!str)
		malloc_handling();
	while (tmp)
	{
		str[i] = (char*)malloc(sizeof(char) * (ft_strlen(tmp->content) +
		ft_strlen(tmp->prefix) + 2));
		ft_strcpy(str[i], tmp->prefix);
		ft_strcat(str[i], "=");
		ft_strcat(str[i], tmp->content);
		tmp = tmp->next;
		i++;
	}
	str[i] = NULL;
	(*e)->env = str;
}

void		refill_path(t_env **e)
{
	t_data	*tmp;

	tmp = get_anything(*e, "PATH");
	if (!tmp || !e || !(*e))
		return ;
	if ((*e)->path && (*e)->path[0])
		free_args((*e)->path);
	fill_path(e, tmp->content);
}

int			change_back(t_env *e)
{
	t_data		*tmp;
	t_data		*aux;
	char		*str;

	tmp = get_anything(e, "PWD");
	aux = get_anything(e, "OLDPWD");
	if (!tmp || !aux)
		return (0);
	if (chdir(aux->content) == -1)
		return (cd_error(aux->content));
	str = aux->content;
	aux->content = tmp->content;
	tmp->content = str;
	return (1);
}

void		actualise_anything(t_env *e, char *choice, char *final)
{
	t_data		*tmp;
	t_data		*aux;
	char		*str;
	int			i;

	i = 0;
	tmp = get_anything(e, choice);
	if (ft_strcmp(choice, "PWD") == 0 && tmp)
	{
		aux = get_anything(e, "OLDPWD");
		str = (char*)malloc(sizeof(char) *
		(ft_strlen(tmp->content) + ft_strlen(final) + 2));
		if (!str)
			exit(EXIT_FAILURE);
		i = ft_strlen(str);
		getcwd(str, 1024);
		if (aux)
		{
			free(aux->content);
			aux->content = tmp->content;
		}
		if (tmp)
			tmp->content = str;
	}
}

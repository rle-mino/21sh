/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 16:21:58 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/15 18:54:09 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_only_redir(char *str, int *i, int *end)
{
	while ((str)[*i] && (str)[*i] != '>' && (str)[*i] != '<')
		*i = *i + 1;
	if ((str)[*i] == 0 || (str)[*i + 1] == 0)
		return (0);
	*end = *i + 1;
	if (((str)[*end] == '>' || (str)[*end] == '<'))
	{
		*end = *end + 1;
		if ((str)[*end] == 0)
			return (0);
		if ((str)[*end] == '&')
		{
			*end = *end + 1;
			if ((str)[*end] == '-')
				*end = *end + 1;
		}
	}
	else if ((str)[*end] == '&')
		get_only_redir_helper(str, end);
	while (*i > 0 && !ft_isspace((str)[*i]))
		*i = *i - 1;
	return (1);
}

void		get_redir_out(char *str, int *i, int *end, char **out, int save)
{
//	int		save;
	char	*redir;
	char	*prefix;
	char	*tmp;
	int		len;

	len = 0;
	tmp = NULL;
	prefix = NULL;
//	save = *end; // false, last problem
	*i = *end;
	if (get_only_redir(str, i, end) == 0 || !str[*i])
	{
		if (!*out)
			*out = ft_strsub(str, save, *i);
		return ;
	}
	else
	{
		if (*out)
			prefix = ft_strdup(*out);
		else
			prefix = ft_strsub(str, save, *i - save);
		redir = ft_strsub(str, *i, *end - *i);
		len = *end;
		while ((str)[len] && !ft_isspace((str)[len]))
			len++;
		if ((len - *end) != 0)
		{
			if (*out)
				ft_strdel(out);
			*out = ft_strsub(str, *end, len - *end);
			tmp = *out;
			*out = join_all(prefix, redir, *out);
			*i = *end;
			free(tmp);
			free(redir);
			free(prefix);
			get_redir_out(str, end, i, out, save);
		}
		else
		{
			*end = len;
			get_redir_out(str, i, end, out, save);
		}
	}
}

char		*join_all(char *first, char *second, char *third)
{
	int		len;
	char	*final;

	len = 0;
	if (first)
		len += ft_strlen(first) + 2;
	if (second)
		len += ft_strlen(second) + 2;
	if (third)
		len += ft_strlen(third) + 2;
	final = (char*)malloc(sizeof(char) * (len + 1));
	if (!final)
		malloc_handling();
	ft_bzero(final, len + 1);
	ft_strcpy(final, first);
	ft_strcat(final, " ");
	ft_strcat(final, second);
	ft_strcat(final, " ");
	ft_strcat(final, third);
	return (final);
}

int			choose_redir(t_env *e, char **l, int i, int *nb)
{
	(void)e;
	if (ft_isdigit(l[i - 1][0]))
	{
		while (ft_isdigit(l[i - 1][*nb]))
			*nb = *nb + 1;
		if (l[i - 1][*nb] == '>' && l[i - 1][*nb + 1] == '>'
		&& l[i - 1][*nb + 2] == 0)
			return (0);
		if (l[i - 1][*nb] == '>' && l[i - 1][*nb + 1] == 0)
			return (1);
		if (ft_strcmp(&l[i - 1][*nb], ">&1") == 0)
			return (4);
	}
	else
	{
		if (l[i - 1][0] == '>' && l[i - 1][1] == '>' && l[i - 1][2] == 0)
			return (2);
		if (l[i - 1][0] == '>' && l[i - 1][1] == 0)
			return (3);
	}
	return (-1);
}

int			find_redir_str(char **str, char **redir, char **prefix, char **out)
{
	int		i;
	int		end;
	char	*other_out;
	char	*str_lol;

	i = 0;
	other_out = NULL;
	if (!*str || get_only_redir(*str, &i, &end) == 0)
		return (0);
	*prefix = ft_strsub(*str, 0, i);
	*redir = ft_strsub(*str, i, end - i);
	get_redir_out(*str, &i, &end, out, end);
	str_lol = *str;
	*str = join_all(*prefix, *redir, *out);
	ft_strdel(&str_lol);
	if (*redir)
		free(*redir);
	if (*prefix)
		free(*prefix);
	if (*out)
		free(*out);
	*redir = NULL;
	*prefix = NULL;
	*out = NULL;
	return (1);
}

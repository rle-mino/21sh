/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_conv_noclong.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 17:08:05 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/12 22:59:45 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		string_min(t_struct data, char *str, size_t k)
{
	int		i;
	size_t	j;

	j = str == NULL ? 0 : (int)ft_strlen(str);
	i = 0;
	if (data.prec != -1)
		while (k < j && (data.prec == 0 ? k < j : k < (size_t)data.prec))
			k += pf_putchar(str[i++]);
	while (k < (size_t)data.min)
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	return (k);
}

static int		string_prec(t_struct data, char *str, size_t k)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = str == NULL ? 0 : (int)ft_strlen(str);
	while (k < (data.min - j > 0 ? 0 : data.min - j))
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	if (data.prec != -1)
		while (i < ((size_t)data.prec > j ? j : data.prec))
			k += pf_putchar(str[i++]);
	return (k);
}

static int		string_size(t_struct data, char *str, int k)
{
	int		i;
	int		j;
	int		l;

	j = str == NULL ? 0 : (int)ft_strlen(str);
	i = 0;
	l = data.prec == -1 ? 1 : 0;
	if (data.prec == 0)
		while (k < data.min - j)
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
	else
		while (k < data.min - (data.prec < j ? data.prec : j) - l)
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
	if (j > 0 && data.prec != -1)
		while (i < j && (data.prec == 0 ? i < j : i < data.prec))
			k += pf_putchar(str[i++]);
	return (k);
}

int				string_conv_noclong(t_struct data, char *str)
{
	int		k;
	int		l;

	k = 0;
	l = 0;
	if (str == NULL && data.flag & 2 && data.min > 0)
	{
		l = 1;
		str = ft_memalloc(7);
	}
	if (data.flag & 4 && data.min != 0)
		return (string_min(data, str, k));
	else if (data.min != 0)
		return (string_size(data, str, k));
	else if (data.prec != 0)
		return (string_prec(data, str, k));
	else
		k += pf_putstr(str);
	if (l == 1)
		free(str);
	return (k);
}

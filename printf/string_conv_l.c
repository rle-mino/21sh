/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_conv_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 23:13:50 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/09 15:34:49 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		string_min_l(t_struct data, wchar_t *str, size_t k)
{
	int		i;
	size_t	j;
	size_t	l;

	j = str == NULL ? 0 : (int)ft_strwlen(str);
	i = 0;
	l = (size_t)data.prec;
	if (data.prec != -1)
		while (k < j && (data.prec == 0 ? k < j : k < l) && str[i])
			k += pf_putcharuni(str[i++]);
	while (k < (size_t)data.min)
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	return (k);
}

static int		string_prec_l(t_struct data, wchar_t *str, size_t k)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = str == NULL ? 0 : (int)ft_strwlen(str);
	while (k < (data.min - j > 0 ? 0 : data.min - j))
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	if (data.prec != -1)
		while (i < ((size_t)data.prec > j ? j : data.prec) && str[i])
			k += pf_putcharuni(str[i++]);
	return (k);
}

static int		string_size_l(t_struct data, wchar_t *str, size_t k)
{
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	m;

	j = str == NULL ? 0 : (int)ft_strwlen(str);
	i = 0;
	m = (size_t)data.min;
	l = (size_t)data.prec;
	if (data.prec == 0)
		while (k < data.min - j)
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
	else
		while (k < (size_t)data.min - (l > j ? j : data.prec) && k < m)
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
	if (j > 0 && data.prec != -1)
		while (i < j && (data.prec == 0 ? i < j : i < l) && str[i])
			k += pf_putcharuni(str[i++]);
	return (k);
}

int				string_conv_l(t_struct data, wchar_t *str)
{
	size_t	k;

	k = 0;
	if (data.flag & 4 && data.min != 0)
		return (string_min_l(data, str, k));
	else if (data.min != 0)
		return (string_size_l(data, str, k));
	else if (data.prec != 0)
		return (string_prec_l(data, str, k));
	else
		k += pf_putstruni(str);
	return (k);
}

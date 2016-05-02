/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_fill_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:22:52 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/12 23:16:14 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			endofnum(char *str, int index)
{
	int		k;

	k = 0;
	while (pf_isnum(str[index]))
	{
		index++;
		k++;
	}
	return (k - 1);
}

int			fill_data_prec(char const *str, size_t *i, va_list ap)
{
	int		k;

	k = 0;
	*i += 1;
	if (str[*i] == '*')
		k = va_arg(ap, int);
	else
	{
		k = ft_atoi(str + *i);
	}
	return (k == 0 ? -1 : k);
}

int			fill_data_min(char const *str, size_t *i, va_list ap)
{
	int		k;

	k = 0;
	if (str[*i] == '*')
		k = va_arg(ap, int);
	else
	{
		k = ft_atoi(str + *i);
		*i += endofnum((char *)str, *i);
	}
	return (k);
}

void		fill_data_flag(char c, t_struct *data)
{
	if (c == '#')
		data->flag = data->flag | 1;
	else if (c == '0')
		data->flag = data->flag | 2;
	else if (c == '-')
		data->flag = data->flag | 4;
	else if (c == '+')
		data->flag = data->flag | 8;
	else if (c == ' ')
		data->flag = data->flag | 16;
}

int			fill_data_clong(char c, char d, t_struct *data)
{
	if (c == 'h' && d == 'h')
	{
		data->clong = data->clong | 1;
		return (2);
	}
	else if (c == 'l' && d == 'l')
	{
		data->clong = data->clong | 2;
		return (2);
	}
	else if (c == 'h')
		data->clong = data->clong | 4;
	else if (c == 'l')
		data->clong = data->clong | 8;
	else if (c == 'j')
		data->clong = data->clong | 16;
	else if (c == 'z')
		data->clong = data->clong | 32;
	return (1);
}

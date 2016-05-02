/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_until_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:16:01 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/12 23:14:17 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_fill_struct(char *str, size_t *i, t_struct *data, va_list a)
{
	if (pf_isflag(str[*i]))
		fill_data_flag(str[*i], data);
	else if (pf_isclong(str[*i], str[*i + 1]))
	{
		if (fill_data_clong(str[*i], str[*i + 1], data) == 2)
			*i += 1;
	}
	else if (str[*i] == '.')
		data->prec = data->prec != 0 ? data->prec : fill_data_prec(str, i, a);
	else if (pf_isnum(str[*i]))
		data->min = data->min != 0 ? data->min : fill_data_min(str, i, a);
}

t_struct	init_data(void)
{
	t_struct	data;

	data.flag = 0;
	data.clong = 0;
	data.prec = 0;
	data.min = 0;
	return (data);
}

int			pf_until_conv(size_t *i, va_list ap, char const *str)
{
	t_struct	data;

	*i += 1;
	data = init_data();
	if (str[*i] == '%')
		return (pf_putchar(str[*i++]));
	while (str[*i] && str[*i] != '%' && pf_isconver(str[*i]) == 0)
	{
		if (pf_isflag(str[*i]) == 0 && pf_isclong(str[*i], str[*i + 1]) == 0
			&& pf_isnum(str[*i]) == 0 && str[*i] != '.')
		{
			*i -= 1;
			return (0);
		}
		pf_fill_struct((char *)str, i, &data, ap);
		*i += 1;
	}
	if (data.min < 0)
	{
		data.flag = data.flag | 4;
		data.min = -data.min;
	}
	if (str[*i] == '\0')
		return (0);
	return (pf_print_var(data, str[*i], ap));
}

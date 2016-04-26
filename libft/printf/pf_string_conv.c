/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_string_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 18:25:50 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/12 22:48:44 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		string_conv(t_struct data, va_list ap, int lower)
{
	if (data.clong == 0 && lower == 1)
		return (string_conv_noclong(data, va_arg(ap, char*)));
	else
		return (string_conv_l(data, va_arg(ap, wchar_t*)));
	return (0);
}

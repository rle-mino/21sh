/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_char_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 18:04:43 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/07 22:19:02 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			char_conv(t_struct data, va_list ap, int lower)
{
	if (data.clong == 0 && lower == 1)
		return (char_conv_noclong(data, (char)va_arg(ap, int)));
	return (char_conv_l(data, va_arg(ap, wchar_t)));
}

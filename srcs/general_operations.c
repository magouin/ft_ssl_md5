/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:33:35 by jcamhi            #+#    #+#             */
/*   Updated: 2018/07/08 17:33:37 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void		print_result_32(uint buffer[4])
{
	int		i;
	char	buff[33];

	i = 0;
	while (i < 16)
	{
		buff[i * 2] = ((((char *)buffer)[i] & 0xf0) >> 4) + '0';
		buff[i * 2] > '9' ? buff[i * 2] = buff[i * 2] - '9' - 1 + 'a' : 0;
		buff[i * 2 + 1] = (((char *)buffer)[i] & 0xf) + '0';
		buff[i * 2 + 1] > '9' ?
			buff[i * 2 + 1] = buff[i * 2 + 1] - '9' - 1 + 'a' : 0;
		i++;
	}
	buff[32] = 0x0a;
	write(1, buff, 33);
}

void		print_result_64(unsigned char buffer[32])
{
	int		i;
	char	buff[65];

	i = 0;
	while (i < 32)
	{
		if (i % 4 == 0)
			*(uint *)(buffer + i) = end_conv_32(*(uint *)(buffer + i));
		buff[i * 2] = ((buffer[i] & 0xf0) >> 4) + '0';
		buff[i * 2] > '9' ? buff[i * 2] = buff[i * 2] - '9' - 1 + 'a' : 0;
		buff[i * 2 + 1] = (buffer[i] & 0xf) + '0';
		buff[i * 2 + 1] > '9' ?
			buff[i * 2 + 1] = buff[i * 2 + 1] - '9' - 1 + 'a' : 0;
		i++;
	}
	buff[64] = 0x0a;
	write(1, buff, 65);
}

uint		end_conv_32(uint nbr)
{
	return (uint)((nbr >> 24) | ((nbr & 0xFF0000) >> 8) |
		((nbr & 0xFF00) << 8) | (nbr << 24));
}

uint64_t	end_conv_64(uint64_t nbr)
{
	return ((uint64_t)end_conv_32(nbr & -1) << 32 | end_conv_32(nbr >> 32));
}

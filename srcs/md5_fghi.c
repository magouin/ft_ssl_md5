/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fghi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:42:49 by jcamhi            #+#    #+#             */
/*   Updated: 2018/06/10 18:42:49 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint	f(uint b, uint c, uint d)
{
	return ((b & c) | ((~b) & d));
}

uint	g(uint b, uint c, uint d)
{
	return ((b & d) | (c & (~d)));
}

uint	h(uint b, uint c, uint d)
{
	return (b ^ c ^ d);
}

uint	i(uint b, uint c, uint d)
{
	return (c ^ (b | (~d)));
}

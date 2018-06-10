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

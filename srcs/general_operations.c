#include <ft_ssl.h>

uint32_t rotl(uint32_t n, uint32_t x)
{
	return ((x << n) | (x >> (32 - n))); 
}

uint32_t rotr(uint32_t n, uint32_t x)
{
	return ((x >> n) | (x << (32 - n))); 
}


void	print_result_32(uint buffer[4])
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

void	print_result_64(uint buffer[4])
{
	int		i;
	char	buff[65];

	i = 0;
	while (i < 32)
	{
		buff[i * 2] = ((((char *)buffer)[i] & 0xf0) >> 4) + '0';
		buff[i * 2] > '9' ? buff[i * 2] = buff[i * 2] - '9' - 1 + 'a' : 0;
		buff[i * 2 + 1] = (((char *)buffer)[i] & 0xf) + '0';
		buff[i * 2 + 1] > '9' ?
			buff[i * 2 + 1] = buff[i * 2 + 1] - '9' - 1 + 'a' : 0;
		i++;
	}
	buff[64] = 0x0a;
	write(1, buff, 65);
}


#include <ft_ssl.h>

uint32_t	ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

uint32_t	maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t	gs0(uint32_t x)
{
	return (rotr(2, x) ^ rotr(13, x) ^ rotr(22, x));
}

uint32_t	gs1(uint32_t x)
{
	return (rotr(6, x) ^ rotr(11, x) ^ rotr(25, x));
}

uint32_t	ps0(uint32_t x)
{
	return (rotr(7, x) ^ rotr(18, x) ^ (x >> 3));
}

uint32_t	ps1(uint32_t x)
{
	return (rotr(17, x) ^ rotr(19, x) ^ (x >> 10));
}

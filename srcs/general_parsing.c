#include <ft_ssl.h>

int		padd_buffer(int original_file_size, int r, char *buffer)
{
	size_t	size;

	original_file_size += r;
	size = (r / 64 + 1) * 64;
	if (size - r <= 8)
		size += 64;
	((uint8_t*)buffer)[r] = 0x80;
	ft_bzero(buffer + r + 1, size - r - 8 - 1);
	*(uint64_t*)(buffer + size - 8) = original_file_size << 3;
	return (size);
}
#include <ft_ssl.h>
#include <math.h>
#include <stdio.h>

void	initialize_buffer (uint *buffer)
{
	buffer[0] = 0x67452301u;
	buffer[1] = 0xefcdab89u;
	buffer[2] = 0x98badcfeu;
	buffer[3] = 0x10325476u;
}

void	initialize_t (uint t[65])
{
	uint i;

	i = 1;
	while (i <= 64)
	{
		t[i] = 4294967296.0 * fabs(sin(i));
		i++;
	}
}


void	ft_init(t_params *params)
{
	initialize_buffer(params->buffer);
	initialize_t(params->t);
}

void	hash_buffer(ssize_t r, t_params *params, char *buffer)
{
	int	i;
	static char nbr_du_milieu[4][4] = {{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}};

	i = 0;
	while (i <= r / 64 - 1)
	{
		compute_buffer(params, nbr_du_milieu, buffer + i * 16 * sizeof(uint));
		i++;
	}
}

int	padd_buffer(int original_file_size, int r, char *buffer)
{
	size_t	size;

	original_file_size += r;
	size = (r / 64 + 1) * 64;
	if (size - r <= 8)
		size += 64;
	((uint8_t*)buffer)[r] = 0x80;
	ft_bzero(buffer + r + 1, size - r - 8 - 1);
	*(uint64_t*)(buffer + size - 8) = original_file_size << 3;
	return size;
}

int    read_file(char *filename)
{
	char		buffer[8192 + 64];
	int		fd;
	ssize_t	r;
	size_t	original_file_size;
	t_params	params;

	ft_init(&params);
	original_file_size = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Can't open file for reading\n", 2);
		return (0);
	}
	while ((r = read(fd, buffer, 8192)) || original_file_size == 0)
	{
		if (r < 0)
		{
			close(fd);
			ft_putstr_fd("Read error\n", 2);
			return (0);
		}
		if (r < 8192)
			r = padd_buffer(original_file_size, r, buffer);
		hash_buffer(r, &params, buffer);
		original_file_size += r;
	}
	printf("%08x%08x%08x%08x\n", end_conv_32(params.buffer[0]), end_conv_32(params.buffer[1]), end_conv_32(params.buffer[2]), end_conv_32(params.buffer[3]));
	close(fd);
	return (1);
}

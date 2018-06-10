#include <ft_ssl.h>
#include <stdio.h>
#include <math.h>

uint cshift (uint nbr, uint s)
{
	return (uint)(((nbr) << (s)) | (((nbr) & ((-1u) << (32 - (s)))) >> (32 - (s))));
}

uint end_conv_32(uint nbr)
{
	return (uint)((nbr >> 24) | ((nbr & 0xFF0000) >> 8) | ((nbr & 0xFF00) << 8) | (nbr << 24));
}

uint64_t end_conv_64(uint64_t nbr)
{
	return (uint64_t)(((uint64_t)(end_conv_32(nbr >> 32)) << 32) | ((end_conv_32((uint)nbr))) );
}

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
	int a = (c ^ (b | (~d)));
	a = (~d);
	a = b | (~d);

	return (c ^ (b | (~d)));
}

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

void	functions (t_params *params, t_fghi function, uint n) //ABCD
{
	uint	*a;
	uint	*b;
	uint	*c;
	uint	*d;

	a = params->buffer + (4 - n) % 4;
	b = params->buffer + (5 - n) % 4;
	c = params->buffer + (6 - n) % 4;
	d = params->buffer + (7 - n) % 4;

	*a = *b + cshift((*a + function(*b, *c, *d)
		+ (params->x)[params->k] + params->t[params->i]), params->s);
	printf("{\n\t%c%c%c%c\n\tf = %x\n\tg = %x\n\n\tA = %x\n\tB = %x\n\tC = %x\n\tD = %x\n}\n", (char)((a - params->buffer) + 'A'), (char)((b - params->buffer) + 'A'), (char)((c - params->buffer) + 'A'), (char)((d - params->buffer) + 'A'), function(*b, *c, *d), params->k, *a, *b, *c, *d);
}

// M[] = words du message

void	stage1(t_params *params, char nbr_du_milieu[4][4])
{
	uint	i;

	i = 0;
	while (i < 16)
	{
		params->k = i;
		params->s = nbr_du_milieu[0][i % 4];
		params->i = i + 1;
		functions(params, f, i % 4);
		i++;
	}
}

void	stage2(t_params *params, char nbr_du_milieu[4][4])
{
	uint	i;

	i = 0;
	params->k = 12; // 12 + 5 % 16 = 1
	while (i < 16)
	{
		params->k = (params->k + 5) % 16;
		params->s = nbr_du_milieu[1][i % 4];
		(params->i)++;
		functions(params, g, i % 4);
		i++;
	}
}

void	stage3(t_params *params, char nbr_du_milieu[4][4])
{
	uint	i;

	i = 0;
	params->k = 2; // 2 + 3 % 16 = 5
	while (i < 16)
	{
		params->k = (params->k + 3) % 16;
		params->s = nbr_du_milieu[2][i % 4];
		(params->i)++;
		functions(params, h, i % 4);
		i++;
	}
}

void	stage4(t_params *params, char nbr_du_milieu[4][4])
{
	uint	j;

	j = 0;
	params->k = 9; // 9 + 7 % 16 = 0
	while (j < 16)
	{
		params->k = (params->k + 7) % 16;
		params->s = nbr_du_milieu[3][j % 4];
		(params->i)++;
		functions(params, i, j % 4);
		j++;
	}
}


char	*compute_md5(void *original_file, int64_t original_file_size)
{
	int64_t	size;
	void		*file;
	uint		tour;
	uint		i;
	uint		j;
	uint		buffer_save[4]; // AA BB CC DD
	char nbr_du_milieu [4][4];
	t_params	params;
	int		f;
	int g;
	int temp;

	ft_memcpy(nbr_du_milieu, (char[4][4]){{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}}, sizeof(nbr_du_milieu));

	size = (original_file_size / 64 + 1) * 64;
	if (size - original_file_size <= 8)
		size += 64;
	// printf("padded size : %llu\n", size);
	if (!(file = malloc(size)))
		return (NULL);
	ft_memcpy(file, original_file, original_file_size);
	free(original_file);
	*(uint8_t *)(file + original_file_size) = 0x80;
	i = 0;
	while (i < size - original_file_size - 8 - 1)
	{
		*(uint8_t *)(file + original_file_size + 1 + i) = 0x00;
		i++;
	}
	// *(int64_t*)(file + original_file_size + 1 + i) = END_CONV_64((uint64_t) original_file_size);
	*(int64_t*)(file + original_file_size + 1 + i) = original_file_size;

	// print_memory(file, size);
	// write(1, file, size);

	initialize_buffer(params.buffer);
	initialize_t(params.t);
	tour = 0;
	while (tour <= size / 64 - 1)
	{
		j = 0;
		while (j <= 15)
		{
			(params.x)[j] = ((uint*)file)[tour * 16 + j];
			printf("%d\n", (params.x)[j]);
			j++;
		}
		// ft_memcpy(buffer_save, params.buffer, sizeof(params.buffer));
		buffer_save[0] = params.buffer[0];
		buffer_save[1] = params.buffer[1];
		buffer_save[2] = params.buffer[2];
		buffer_save[3] = params.buffer[3];

		stage1(&params, nbr_du_milieu);
		stage2(&params, nbr_du_milieu);
		stage3(&params, nbr_du_milieu);
		stage4(&params, nbr_du_milieu);

		params.buffer[0] = (uint)params.buffer[0] + (uint)buffer_save[0];
		params.buffer[1] = (uint)params.buffer[1] + (uint)buffer_save[1];
		params.buffer[2] = (uint)params.buffer[2] + (uint)buffer_save[2];
		params.buffer[3] = (uint)params.buffer[3] + (uint)buffer_save[3];
		tour++;
	}
	printf("%08x%08x%08x%08x\n", end_conv_32(params.buffer[0]), end_conv_32(params.buffer[1]), end_conv_32(params.buffer[2]), end_conv_32(params.buffer[3]));
	return file;
}

int main(int argc, char **argv)
{

	void		*file;
	size_t	file_size;

	if (argc != 2)
	{
		ft_putstr_fd("Usage : not like this\n", 2);
		return (1);
	}
	if (!(file = read_file(argv[1], &file_size)))
	{
		return (2);
	}
	// write(1, file, file_size);

	// printf("%d\n", cshift(3221225472u,2));
	file = compute_md5(file, file_size);
	free(file);
}

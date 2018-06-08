#include <ft_ssl.h>
#include <stdio.h>
#include <math.h>

void	*memjoin_af1(void *m1, size_t s1, const void *m2, size_t s2)
{
	void *ret;

	if (!(ret = malloc(s1 + s2)))
		return NULL;
	ft_memcpy(ret, m1, s1);
	free(m1);
	ft_memcpy(ret + s1, m2, s2);
	return (ret);
}

void    *read_file(char *filename, size_t *file_size)
{
	char		buffer[32];
	int		fd;
	ssize_t	r;
	void		*ret;
	size_t	size;

	size = 0;
	ret = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Can't open file for reading\n", 2);
		return (NULL);
	}
	while ((r = read(fd, buffer, 32)))
	{
		if (r < 0)
		{
			close(fd);
			free(ret);
			ft_putstr_fd("Read error\n", 2);
			return NULL;
		}
		if (!(ret = memjoin_af1(ret, size, buffer, r)))
		{
			close(fd);
			ft_putstr_fd("Allocation error\n", 2);
			return (NULL);
		}
		size += r;
	}
	close(fd);
	*file_size = size;
	return (ret);
}

int	f(int x, int y, int z)
{
	 return ((x & y) | ((!x) & z));
}

int	g(int x, int y, int z)
{
	return ((x & z) | (y & (!z)));
}

int	h(int x, int y, int z)
{
	return (x ^ y ^ z);
}

int	i(int x, int y, int z)
{
	return (y ^ (x | (!z)));
}


void	initialize_buffer (int *buffer)
{
	buffer[0] = 0x67452301;
	buffer[1] = 0xefcdab89;
	buffer[2] = 0x98badcfe;
	buffer[3] = 0x10325476;
}

void	initialize_t (unsigned int *t)
{
	int i;

	i = 1;
	while (i <= 64)
	{
		t[i] = 4294967296.0 * fabs(sin(i));
		i++;
	}
}

void	functions (t_params *params, t_fghi function, int n) //ABCD
{
	int	*a;
	int	*b;
	int	*c;
	int	*d;

	a = params->buffer + (0 + n) % 4;
	b = params->buffer + (1 + n) % 4;
	c = params->buffer + (2 + n) % 4;
	d = params->buffer + (3 + n) % 4;

	*a = *b + CSHIFT(((*a + function(*b, *c, *d)
		+ (params->x)[params->k] + params->t[params->i])), params->s);
}

// M[] = words du message

void	stage1(t_params *params, char nbr_du_milieu[4][4])
{
	int	i;

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
	int	i;

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
	int	i;

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
	int	j;

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
	int		i;
	int		j;
	int		buffer_save[4]; // AA BB CC DD
	int		stage;
	int		x;
	int		y;
	char nbr_du_milieu [4][4];
	t_params	params;


	ft_memcpy(nbr_du_milieu, (char[4][4]){{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}}, sizeof(nbr_du_milieu));

	size = (original_file_size / 64 + 1) * 64;
	if (size - original_file_size <= 8)
		size += 64;
	printf("padded size : %llu\n", size);
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
	*(int64_t*)(file + original_file_size + 1 + i) = original_file_size;
	// print_memory(file, size);
	initialize_buffer(params.buffer);
	initialize_t(params.t);
	i = 0;
	stage = 0;
	x = 0;
	y = 0;
	while (i <= size / 64 - 1)
	{
		j = 0;
		while (j <= 15)
		{
			(params.x)[j] = ((int*)file)[i * 16 + j];
			j++;
		}
		ft_memcpy(buffer_save, params.buffer, sizeof(params.buffer));
		stage1(&params, nbr_du_milieu);
		stage2(&params, nbr_du_milieu);
		stage3(&params, nbr_du_milieu);
		stage4(&params, nbr_du_milieu);
		i++;
	}
	printf("%x%x%x%x\n", params.buffer[0], params.buffer[1], params.buffer[2], params.buffer[3]);
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
		return (2);
	// write(1, file, file_size);

	printf("%d\n", CSHIFT(3221225472u,2));
	compute_md5(file, file_size);
}
//

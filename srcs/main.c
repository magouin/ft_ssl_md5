#include <ft_ssl.h>
#include <stdio.h>

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

char	*compute_md5(void *original_file, int64_t original_file_size)
{
	int64_t	size;
	void		*file;
	int		i;

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
	print_memory(file, size);
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
	compute_md5(file, file_size);
}

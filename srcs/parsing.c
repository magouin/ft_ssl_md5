#include <ft_ssl.h>

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
	ret = malloc(1);
	*(char*)ret = '\0';
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Can't open file for reading\n", 2);
		free (ret);
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

#include <ft_ssl.h>

void	hash_buffer_md5(ssize_t r, t_params_md5 *params, char *buffer)
{
	int			i;
	static char	nbr_du_milieu[4][4] = {{7, 12, 17, 22},
		{5, 9, 14, 20}, {4, 11, 16, 23}, {6, 10, 15, 21}};

	i = 0;
	while (i <= r / 64 - 1)
	{
		compute_buffer(params, nbr_du_milieu, buffer + i * 16 * sizeof(uint));
		i++;
	}
}

int		ft_init(t_params_md5 *params, size_t *original_file_size,
		int *fd, char *filename)
{
	initialize_buffer(params->buffer);
	initialize_t(params->t);
	*original_file_size = 0;
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd("Can't open file for reading\n", 2);
		return (0);
	}
	return (1);
}


int		read_file(char *filename)
{
	char		buffer[8192 + 64];
	int			fd;
	ssize_t		r;
	size_t		original_file_size;
	t_params_md5	params;

	if (!ft_init(&params, &original_file_size, &fd, filename))
		return (0);
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
		hash_buffer_md5(r, &params, buffer);
		original_file_size += r;
	}
	print_result_32(params.buffer);
	close(fd);
	return (1);
}

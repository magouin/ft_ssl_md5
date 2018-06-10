#include <ft_ssl.h>
#include <stdio.h>

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

// M[] = words du message

void	compute_buffer(t_params *params, char nbr_du_milieu[4][4], void *buffer)
{
	int	j;
	uint	buffer_save[4];

	j = 0;
	while (j <= 15)
	{
		(params->x)[j] = ((uint*)buffer)[j];
		j++;
	}
	buffer_save[0] = params->buffer[0];
	buffer_save[1] = params->buffer[1];
	buffer_save[2] = params->buffer[2];
	buffer_save[3] = params->buffer[3];

	stage1(params, nbr_du_milieu);
	stage2(params, nbr_du_milieu);
	stage3(params, nbr_du_milieu);
	stage4(params, nbr_du_milieu);

	params->buffer[0] = (uint)params->buffer[0] + (uint)buffer_save[0];
	params->buffer[1] = (uint)params->buffer[1] + (uint)buffer_save[1];
	params->buffer[2] = (uint)params->buffer[2] + (uint)buffer_save[2];
	params->buffer[3] = (uint)params->buffer[3] + (uint)buffer_save[3];
}

// char	*compute_md5(void *original_file, uint64_t original_file_size)
// {
// 	int64_t	size;
// 	void		*file;
// 	uint		tour;
// 	uint		i;
// 	uint		buffer_save[4]; // AA BB CC DD
// 	char nbr_du_milieu [4][4];
// 	t_params	params;
//
// 	// ft_memcpy(nbr_du_milieu, (char[4][4]){{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}}, sizeof(nbr_du_milieu));
//
// 	// size = (original_file_size / 64 + 1) * 64;
// 	// if (size - original_file_size <= 8)
// 	// 	size += 64;
// 	// if (!(file = malloc(size)))
// 	// 	return (NULL);
// 	// ft_memcpy(file, original_file, original_file_size);
// 	// free(original_file);
// 	// *(uint8_t *)(file + original_file_size) = 0x80;
// 	// i = 0;
// 	// while (i < size - original_file_size - 8 - 1)
// 	// {
// 	// 	*(uint8_t *)(file + original_file_size + 1 + i) = 0x00;
// 	// 	i++;
// 	// }
// 	// *(uint64_t*)(file + original_file_size + 1 + i) = original_file_size << 3;
//
// 	// initialize_buffer(params.buffer);
// 	// initialize_t(params.t);
// 	tour = 0;
// 	while (tour <= size / 64 - 1)
// 	{
// 		compute_buffer(&params, nbr_du_milieu, file + (tour * 16 * sizeof(uint)));
// 		tour++;
// 	}
// 	printf("%08x%08x%08x%08x\n", end_conv_32(params.buffer[0]), end_conv_32(params.buffer[1]), end_conv_32(params.buffer[2]), end_conv_32(params.buffer[3]));
// 	return file;
// }

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
	printf("Read ok \n");
	// file = compute_md5(file, file_size);
	free(file);
}

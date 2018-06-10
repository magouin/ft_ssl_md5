#include <ft_ssl.h>

uint	cshift(uint nbr, uint s)
{
	return (uint)(((nbr) << (s)) |
		(((nbr) & ((-1u) << (32 - (s)))) >> (32 - (s))));
}

uint	end_conv_32(uint nbr)
{
	return (uint)((nbr >> 24) | ((nbr & 0xFF0000) >> 8) |
		((nbr & 0xFF00) << 8) | (nbr << 24));
}

void	compute_buffer(t_params *params, char nbr_du_milieu[4][4], void *buffer)
{
	uint	buffer_save[4];

	params->x = buffer;
	ft_memcpy(buffer_save, params->buffer, sizeof(params->buffer));
	stage1(params, nbr_du_milieu);
	stage2(params, nbr_du_milieu);
	stage3(params, nbr_du_milieu);
	stage4(params, nbr_du_milieu);
	params->buffer[0] = (uint)params->buffer[0] + (uint)buffer_save[0];
	params->buffer[1] = (uint)params->buffer[1] + (uint)buffer_save[1];
	params->buffer[2] = (uint)params->buffer[2] + (uint)buffer_save[2];
	params->buffer[3] = (uint)params->buffer[3] + (uint)buffer_save[3];
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Usage : not like this\n", 2);
		return (1);
	}
	if (!read_file(argv[1]))
		return (2);
	return (0);
}

#ifndef FT_SSL_H
# define FT_SSL_H

# include <libft.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

typedef struct	s_params
{
	uint		buffer[4];
	uint		k;
	uint		s;
	uint		i;
	uint		t[65];
	const uint	*x;
}				t_params;

typedef uint	(*t_fghi) (uint, uint, uint);
typedef void	(*t_f1234) (t_params*, t_fghi);

int				read_file(char *filename);

void			stage1(t_params *params, char nbr_du_milieu[4][4]);
void			stage2(t_params *params, char nbr_du_milieu[4][4]);
void			stage3(t_params *params, char nbr_du_milieu[4][4]);
void			stage4(t_params *params, char nbr_du_milieu[4][4]);

void			compute_buffer(t_params *params, char nbr_du_milieu[4][4],
	void *buffer);

uint			f(uint b, uint c, uint d);
uint			g(uint b, uint c, uint d);
uint			h(uint b, uint c, uint d);
uint			i(uint b, uint c, uint d);

uint			cshift(uint nbr, uint s);
uint			end_conv_32(uint nbr);

void			initialize_buffer(uint *buffer);
void			initialize_t(uint t[65]);
#endif

#ifndef FT_SSL_H
# define FT_SSL_H

# include <libft.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

# define P_OPT	1
# define Q_OPT	2
# define R_OPT	4
# define S_OPT	8

/*
	General
*/

typedef struct	s_opt
{
	int8_t		flags;
	char		*content; // File or string depending
}				t_opt;

int			padd_buffer(int original_file_size, int r, char *buffer);
uint32_t	rotl(uint32_t n, uint32_t x);
uint32_t	rotr(uint32_t n, uint32_t x);
void		print_result_32(uint buffer[4]);


/*
	MD5
*/

typedef struct	s_params_md5
{
	uint		buffer[4];
	uint		k;
	uint		s;
	uint		i;
	uint		t[65];
	const uint	*x;
}				t_params_md5;

typedef uint	(*t_fghi) (uint, uint, uint);

int				read_file(char *filename);

void			stage1(t_params_md5 *params, char nbr_du_milieu[4][4]);
void			stage2(t_params_md5 *params, char nbr_du_milieu[4][4]);
void			stage3(t_params_md5 *params, char nbr_du_milieu[4][4]);
void			stage4(t_params_md5 *params, char nbr_du_milieu[4][4]);

void			compute_buffer(t_params_md5 *params, char nbr_du_milieu[4][4],
	void *buffer);
int				compute_from_string_md5(char *str);

uint			f(uint b, uint c, uint d);
uint			g(uint b, uint c, uint d);
uint			h(uint b, uint c, uint d);
uint			i(uint b, uint c, uint d);

uint			cshift(uint nbr, uint s);
uint			end_conv_32(uint nbr);

void			initialize_buffer(uint *buffer);
void			initialize_t(uint t[65]);



int	main_md5(int argc, char **argv);

/*
	SHA-256
*/


typedef struct	s_params_sha256
{
	uint32_t	*k;
	uint32_t	*h;
	uint32_t	*schedule;
	uint32_t	*working;
}				t_params_sha256;




int				main_256(int ac, char **av, t_opt *opt);
uint32_t		ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t		maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t		gs0(uint32_t x);
uint32_t		gs1(uint32_t x);
uint32_t		ps0(uint32_t x);
uint32_t		ps1(uint32_t x);

void			sha256_compute_buffer(t_params_sha256 *params, void *buffer);
void			print_result_64(unsigned char buffer[32]);
uint64_t		end_conv_64(uint64_t nbr);

#endif

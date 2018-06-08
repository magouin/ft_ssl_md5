#ifndef FT_SSL_H
# define FT_SSL_H

# include <libft.h>
# include <fcntl.h>
# include <unistd.h>

# define CSHIFT(nbr, s) (int)(((nbr) << (s)) | (((nbr) & ((-1u) << (32 - (s)))) >> (32 - (s))))

typedef struct s_params
{
	int buffer[4];
	int k;
	int s;
	int i;
	unsigned int t[65];
	int x[16];
}		t_params;

typedef int	(*t_fghi) (int, int, int);
typedef void (*t_f1234) (t_params*, t_fghi);

void print_memory(char *start, size_t size);

#endif

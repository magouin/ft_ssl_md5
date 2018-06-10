#include <ft_ssl.h>


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
	// printf("{\n\t%c%c%c%c\n\tf = %x\n\tg = %x\n\n\tA = %x\n\tB = %x\n\tC = %x\n\tD = %x\n}\n", (char)((a - params->buffer) + 'A'), (char)((b - params->buffer) + 'A'), (char)((c - params->buffer) + 'A'), (char)((d - params->buffer) + 'A'), function(*b, *c, *d), params->k, *a, *b, *c, *d);
}

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

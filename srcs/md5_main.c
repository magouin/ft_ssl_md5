#include <ft_ssl.h>

static void print_opt(t_opt *opt)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (opt->flags & (1 << i))
			printf("option -%c enabled.\n", 'p' + i);
		i++;
	}
	printf("content : [%s]\n", opt->content);
}

int	main_md5(t_opt *opt)
{
	print_opt(opt);
	if (opt->flags & S_OPT)
		compute_from_string_md5(opt->content);
	else
		read_file(opt->content);
	return (1);
}

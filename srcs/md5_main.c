#include <ft_ssl.h>

// static void print_opt(t_opt *opt)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i < 4)
// 	{
// 		if (opt->flags & (1 << i))
// 			printf("option -%c enabled.\n", 'p' + i);
// 		i++;
// 	}
// 	printf("content : [%s]\n", opt->content);
// }

int	main_md5(t_opt *opt)
{
	// static int	already_called_with_p = 0;

	// if (already_called_with_p == 1 && opt->content == NULL)
	// 	return (1);
	// if (opt->flags & P_OPT)
	// 	already_called_with_p = 1;
	// print_opt(opt);
	if (opt->flags & S_OPT)
		compute_from_string_md5(opt->content);
	else
		read_file(opt->content);
	return (1);
}

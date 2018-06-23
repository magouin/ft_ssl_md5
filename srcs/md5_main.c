#include <ft_ssl.h>

int	main_md5(int argc, char **argv)
{
	if (argc >= 3)
	{
		if (!read_file(argv[2]))
			return (2);
	}
	return (0);
}

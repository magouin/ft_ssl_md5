#include <ft_ssl.h>

static int	get_option(char *option, t_opt *opt)
{
	int	i;
	int	tmp;

	i = 1;
	tmp = 1;
	while (option[i])
	{
		if (option[i] >= 'p' && option[i] <= 's')
			opt->flags |= 1 << (option[i] - 'p');
		else
		{
			ft_putstr_fd("Illegal option: ", 2);
			write(2, option + i, 1);
			ft_putstr_fd("\n", 2);
			return (0);
		}
		if (opt->flags & S_OPT)
			tmp = 2;
		i++;
	}
	return (tmp);
}

static int	do_parsing(char **av, t_opt *opt, int (*fun) (t_opt*))
{
	int	i;
	int	x;

	i = 2;
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			if ((x = get_option(av[i], opt)) == 0)
				return (0);
			else if (x == 2)
			{
				if (!av[i + 1])
					return (0);
				opt->content = av[i + 1];
				fun(opt);
				opt->flags &= ~S_OPT;
				i++;
			}
		}
		else
		{
			opt->content = av[i];
			fun(opt);
		}
		i++;
	}
	return (1);
}

int	parse_options(int ac, char **av, t_opt *opt)
{
	int (*fun) (t_opt*);

	if (ac < 3)
		return (0);
	ft_bzero(opt, sizeof(t_opt));
	if (ft_strequ(av[1], "md5"))
		fun = main_md5;
	else if (ft_strequ(av[1], "sha256"))
		fun = main_256;
	else
	{
		ft_putstr_fd("Unknown algorithm: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	if (!do_parsing(av, opt, fun))
		return (0);

	return (1);
}

#include <ft_ssl.h>

static int	get_option(char *option, t_opt *opt, int (*fun) (t_opt*))
{
	int	i;

	i = 1;
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
		{
			if (option[i + 1] == '\0')
				opt->content = NULL;
			else
				opt->content = option + i + 1;
			return (1);
		}
		else if (opt->flags & P_OPT)
		{
			fun(opt);
			opt->flags &= ~P_OPT;
			opt->has_read_something = opt->flags & R_OPT ? 0 : 1;
		}
		else if (opt->flags & R_OPT && opt->has_read_something)
			opt->has_read_something = 0;
		i++;
	}
	return (1);
}

static int	do_parsing(char **av, t_opt *opt, int (*fun) (t_opt*))
{
	int	i;

	i = 2;
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			if (!get_option(av[i], opt, fun))
				return (0);
			if (opt->flags & S_OPT)
			{
				if (!opt->content)
				{
					if (!av[i + 1])
						return (0);
					opt->content = av[i + 1];
					i++;
				}
				fun(opt);
				opt->flags &= ~S_OPT;
			}
		}
		else
		{
			opt->content = av[i];
			fun(opt);
		}
		i++;
	}
	if (opt->content == NULL && !opt->has_read_something)
		fun(opt);
	return (1);
}

int	parse_options(int ac, char **av, t_opt *opt)
{
	int (*fun) (t_opt*);

	if (ac < 2)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 05:35:04 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/29 03:33:25 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

static int set_timeout(int *i, int ac, char *value)
{
	int	timeout;
	
	if (*i + 1 < ac && ft_isnumber(value))
	{
		timeout = ft_atoi(value);
		if (timeout < 1 || timeout > 300)
			return (print_args_error("%sft_malcolm:%s timeout out of range\n", RED, NC));
	}
	else
	{
		if (value)
			return (print_args_error("%sft_malcolm:%s cannot handle `-t' option with arg `%s' (argc %d)\n", RED, NC, value, *i + 2));
		else
			return (print_args_error("%sft_malcolm:%s option `-t' (argc %d) requires an argument: `-t TIMEOUT'\n", RED, NC, *i + 1));
	}
	*i += 1;
	return (timeout);
}

static int	handle_options(t_options *ops, int ac, char **av)
{
	int	i;

	i = 5;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (ft_strchr("vgt", av[i][1]) && av[i][2] == '\0')
			{
				switch(av[i][1])
				{
					case 'v':
						ops->verbose = 1;
						break ;
					case 'g':
						ops->gratuitous = 1;
						break ;
					case 't':
						ops->timeout = set_timeout(&i, ac, av[i + 1]);
						if (ops->timeout == NON_VALID)
							return (NON_VALID);
						break ;
				}
			}
			else
				return (print_args_error("%sft_malcolm:%s bad option `%s' (argc %d)\n", RED, NC, av[i], i + 1));
		}
		else
			return (print_args_error("%sft_malcolm:%s extra arg `%s' (argc %d)\n", RED, NC, av[i], i + 1));
		i++;
	}
	return (VALID);
}

static int	convert_addr(char type, t_device *device, char *addr, int i)
{
	int	ret;

	if (type == 'i')
	{
		ret = is_valid_ipv4_or_hostname(addr, device, i);
		if (ret == VALID)
		{
			if (!inet_pton(AF_INET, device->ip_str, device->ip_addr))
				return (print_args_error("%sft_malcolm:%s failed to convert IPv4 address into binary format `%s' (argc %d)\n", RED, NC, addr, i));
		}
		else if (ret == MSG_PRINTED)
			return (NON_VALID);
		else
			return (print_args_error("%sft_malcolm:%s invalid IPv4 address or FQDN format `%s' (argc %d)\n", RED, NC, addr, i));
	}
	else if (type == 'm')
	{
		if (is_valid_mac(addr) == VALID)
		{
			printf("VALID MAC\n");
		}
		else
			return (print_args_error("%sft_malcolm:%s invalid MAC address format `%s' (argc %d)\n", RED, NC, addr));
	}
	return (VALID);
}

static int	check_addr(t_device *source, t_device *target, char **av)
{
	if (convert_addr('i', source, av[1], 2) == NON_VALID)
		return (NON_VALID);
	if (convert_addr('i', target, av[3], 4) == NON_VALID)
		return (NON_VALID);
	if (convert_addr('m', source, av[2], 3) == NON_VALID)
		return (NON_VALID);
	if (convert_addr('m', source, av[4], 5) == NON_VALID)
		return (NON_VALID);
	return (VALID);
}

int	parse_args(t_malcolm *malcolm, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strncmp(av[i], "--help", 6) == 0 && ft_strlen(av[i]) == 6)
			return (print_usage(av[0], EXIT_SUCCESS));
		i++;
	}

	if (handle_options(&malcolm->options, ac, av) == NON_VALID)
		return (NON_VALID);

	if (check_addr(&malcolm->source, &malcolm->target, av) == NON_VALID)
		return (NON_VALID);

	return (VALID);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 04:21:30 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/29 05:34:35 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

static int	resolve_host(char *hostname, struct addrinfo **res)
{
	struct addrinfo	hints;

	*res = NULL;
	ft_memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;

	if (getaddrinfo(hostname, NULL, &hints, res) == -1 || *res == NULL)
		return (NON_VALID);
	return (VALID);
}

static int	fetch_ip_addr(char *input, t_device *device, int pos)
{
	struct addrinfo		*res;
	struct sockaddr_in	*addr_in;

	if (resolve_host(input, &res) == NON_VALID)
		return (print_args_error("%sft_malcolm:%s failed to retrieve address info for `%s' (argc %d)\n", RED, NC, input, pos));

	if (res->ai_addrlen != IPv4_LENGTH)
	{
		freeaddrinfo(res);
		return (print_args_error("%sft_malcolm:%s address length mismatch `%s' (argc %d)\n", RED, NC, input, pos));
	}

	addr_in = (struct sockaddr_in *)res->ai_addr;
	ft_strlcpy(device->ip_str, inet_ntoa(addr_in->sin_addr), IPv4_LENGTH);
	freeaddrinfo(res);
	return (VALID);
}

static int	is_valid_decimal_ipv4(char *input, t_device *device)
{
	int				i;
	long			decimal_ip;
	struct in_addr	addr;

	i = 0;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
			return (NON_VALID);
		i++;
	}
	decimal_ip = ft_atoi_long(input);
	if (decimal_ip < 0 || decimal_ip > 4294967295)
		return (NON_VALID);
	addr.s_addr = htonl(decimal_ip);
	if (!inet_ntop(AF_INET, &addr, device->ip_str, sizeof(device->ip_str)))
		return (NON_VALID);
	return (VALID);
}

static int	is_valid_ipv4(char *input)
{
	int		i;
	int		num;
	int		dots;
	int		octet;

	i = 0;
	dots = 0;
	while (input[i])
	{
		octet = i;
		if (!ft_isdigit(input[i]) && input[i] != '.')
			return (NON_VALID);
		num = ft_atoi(&input[i]);
		if (num < 0 || num > 255)
			return (NON_VALID);
		while (input[i] && input[i] != '.')
			i++;
		if (input[octet] == '0' && (i - octet) > 1)
			return (NON_VALID);
		if (input[i] == '.')
		{
			if (i == octet)
				return (NON_VALID);
			dots += 1;
			i++;	
		}
	}
	if (dots != 3)
		return (NON_VALID);
	return (VALID);
}

int	is_valid_ipv4_or_hostname(char *input, t_device *device, int pos)
{
	int	len;
	int	i;

	i = 0;
	if (is_valid_decimal_ipv4(input, device) == VALID)
		return (VALID);
	if (is_valid_ipv4(input) == VALID)
	{
		ft_strlcpy(device->ip_str, input, ft_strlen(input) + 1);
		return (VALID);
	}
	len = ft_strlen(input);
	if (len == 0 || len > MAX_HOSTNAME)
		return (NON_VALID);
	if (input[0] == '.' || input[len - 1] == '.')
		return (NON_VALID);
	while (i < len)
	{
		if (!ft_isalnum(input[i]) && input[i] != '-' && input[i] != '.')
			return (NON_VALID);
		if (input[i] == '.' && input[i + 1] == '.')
			return (NON_VALID);
		if (input[i] == '-' && (i == 0 || i == len - 1 || input[i - 1] == '.'))
			return (NON_VALID);
		i++;
	}
	if (fetch_ip_addr(input, device, pos) == NON_VALID)
		return (MSG_PRINTED);
	return (VALID);
}

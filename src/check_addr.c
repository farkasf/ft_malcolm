/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_addr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 04:21:30 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/29 03:32:23 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

int	is_valid_mac(char *input)
{
	int	i;

	i = 0;
	if (ft_strlen(input) != 17)
		return (NON_VALID);
	while (input[i])
	{
		if (i % 3 == 2)
		{
			if (input[i] != ':')
				return (NON_VALID);
		}
		else
		{
			if (!ft_isxdigit(input[i]))
				return (NON_VALID);
		}
		i++;
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mac.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 04:20:39 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/29 05:06:50 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

static void	convert_mac_addr(char *mac_addr, t_device *device)
{
	int	i;
	int	j;
	int	k;
	int value;

	i = 0;
	j = 0;
	while (mac_addr[i] && j < MAC_BINLENGTH)
	{
		k = 0;
		value = 0;
		while (k < 2)
		{
			if (mac_addr[i] == ':')
			{
				i++;
				continue ;
			}
			if (mac_addr[i] >= '0' && mac_addr[i] <= '9')
				value = value * 16 + (mac_addr[i] - '0');
			else
				value = value * 16 + (ft_tolower(mac_addr[i]) - 'a' + 10);
			i++;
			k++;
		}
		device->mac_addr[j] = (unsigned char)value;
		j++;
	}
}

int	is_valid_mac(char *input, t_device *device)
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
	convert_mac_addr(input, device);
	return (VALID);
}

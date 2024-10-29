/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:35:18 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/29 03:32:26 by ffarkas          ###   ########.fr       */
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

int	fetch_ip_addr(char *input, t_device *device, int pos)
{
	struct addrinfo		*res;
	struct sockaddr_in	*addr_in;

	if (resolve_host(input, &res) == NON_VALID)
		return (print_args_error("%sft_malcolm:%s temporary failure in hostname `%s' resolution (argc %d)\n", RED, NC, input, pos));

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spoof.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:48:56 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/31 03:12:39 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

int	listen_to_broadcast(t_malcolm *malcolm)
{
	struct sockaddr_in	recv_addr;
	socklen_t			addr_size;
	ssize_t				recv_bytes;
	unsigned char		buffer[sizeof(struct ethhdr) + sizeof(t_packet)];
	int					iter;

	iter = 0;
	addr_size = sizeof(recv_addr);
	while (g_sig_status)
	{
		iter++;
		recv_bytes = recvfrom(malcolm->spoof.socket_fd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&recv_addr, &addr_size);
		if (recv_bytes == -1)
		{
			if (errno == EINTR)
				return (VALID);
			else if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				if (malcolm->options.verbose)
					print_timeout(iter, malcolm->options.timeout);
				continue ;
			}
			return (print_args_error("%sft_malcolm:%s packet receiving failed\n", RD, NC));
		}
		if (ft_memcmp(buffer, "\xff\xff\xff\xff\xff\xff", 6) == 0)
		{
			dprintf(STDOUT_FILENO, "\n%sft_malcolm:%s an ARP request has been broadcast [%s]\n", YL, NC, fetch_time());
			return (VALID);
		}
	}
	return (VALID);
}

int	spoof_run(t_malcolm *malcolm)
{
	if (fetch_interface(malcolm) == NON_VALID)
		return (print_args_error("%sft_malcolm:%s no matching interface found\n", RD, NC));
	
	if (setup_socket(malcolm) == NON_VALID)
		return (NON_VALID);

	if (listen_to_broadcast(malcolm) == NON_VALID)
		return (NON_VALID);

	return (VALID);
}

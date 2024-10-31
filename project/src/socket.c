/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:31:22 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/31 01:23:54 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

static int	init_socket(int *socket_fd)
{
	*socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (*socket_fd == -1)
		return (print_args_error("%sft_malcolm:%s failed to create ARP socket: %s\n", RD, NC, strerror(errno)));
	return (VALID);
}

static int	set_socket_timeout(int socket_fd, int timeout)
{
	struct timeval	period;

	period.tv_sec = timeout;
	period.tv_usec = 0;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &period, sizeof(period)) == -1)
	{
		close(socket_fd);
		return (print_args_error("%sft_malcolm:%s failed to set socket timeout: %s\n", RD, NC, strerror(errno)));	
	}
	return (VALID);
}

static int	configure_sender(struct sockaddr_ll	*socket_addr, t_malcolm *malcolm)
{
	unsigned int	interface_index;

	ft_memset(socket_addr, 0, sizeof(struct sockaddr_ll));
	interface_index = if_nametoindex(malcolm->interface);
	if (interface_index == 0)
	{
		close(malcolm->spoof.socket_fd);
		return (print_args_error("%sft_malcolm:%s could not fetch interface index", RD, NC));	
	}
	socket_addr->sll_ifindex = interface_index;
	ft_memcpy(socket_addr->sll_addr, malcolm->target.mac_addr, MAC_BINLENGTH);
	socket_addr->sll_family = AF_PACKET;
	socket_addr->sll_pkttype = 0;
	socket_addr->sll_protocol = htons(ETH_P_ARP);
	socket_addr->sll_hatype = htons(ARPHRD_ETHER);
	socket_addr->sll_halen = MAC_BINLENGTH;
	return (VALID);
}

int	setup_socket(t_malcolm *malcolm)
{
	if (init_socket(&malcolm->spoof.socket_fd) == NON_VALID)
		return (NON_VALID);
	if (set_socket_timeout(malcolm->spoof.socket_fd, malcolm->options.timeout) == NON_VALID)
		return (NON_VALID);
	if (configure_sender(&malcolm->spoof.socket_addr, malcolm) == NON_VALID)
		return (NON_VALID);
	return (VALID);
}

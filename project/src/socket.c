/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:31:22 by ffarkas           #+#    #+#             */
/*   Updated: 2024/11/01 08:33:19 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

int	configure_sender(struct sockaddr_ll	*socket_addr, t_malcolm *malcolm)
{
	ft_memset(socket_addr, 0, sizeof(struct sockaddr_ll));
	socket_addr->sll_ifindex = malcolm->interface.index;
	if (malcolm->options.gratuitous)
		ft_memset(socket_addr->sll_addr, 0xFF, MAC_BINLENGTH);
	else
		ft_memcpy(socket_addr->sll_addr, malcolm->target.mac_addr, MAC_BINLENGTH);
	socket_addr->sll_family = AF_PACKET;
	socket_addr->sll_pkttype = 0;
	socket_addr->sll_protocol = htons(ETH_PROTOCOL_ARP);
	socket_addr->sll_hatype = htons(ARPHRD_ETHER);
	socket_addr->sll_halen = MAC_BINLENGTH;
	return (VALID);
}

static int	init_socket(int *socket_fd)
{
	*socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_PROTOCOL_ARP));
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

int	setup_socket(t_malcolm *malcolm)
{
	if (init_socket(&malcolm->spoof.socket_fd) == NON_VALID)
		return (NON_VALID);
	if (set_socket_timeout(malcolm->spoof.socket_fd, malcolm->options.timeout) == NON_VALID)
		return (NON_VALID);
	return (VALID);
}

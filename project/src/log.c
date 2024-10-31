/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 05:20:45 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/31 07:06:05 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

void	print_eth_info(struct ethhdr *eth_header)
{
	char	eth_s_mac[MAC_LENGTH];
	char	eth_t_mac[MAC_LENGTH];

	format_mac(eth_header->h_source, eth_s_mac);
	format_mac(eth_header->h_dest, eth_t_mac);
	dprintf(STDOUT_FILENO, 
		"%s%sETHERNET HEADER%s\n"
		"%s* source MAC address: %s\n"
		"%s* target MAC address: %s\n"
		"%s* protocol: 0x%04x\n\n"
		, PAD, BL, NC, PAD, eth_s_mac, PAD, eth_t_mac, PAD, ntohs(eth_header->h_proto));
}

void	print_arp_info(t_packet *packet)
{
	dprintf(STDOUT_FILENO, 
		"%s%sARP HEADER%s\n"
		"%s* hardware type: %u\n"
		"%s* protocol: 0x%04x\n"
		"%s* length of the hardware address: %u\n"
		"%s* length of the protocol address: %u\n"
		"%s* operation type: %u\n\n"
		, PAD, BL, NC, PAD, htons(packet->header.ar_hrd), PAD, htons(packet->header.ar_pro), PAD \
		, packet->header.ar_hln, PAD, packet->header.ar_pln, PAD, htons(packet->header.ar_op));
}

void	print_request(t_malcolm *malcolm)
{
	char	source_mac[MAC_LENGTH];
	char	source_ip[IPv4_LENGTH];
	char	target_mac[MAC_LENGTH];
	char	target_ip[IPv4_LENGTH];
	char	source_name[MAX_HOSTNAME];
	char	target_name[MAX_HOSTNAME];

	format_mac(malcolm->packet.source_mac, source_mac);
	format_mac(malcolm->packet.target_mac, target_mac);
	format_ip(malcolm->packet.source_ip, source_ip);
	format_ip(malcolm->packet.target_ip, target_ip);
	format_host(malcolm->packet.source_ip, source_name);
	format_host(malcolm->packet.target_ip, target_name);
	dprintf(STDOUT_FILENO, 
		"%s\nft_malcolm:%s an ARP request has been broadcast [%s]\n\n"
		"%s%sARP PACKET%s\n"
		"%s* source IP address: %s (%s)\n"
		"%s* source MAC address: %s\n"
		"%s* target IP address: %s (%s)\n"
		"%s* target MAC address: %s\n\n"
		, YL, NC, fetch_time(), PAD, BL, NC, PAD, source_ip, source_name, PAD, source_mac, PAD, target_ip \
		, target_name, PAD, target_mac);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 05:20:45 by ffarkas           #+#    #+#             */
/*   Updated: 2024/11/01 07:50:28 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

void	print_interface(t_malcolm *malcolm)
{
	char			gateway[IPv4_LENGTH];
	char			netmask[IPv4_LENGTH];

	format_ip(malcolm->interface.gateway, gateway);
	format_ip(malcolm->interface.netmask, netmask);
	dprintf(STDOUT_FILENO, 
		"%s%sINTERFACE INFO%s\n"
		"%s* target interface index: %u\n"
		"%s* target gateway: %s\n"
		"%s* target netmask: %s\n\n"
		, PAD, BL, NC, PAD, malcolm->interface.index, PAD, gateway, PAD, netmask);
}

void	print_start(t_malcolm *malcolm)
{
	char	source_mac[MAC_LENGTH];
	char	target_mac[MAC_LENGTH];

	format_mac(malcolm->source.mac_addr, source_mac);
	format_mac(malcolm->target.mac_addr, target_mac);
	dprintf(STDOUT_FILENO, 
		"%s%sINPUT INFO%s\n"
		"%s* source IP address: %s (%u) => %s\n"
		"%s* source MAC address: %s\n"
		"%s* target IP address: %s (%u) => %s\n"
		"%s* target MAC address: %s\n\n"
		, PAD, BL, NC, PAD, malcolm->source.ip_str, format_ip_dec(malcolm->source.ip_addr) \
		, malcolm->source.hostname, PAD, source_mac, PAD, malcolm->target.ip_str \
		, format_ip_dec(malcolm->target.ip_addr), malcolm->target.hostname, PAD, target_mac);
}

void	print_eth_info(struct ethhdr *eth_header)
{
	char	eth_s_mac[MAC_LENGTH];
	char	eth_t_mac[MAC_LENGTH];

	format_mac(eth_header->h_source, eth_s_mac);
	format_mac(eth_header->h_dest, eth_t_mac);
	dprintf(STDOUT_FILENO, 
		"%s%sETHERNET HEADER%s\n"
		"%s* target MAC address: %s\n"
		"%s* source MAC address: %s\n"
		"%s* protocol: 0x%04x\n\n"
		, PAD, BL, NC, PAD, eth_t_mac, PAD, eth_s_mac, PAD, ntohs(eth_header->h_proto));
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

void	print_packet_info(t_packet *packet, int operation)
{
	char	source_mac[MAC_LENGTH];
	char	source_ip[IPv4_LENGTH];
	char	target_mac[MAC_LENGTH];
	char	target_ip[IPv4_LENGTH];
	char	source_name[MAX_HOSTNAME];
	char	target_name[MAX_HOSTNAME];

	format_mac(packet->source_mac, source_mac);
	format_mac(packet->target_mac, target_mac);
	format_ip(packet->source_ip, source_ip);
	format_ip(packet->target_ip, target_ip);
	format_host(packet->source_ip, source_name);
	format_host(packet->target_ip, target_name);
	if (operation == ARP_OP_REQUEST)
		dprintf(STDOUT_FILENO, "%s%sARP REQUEST PACKET%s\n", PAD, BL, NC);
	else
		dprintf(STDOUT_FILENO, "%s%sARP REPLY PACKET%s\n", PAD, BL, NC);
	dprintf(STDOUT_FILENO, 
		"%s* source IP address: %s (%u) => %s\n"
		"%s* source MAC address: %s\n"
		"%s* target IP address: %s (%u) => %s\n"
		"%s* target MAC address: %s\n\n"
		, PAD, source_ip, format_ip_dec(packet->source_ip), source_name, PAD, source_mac \
		, PAD, target_ip, format_ip_dec(packet->target_ip), target_name, PAD, target_mac);
}

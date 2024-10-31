/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 03:06:43 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/31 07:06:09 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

void	format_mac(unsigned char *mac, char *out)
{
	snprintf(out, MAC_LENGTH, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void	format_ip(unsigned char *ip, char *out)
{
	snprintf(out, IPv4_LENGTH, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
}

void	format_host(unsigned char *ip, char *out)
{
	struct hostent	*hostname;

	hostname = gethostbyaddr(ip, IPv4_BINLENGTH, AF_INET);
	if (hostname)
		ft_strlcpy(out, hostname->h_name, MAX_HOSTNAME);
	else
		snprintf(out, MAX_HOSTNAME, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
}

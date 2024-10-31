/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:59:30 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/31 23:58:07 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

static void	calculate_mask(uint32_t netmask, unsigned char *out)
{
	unsigned char	mask[IPv4_BINLENGTH];

	mask[3] = (netmask >> 24) & 0xFF;
	mask[2] = (netmask >> 16) & 0xFF;
	mask[1] = (netmask >> 8) & 0xFF;
	mask[0] = netmask & 0xFF;
	ft_memcpy(out, mask, IPv4_BINLENGTH);
}

static void	calculate_gateway(uint32_t netstart, unsigned char *out)
{
	unsigned char	gateway[IPv4_BINLENGTH];

	gateway[3] = 1;
	gateway[2] = (netstart >> 16) & 0xFF;
	gateway[1] = (netstart >> 8) & 0xFF;
	gateway[0] = (netstart) & 0xFF;
	ft_memcpy(out, gateway, IPv4_BINLENGTH);
}

static uint32_t	get_binary_ip(unsigned char *ip_addr)
{
	uint32_t	binary_ip;

	ft_memcpy(&binary_ip, ip_addr, IPv4_BINLENGTH);
	return (binary_ip);
}

static int	is_ip_in_range(uint32_t netip, uint32_t netmask, t_malcolm *malcolm)
{
	uint32_t	netstart;
	uint32_t	netend;
	uint32_t	s_bin_ip;
	uint32_t	t_bin_ip;

	netstart = (netip & netmask);
	netend = (netstart | ~netmask);
	s_bin_ip = get_binary_ip(malcolm->source.ip_addr);
	t_bin_ip = get_binary_ip(malcolm->target.ip_addr);
	if (s_bin_ip >= netstart && s_bin_ip <= netend)
	{
		if (t_bin_ip >= netstart && t_bin_ip <= netend)
		{
			calculate_gateway(netstart, malcolm->interface.gateway);
			calculate_mask(netmask, malcolm->interface.netmask);
			return (VALID);
		}
	}
	return (NON_VALID);
}

static int	is_valid_interface(struct ifaddrs *ifa)
{
	if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET && (ifa->ifa_flags & IFF_UP) && \
			(ifa->ifa_flags & IFF_RUNNING) && !(ifa->ifa_flags & IFF_LOOPBACK))
		return (VALID);
	return (NON_VALID);
}

int	fetch_interface(t_malcolm *malcolm)
{
	struct ifaddrs		*ifaddr;
	struct ifaddrs		*ifa;
	struct sockaddr_in	*addr;
	struct sockaddr_in	*netmask_addr;

	if (getifaddrs(&ifaddr) == -1)
		return (print_args_error("%sft_malcolm:%s error retrieving network interfaces\n", RD, NC));
	
	ifa = ifaddr;
	while (ifa != NULL)
	{
		if (is_valid_interface(ifa) == VALID)
		{
			addr = (struct sockaddr_in *)ifa->ifa_addr;
			netmask_addr = (struct sockaddr_in *)ifa->ifa_netmask;
			if (is_ip_in_range(addr->sin_addr.s_addr, netmask_addr->sin_addr.s_addr, malcolm) == VALID)
			{
				dprintf(STDOUT_FILENO, "%sft_malcolm:%s found available interface: %s\n\n", YL, NC, ifa->ifa_name);
				ft_strlcpy(malcolm->interface.int_name, ifa->ifa_name, MAX_INTERFACE);
				malcolm->interface.index = if_nametoindex(malcolm->interface.int_name);
				if (malcolm->interface.index == 0)
				{
					close(malcolm->spoof.socket_fd);
					return (print_args_error("%sft_malcolm:%s could not fetch interface index", RD, NC));	
				}
				if (malcolm->options.verbose)
					print_interface(malcolm);
				freeifaddrs(ifaddr);
				return (VALID);	
			}
		}
		ifa = ifa->ifa_next;
	}
	freeifaddrs(ifaddr);
	return (NON_VALID);
}

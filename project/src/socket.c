/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:31:22 by ffarkas           #+#    #+#             */
/*   Updated: 2024/11/01 08:46:46 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

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

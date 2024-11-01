/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:11:09 by ffarkas           #+#    #+#             */
/*   Updated: 2024/11/01 08:52:42 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# include <stdbool.h>
# include <stdarg.h>
# include <string.h>

# include <errno.h>
# include <sys/time.h>
# include <time.h>
# include <signal.h>

# include <arpa/inet.h>
# include <sys/socket.h>
# include <netdb.h>
# include <ifaddrs.h>
# include <netinet/in.h>
# include <net/if.h>
# include <netinet/if_ether.h>
# include <netpacket/packet.h>

# define BL     "\033[1;36m"
# define RD     "\033[1;31m"
# define GR     "\033[1;32m"
# define YL     "\033[1;33m"
# define NC     "\033[0m"
# define PAD    "     "
# define DPAD    "          "

# define VALID          1
# define NON_VALID      -1
# define MSG_PRINTED    3

# define IPv4_LENGTH     16
# define IPv4_BINLENGTH  4
# define MAC_LENGTH      18
# define MAC_BINLENGTH   6
# define MAX_HOSTNAME    253
# define MAX_INTERFACE   16

# define FRAME_CHECK_SEQ  4
# define ETH_PROTOCOL_ARP 0x0806
# define ARP_HARDWARE_ETH 1
# define ARP_PROTOCOL_IP  0x0800
# define ARP_OP_REQUEST   1
# define ARP_OP_REPLY     2

# define BROADCAST      "\xff\xff\xff\xff\xff\xff"

extern volatile	sig_atomic_t g_sig_status;

typedef struct s_options
{
	bool	verbose;
	bool	gratuitous;
	int		timeout;
}	t_options;

typedef struct s_device
{
	unsigned char	ip_addr[IPv4_BINLENGTH];
	unsigned char	mac_addr[MAC_BINLENGTH];
	char			ip_str[IPv4_LENGTH];
	char			hostname[MAX_HOSTNAME];
}	t_device;

typedef struct s_spoof
{
	struct sockaddr_ll	socket_addr;
	int					socket_fd;
}	t_spoof;

typedef struct s_packet
{
	struct arphdr	header;
	unsigned char	source_mac[MAC_BINLENGTH];
	unsigned char	source_ip[IPv4_BINLENGTH];
	unsigned char	target_mac[MAC_BINLENGTH];
	unsigned char	target_ip[IPv4_BINLENGTH];
}	t_packet;

typedef struct s_inferface
{
	char			int_name[MAX_INTERFACE];
	unsigned int	index;
	unsigned char	gateway[IPv4_BINLENGTH];
	unsigned char	netmask[IPv4_BINLENGTH];
}	t_interface;

typedef struct s_malcolm
{
	t_options		options;
	t_device		source;
	t_device		target;
	t_spoof			spoof;
	t_interface		interface;
	t_packet		packet;
}	t_malcolm;

//interface.c
int			fetch_interface(t_malcolm *malcolm);

//log_utils.c
void		format_mac(unsigned char *mac, char *out);
void		format_ip(unsigned char *ip, char *out);
void		format_host(unsigned char *ip, char *out);
uint32_t	format_ip_dec(unsigned char *ip);

//log.c
void		print_start(t_malcolm *malcolm);
void		print_interface(t_malcolm *malcolm);
void		print_eth_info(struct ethhdr *eth_header);
void		print_arp_info(t_packet *packet);
void		print_packet_info(t_packet *packet, int operation);

//mitm.c
int			mitm_run(t_malcolm *malcolm);

//packet.c
int			send_arp_reply(t_malcolm *malcolm);

//parse_ip.c
int			is_valid_ipv4_or_hostname(char *input, t_device *device, int pos);

//parse_mac.c
int			is_valid_mac(char *input, t_device *device);

//parser.c
int			parse_args(t_malcolm *malcolm, int ac, char **av);

//socket.c
int			setup_socket(t_malcolm *malcolm);

//utils.c
char		*fetch_time(void);
int			print_args_error(const char *msg, ...);
int			check_uid(void);
int			print_usage(char *prog_name, int status);

#endif

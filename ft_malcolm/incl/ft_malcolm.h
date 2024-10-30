/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:11:09 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/30 06:15:07 by ffarkas          ###   ########.fr       */
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

# include <arpa/inet.h>
# include <sys/socket.h>
# include <netdb.h>
# include <ifaddrs.h>
# include <netinet/in.h>
# include <net/if.h>

# define BLUE   "\033[0;34m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define YELLOW "\033[0;33m"
# define NC     "\033[0m"

# define VALID          1
# define NON_VALID      -1
# define MSG_PRINTED    3

# define IPv4_LENGTH    16
# define IPv4_BINLENGTH 4
# define MAC_BINLENGTH  6
# define MAX_HOSTNAME   253
# define MAX_INTERFACE  16

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

typedef struct s_malcolm
{
	t_options	options;
	t_device	source;
	t_device	target;
	char		interface[MAX_INTERFACE];
}	t_malcolm;

int		print_args_error(const char *msg, ...);
int		print_usage(char *prog_name, int status);
int		check_uid(void);

int		parse_args(t_malcolm *malcolm, int ac, char **av);

int		is_valid_mac(char *input, t_device *device);

int		is_valid_ipv4_or_hostname(char *input, t_device *device, int pos);

int		fetch_interface(t_malcolm *malcolm);

int		spoof_run(t_malcolm *malcolm);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:51:56 by ffarkas           #+#    #+#             */
/*   Updated: 2024/11/01 08:46:04 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

char	*fetch_time(void)
{
	static char	time_buff[20];
	time_t		now;
	struct tm	*local;

	now = time(NULL);
	local = localtime(&now);
	strftime(time_buff, sizeof(time_buff), "%Y-%m-%d %H:%M:%S", local);
	return (time_buff);
}

int	print_args_error(const char *msg, ...)
{
	va_list	args_list;

	va_start(args_list, msg);
	vdprintf(STDERR_FILENO, msg, args_list);
	va_end(args_list);
	return (NON_VALID);
}

int	check_uid(void)
{
	if (getuid() == 0)
		return (VALID);
	dprintf(STDERR_FILENO, "%sft_malcolm:%s user not root\n", RD, NC);
	return (NON_VALID);
}

int	print_usage(char *prog_name, int status)
{
	dprintf(STDOUT_FILENO,
		"\n%sUsage:%s\n"
		"  %s source_ip source_mac target_ip target_mac [ options ]\n"
		"\n%sOptions:%s\n"
		"  -v               Print detailed packet information.\n"
		"  -g               Send a gratuitous ARP broadcast.\n"
		"  -t TIMEOUT       Set a timeout (in seconds) to wait for an ARP request.\n"
		"                   Values from 1 to 300 are accepted.\n"
		"  --help           Display this help message and exit.\n"
		"\n%sArguments:%s\n"
		"  + source_ip      IP address that ft_malcolm will spoof.\n"
		"  + source_mac     MAC address that ft_malcolm will use for spoofing.\n"
		"  + target_ip      IP address of the machine to be impersonated.\n"
		"  + target_mac     MAC address of the machine to be impersonated.\n\n"
		, GR, NC, prog_name, YL, NC, YL, NC);
	return (status);
}

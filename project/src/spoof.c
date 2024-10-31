/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spoof.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:48:56 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/31 02:01:38 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

int	listen_to_broadcast(t_malcolm *malcom)
{
	unsigned char	buffer[]
}

int	spoof_run(t_malcolm *malcolm)
{
	if (fetch_interface(malcolm) == NON_VALID)
		return (print_args_error("%sft_malcolm:%s no matching interface found\n", RD, NC));
	
	if (setup_socket(malcolm) == NON_VALID)
		return (NON_VALID);

	while (g_sig_status)
	{
		sleep(1);
	}
	return (VALID);
}

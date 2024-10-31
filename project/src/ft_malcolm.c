/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:12:05 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/31 00:05:11 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

volatile sig_atomic_t	g_sig_status = 1;

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
		g_sig_status = 0;
}

int	main(int ac, char **av)
{
	t_malcolm	malcolm;

	// if (check_uid() != VALID)
	// 	return (EXIT_FAILURE);
	
	if (ac < 5)
		return (print_usage(av[0], EXIT_FAILURE));

	ft_memset(&malcolm, 0, sizeof(malcolm));
	if (parse_args(&malcolm, ac, av) == NON_VALID)
		return (EXIT_FAILURE);

	printf("%s | %s\n", malcolm.source.hostname, malcolm.target.hostname);
	printf("verbose: %d | gratuitous: %d | timeout: %d\n", malcolm.options.verbose, malcolm.options.gratuitous, malcolm.options.timeout);

	signal(SIGINT, &sig_handler);

	if (spoof_run(&malcolm) == NON_VALID)
		return (EXIT_FAILURE);

	dprintf(STDERR_FILENO, "\n%sft_malcolm:%s exiting gracefully...\n", GR, NC);
	return (EXIT_SUCCESS);
}

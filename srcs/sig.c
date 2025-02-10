/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:32:20 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/10 08:32:20 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/chardefs.h>

void	init_sig()
{
	int i;
	struct sigaction sa[2];

	i = -1;
	while (++i < 2)
	{
		ft_memset(&(sa[i]), 0, sizeof(sa[i]));
    	(sa[i]).sa_flags = SA_RESTART;	
    	sigemptyset(&((sa[i]).sa_mask));
	}
    (sa[0]).sa_handler = handle_sigint;
	sigaction(SIGINT, &(sa[0]), NULL);
    (sa[1]).sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &(sa[1]), NULL);
}

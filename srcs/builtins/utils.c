/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:41 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/24 14:32:41 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	err_msg_cmd(char *cmd, char *arg, char *msg, int code)
{
	ft_put_s_fd(cmd, 2);
	ft_put_s_fd(": ", 2);
	ft_put_s_fd(msg, 2);
	if (arg)
	{
		ft_put_s_fd(": ", 2);
		ft_putendl_fd(arg, 2);
	}
	return (code);
}

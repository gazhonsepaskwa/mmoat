/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:10:06 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/19 09:10:06 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>

int	is_dir(char *str)
{
	struct stat	st;

	if (stat(str, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

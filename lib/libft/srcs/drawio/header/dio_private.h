/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dio_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:06:54 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/24 11:06:54 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIO_PRIVATE
# define DIO_PRIVATE

int	draw_rect(int fd, int id, t_dio_elem *elem);
int	draw_arrow(int fd, int id, t_dio_elem *elem);

#endif

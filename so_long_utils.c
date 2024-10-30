/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:45:17 by root              #+#    #+#             */
/*   Updated: 2024/10/27 15:29:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	handle_error_close(char *str, int fd)
{
	perror(str);
	if (fd >= 0)
		close(fd);
	exit(EXIT_FAILURE);
}

void	handle_error_close_free(char *str, int fd, char **map)
{
	free_dbl_tab(map);
	if (fd >= 0)
		close(fd);
	perror(str);
	exit(EXIT_FAILURE);
}

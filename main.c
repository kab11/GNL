/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:02:45 by kblack            #+#    #+#             */
/*   Updated: 2018/09/13 21:08:51 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Made by: csinglet
*/

#include "get_next_line.h"
#include "libft/libft.h"

#include <stdio.h>

int		main(int argc, char *argv[])
{
		char *line[90];
		int		fd;
		int		fd2;
		int		index;
		int		ret;

		line[0] = NULL;
		index = 0;
		ret = 0;
		if (argc > 1)
		{
			fd = open(argv[1]);
			fd2 = open(argv[2]);
			while ((ret = get_next_line(fd, &line[index])))
			{
				// printf("index: %d\n", index);
				printf("line1:   %-5s\n", line[index]);
				index++;
			}
		}
		printf("ret: %d\n", ret);
		return (0);
}

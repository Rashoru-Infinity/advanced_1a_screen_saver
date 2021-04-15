/* ************************************************************************** */
/*                                                                            */
/*   debug.c                                                                  */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/14 23:17:13 by Keita Hagiwara                           */
/*   Updated: 2021/04/14 23:17:13 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <scr.h>
#include <stdlib.h>

int main(void)
{
	char **map;
	if (!(map = set_map("sample.map")))
	{
		printf("fail to set map\n");
		exit(0);
	}
	if (check_map(map) == FAIL)
	{
		printf("invalid map\n");
		exit(0);
	}
	printf("no error in map file");
}

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
#include <status.h>
#include <two_dimensions.h>
#include <vla.h>

int main(void)
{
	arg_t *arg;
	char *lines;

	if (!(lines = read_config("lang_model.conf")))
	{
		printf("fail to read file\n");
		return 0;
	}
	printf("%s\n", lines);
	if (!(arg = set_config(lines)))
	{
		printf("fail to set config\n");
		return 0;
	}
	printf("success\n");
	do_actions(arg);
	return 0;
}

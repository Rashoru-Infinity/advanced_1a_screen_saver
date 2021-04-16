/* ************************************************************************** */
/*                                                                            */
/*   set_map.c                                                                */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/15 21:11:02 by Keita Hagiwara                           */
/*   Updated: 2021/04/15 21:11:02 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#include <scr.h>
#include <stdlib.h>
#include <stdio.h>

char **set_map(const char *file_name)
{
	extstr_t content;
	char **map;

	if (!file_name || extstr_init(&content) == FAIL)
		return NULL;
	if (read_file(file_name, &content) == FAIL)
	{
		free(content.str);
		return NULL;
	}
	content.str[content.curr_size] = 0;
	extstr_append(&content, "\0", 1);
	if (!(map = ft_split(content.str, '\n')))
	{
		free(content.str);
		return NULL;
	}
	free(content.str);
	return map;
}

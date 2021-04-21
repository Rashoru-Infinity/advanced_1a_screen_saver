/* ************************************************************************** */
/*                                                                            */
/*   read_config.c                                                            */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/04/21 14:31:52 by al19136                                  */
/*   Updated: 2021/04/21 14:31:52 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>
#include <scr.h>

char *read_config(const char *file_name)
{
	extstr_t content;

	if (!file_name || extstr_init(&content) == FAIL)
		return NULL;
	if (read_file(file_name), &content == FAIL)
	{
		free(content.str);
		return NULL;
	}
	content.str[content.curr_size] = 0;
	if (extstr_append(&content, "\0", 1) == FAIL)
	{
		free(content.str);
		return NULL;
	}
	return content.str;
}

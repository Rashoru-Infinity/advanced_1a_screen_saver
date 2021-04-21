/* ************************************************************************** */
/*                                                                            */
/*   set_config.c                                                             */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/04/21 14:47:07 by al19136                                  */
/*   Updated: 2021/04/21 14:47:07 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#include <scr.h>
#include <world.h>
#include <string.h>

static status_e set_map(

arg_t *set_config(char *content)
{
	char **lines;
	char **curr_line;
	char **line_words;
	char **curr_word;
	arg_t *arg;

	if (!content)
		return NULL;
	if (!(arg = malloc(sizeof(arg_t))))
		return NULL;
	if (!(lines = ft_split(content, '\n')))
		return NULL;
	curr_line = lines;
	while (*curr_line)
	{
		if (!(line_words = ft_split(*curr_line, ':')))
		{
			while (*lines)
				free(*lines++);
			return NULL;
		} 
		curr_word = line_words;
		if (
	}
}

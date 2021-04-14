/* ************************************************************************** */
/*                                                                            */
/*   extstr.c                                                                 */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/14 16:27:37 by Keita Hagiwara                           */
/*   Updated: 2021/04/14 16:27:37 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#include <scr.h>
#include <stdlib.h>
#include <string.h>

status_e extstr_init(extstr_t *str)
{
	if (!str)
		return FAIL;
	if (!(str->str = malloc(sizeof(char) * 10)))
		return FAIL;
	str->real_size = 10;
	str->curr_size = 0;
	return SUCCESS;
}

static status_e extstr_extend(extstr_t *str)
{
	char *new_array;

	if (!str)
		return FAIL;
	if (!(new_array = realloc(str->str, sizeof(char) * str->real_size * 2)))
		return FAIL;
	str->str = new_array;
	return SUCCESS;
}

status_e extstr_append(extstr_t *str, char *new_str, size_t len)
{
	if (!new_str || !str)
		return FAIL;
	if (str->curr_size + len >= str->real_size)
	{
		if (extstr_extend(str) == FAIL)
			return FAIL;
	}
	memcpy(str->str + str->curr_size, new_str, len);
	str->curr_size += len;
	return SUCCESS;
}

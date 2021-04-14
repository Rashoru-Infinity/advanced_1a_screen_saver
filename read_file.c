/* ************************************************************************** */
/*                                                                            */
/*   read_file.c                                                              */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/14 16:09:41 by Keita Hagiwara                           */
/*   Updated: 2021/04/14 16:09:41 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <scr.h>

status_e read_file(const char *file_name, extstr_t *content)
{
	FILE *fp;
	const size_t BUF_SIZE = 1024;
	char buf[BUF_SIZE];
	size_t read_size;

	if (!file_name || !content)
		return FAIL;
	if (!(fp = fopen(file_name, "r", fp)))
		return FAIL;
	while (!feof(fp))
	{
		memset(buf, 0x1a, BUF_SIZE);
		read_size = fread(buf, BUF_SIZE, fp);
		if (ferror(fp))
			return FAIL;
		if (extstr_append(content, buf))
			return FAIL;
	}
	fclose(fp);
	return SUCCESS;
}

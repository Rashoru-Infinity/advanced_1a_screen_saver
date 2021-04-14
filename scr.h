/* ************************************************************************** */
/*                                                                            */
/*   scr.h                                                                    */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/14 16:09:59 by Keita Hagiwara                           */
/*   Updated: 2021/04/14 16:09:59 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
#define TYPE_H
//#include <BaseTsd.h>
#define SIZE_T size_t

typedef enum {
	SUCCESS,
	FAIL
}		status_e;

typedef struct {
	char	*str;
	size_t	real_size;
	size_t	curr_size;
}		extstr_t;

status_e extstr_init(extstr_t *str);
status_e extstr_append(extstr_t *str, char *new_str, size_t len);

status_e read_file(const char *file_name, extstr_t *content);

#endif

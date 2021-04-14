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
status_e extstr_append(extstr *str, char *new_str);

#endif

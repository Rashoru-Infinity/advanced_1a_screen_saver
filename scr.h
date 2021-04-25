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

#ifndef SCR_H
#define SCR_H
#include <BaseTsd.h>
#include <stddef.h>
#include <world.h>
#include <status.h>

typedef struct {
	char	*str;
	size_t	real_size;
	size_t	curr_size;
}		extstr_t;

status_t extstr_init(extstr_t *str);
status_t extstr_append(extstr_t *str, char *new_str, size_t len);

status_t read_file(const char *file_name, extstr_t *content);

status_t check_map(char **map);

char **read_map(const char *file_name);

char **ft_split(char const *s, char c);
void ft_split_clear(char **strs);

char *read_config(const char *s);
arg_t *set_config(char *lines);

#endif

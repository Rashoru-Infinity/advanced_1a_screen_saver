/* ************************************************************************** */
/*                                                                            */
/*   vla.h                                                                    */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/05/08 20:02:02 by al19136                                  */
/*   Updated: 2021/05/08 20:02:02 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef VLA_H
#define VLA_H
#include <stdlib.h>
#include <stdbool.h>
#include <status.h>

typedef	struct	s_array {
	void		**contents;
	size_t		size;
	size_t		real_size;
}				t_array;

status_t	array_init(t_array *original, void (*func)(t_array *), size_t init_size);
status_t	array_extend(t_array *original);
void		array_elements_clear(t_array *arr, bool freeable);
void		array_clear(t_array *arr, bool elemfreeable, bool freeable);

#endif

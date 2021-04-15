/* ************************************************************************** */
/*                                                                            */
/*   two_dimensions.h                                                         */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/15 21:47:45 by Keita Hagiwara                           */
/*   Updated: 2021/04/15 21:47:45 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWO_DIMENSIONS_H
#define TWO_DIMENSIONS_H

typedef struct {
	int x;
	int y;
}		int2d_t;

typedef struct {
	double x;
	double y;
}		double2d_t;

typedef struct {
	int2d_t point;
	int2d_list_t *next;
}		int2d_list_t;

void list_clear(int2d_list_t **head);

#endif

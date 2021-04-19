/* ************************************************************************** */
/*                                                                            */
/*   world.h                                                                  */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/04/19 23:55:11 by al19136                                  */
/*   Updated: 2021/04/19 23:55:11 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
#define WORLD_H
#include <scr.h>
#include <stdlib.h>
#include <two_dimensions.h>

typedef struct pattern_s {
	void (*func)(void *);
	void *arg;
	struct pattern_s *next;
} pattern_t;

typedef struct {
	void (*func)(void *);
	void *arg;
	struct pattern_s *next;
} action_t;

typedef struct {
	int loop_counter;
	double2d_t pos;
	double ahead_remain;
	double rturn_remain;
	action_t routine;
} player_t;

#endif

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

typedef struct {
	double2d_t pos;
	double heading;
} player_t;

typedef struct action_list_s {
	void (*func)(player_t *);
	struct action_list_s *next;
} action_list_t;

typedef struct pattern_s {
	char *name;
	action_list_t *ptn;
	struct pattern_s *next;
} pattern_t;

typedef struct {
	player_t *player;
	char **map;
	pattern_t *pattern_list;
} arg_t;

typedef struct {
	char **map;
	player_t *player;
}	config_t;

void ahead(arg_t *arg);
void back(arg_t *arg);
void turnR(arg_t *arg);
void turnL(arg_t *arg);
void do_actions(arg_t *arg);

#endif

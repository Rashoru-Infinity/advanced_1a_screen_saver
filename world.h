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
#include <stdlib.h>
#include <two_dimensions.h>
#include <vla.h>
#include <stdbool.h>
#include <windows.h>

typedef struct {
	double2d_t pos;
	double heading;
} player_t;

typedef struct action_list_s {
	void (*func)(void *);
	struct action_list_s *next;
} action_list_t;

typedef struct pattern_s {
	char *name;
	action_list_t *ptn;
	struct pattern_s *next;
} pattern_t;

typedef struct {
	player_t player;
	char **map;
	t_array *entry_point;
	t_array *pattern_list;
	bool end;
	HDC hdc;
	HGLRC hrc;
	HWND hWnd;
	int2d_t scr_size;
} arg_t;

void ahead(void *arg);
void back(void *arg);
void turnR(void *arg);
void turnL(void *arg);
void exit_func(void *arg);
unsigned __stdcall do_actions(void *arg);

#endif

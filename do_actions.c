/* ************************************************************************** */
/*                                                                            */
/*   do_actions.c                                                             */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/04/21 13:31:58 by al19136                                  */
/*   Updated: 2021/04/21 13:31:58 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>
#include <scr.h>
#include <math.h>
#include <two_dimensions.h>
#include <string.h>
#include <stdio.h>

void ahead(void *ag)
{
	arg_t *arg;

	arg = (arg_t *)ag;
	//try to visit
	double2d_t new_point;
	//map index
	int2d_t map_point;
	int2d_t diag;
	char **line;
	size_t curr_y;

	new_point.x = arg->player.pos.x + 0.3 * cos(arg->player.heading);
	new_point.y = arg->player.pos.y + 0.3 * sin(arg->player.heading);
	map_point.x = floor(new_point.x);
	map_point.y = floor(new_point.y);
	line = arg->map;
	curr_y = 0;
	while (line)
	{
		if (curr_y == (size_t)map_point.y)
			break;
		++line;
		++curr_y;
	}
	if (curr_y == (size_t)map_point.y)
	{
		if (map_point.x >= 0 && strlen(*line) > (size_t)map_point.x)
		{
			if (arg->map[map_point.y][map_point.y] == 'X' || arg->map[map_point.y][map_point.x] == ' ')
				return ;
			if (fabs(floor(arg->player.pos.x) - new_point.x) > 1 && fabs(floor(arg->player.pos.y) - new_point.y) > 1)
			{
				if (fabs(arg->player.heading) <= M_PI / 2)
					diag.x = (int)(arg->player.pos.x + 1);
				else
					diag.x = (int)(arg->player.pos.x - 1);
				diag.y = new_point.y;
				if (arg->map[diag.y][diag.x] == 'X' || arg->map[diag.y][diag.x] == ' ')
					return ;
				diag.x = (int)(arg->player.pos.x);
				if (fabs(arg->player.heading) > 0)
					diag.y = (int)(arg->player.pos.y + 1);
				else
					diag.y = (int)(arg->player.pos.y - 1);
				if (arg->map[diag.y][diag.x] == 'X' || arg->map[diag.y][diag.x] == ' ')
					return ;
			}
			arg->player.pos.x = new_point.x;
			arg->player.pos.y = new_point.y;
		}
	}
}

void back(void *ag)
{
	arg_t *arg;

	arg = (arg_t *)ag;
	//try to visit
	double2d_t new_point;
	//map index
	int2d_t map_point;
	int2d_t diag;
	char **line;
	size_t curr_y;

	new_point.x = arg->player.pos.x - 0.3 * cos(arg->player.heading);
	new_point.y = arg->player.pos.y - 0.3 * sin(arg->player.heading);
	map_point.x = floor(new_point.x);
	map_point.y = floor(new_point.y);
	line = arg->map;
	curr_y = 0;
	while (line)
	{
		if (curr_y == (size_t)map_point.y)
			break;
		++line;
	}
	if (curr_y == (size_t)map_point.y)
	{
		if (map_point.x >= 0 && strlen(*line) > (size_t)map_point.x)
		{
			if (arg->map[map_point.y][map_point.y] == 'X' || arg->map[map_point.y][map_point.x] == ' ')
				return ;
			if (fabs(floor(arg->player.pos.x) - new_point.x) > 1 && fabs(floor(arg->player.pos.y) - new_point.y) > 1)
			{
				if (fabs(arg->player.heading) >= M_PI / 2)
					diag.x = (int)(arg->player.pos.x + 1);
				else
					diag.x = (int)(arg->player.pos.x - 1);
				diag.y = new_point.y;
				if (arg->map[diag.y][diag.x] == 'X' || arg->map[diag.y][diag.x] == ' ')
					return ;
				diag.x = (int)(arg->player.pos.x);
				if (fabs(arg->player.heading) < 0)
					diag.y = (int)(arg->player.pos.y + 1);
				else
					diag.y = (int)(arg->player.pos.y - 1);
				if (arg->map[diag.y][diag.x] == 'X' || arg->map[diag.y][diag.x] == ' ')
					return ;
			}
			arg->player.pos.x = new_point.x;
			arg->player.pos.y = new_point.y;
		}
	}
}

void turnR(void *ag)
{
	arg_t *arg;

	arg = (arg_t *)ag;
	arg->player.heading -= M_PI / 60;
	arg->player.heading = fmod(arg->player.heading, M_PI);
}

void turnL(void *ag)
{
	arg_t *arg;

	arg = (arg_t *)ag;
	arg->player.heading += M_PI / 60;
	arg->player.heading = fmod(arg->player.heading, M_PI);
}

void do_actions(arg_t *arg)
{
	pattern_t *pattern;
	action_list_t *action;

	while (1)
	{
		for (size_t i = 0;i < arg->entry_point->size;++i)
		{
			pattern = arg->entry_point->contents[0];
			action = pattern->ptn;
			while (action)
			{
				(*(action->func))(arg);
				//render
				action = action->next;
				printf("position: (%f, %f), heading: %f\n", arg->player.pos.x, arg->player.pos.y, arg->player.heading);
			}
			if (!pattern)
				break;
		}
	}
}

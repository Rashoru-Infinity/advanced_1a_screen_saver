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

#include <windows.h>
#include <world.h>
#include <scr.h>
#include <math.h>
#include <two_dimensions.h>
#include <string.h>
#include <stdio.h>
#include <gl/gl.h>

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
				if (arg->player.heading > 0)
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
	arg->player.heading += M_PI / 60;
	arg->player.heading = fmod(arg->player.heading, 2 * M_PI);
	if (arg->player.heading > M_PI)
		arg->player.heading -= 2 * M_PI;
	if (arg->player.heading < -M_PI)
		arg->player.heading += 2 * M_PI;
}

void turnL(void *ag)
{
	arg_t *arg;

	arg = (arg_t *)ag;
	arg->player.heading -= M_PI / 60;
	arg->player.heading = fmod(arg->player.heading, 2 * M_PI);
	if (arg->player.heading > M_PI)
		arg->player.heading -= 2 * M_PI;
	if (arg->player.heading < -M_PI)
		arg->player.heading += 2 * M_PI;
}

void exit_func(void *arg)
{
	(void)arg;
	return;
}

unsigned __stdcall do_actions(void *ag)
{
	action_list_t *action;
	arg_t *arg;

	arg = (arg_t *)ag;
	enable_gl(&(arg->hdc), &(arg->hrc));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, arg->scr_size.x, 0, arg->scr_size.y, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(0.0, 0.0, 0.0);
	glViewport(0, 0, arg->scr_size.x, arg->scr_size.y);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.4, 1.0, 1.0);
	while (!arg->end)
	{
		for (size_t i = 0;i < arg->entry_point->size;++i)
		{
			if (arg->end)
				break;
			action = ((action_list_t *)(arg->entry_point->contents[i]));
			while (action)
			{
				if (arg->end)
					break;
				render(arg);
				if (action->func != exit_func)
					Sleep(1000);
				(*(action->func))(arg);
				if (action->func == ahead)
					printf("ahead:");
				else if (action->func == back)
					printf("back:");
				else if (action->func == turnR)
					printf("turnR:");
				else if (action->func == turnL)
					printf("turnL:");
				else if (action->func == exit_func)
					printf("exit:");
				printf("(0x%x)\n", (size_t)(action->func));
				action = action->next;
			}
		}
	}
	return 0;
}

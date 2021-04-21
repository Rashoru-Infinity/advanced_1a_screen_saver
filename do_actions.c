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

void ahead(player_t *player)
{
	player->pos.x += 0.3 * cos(player->heading);
	player->pos.y += 0.3 * sin(player->heading);
}

void back(player_t *player)
{
	player->pos.x -= 0.3 * cos(player->heading);
	player->pos.y -= 0.3 * sin(player->heading);
}

void turnR(player_t *player)
{
	player->heading -= M_PI / 60;
	player->heading = fmod(player->heading, M_PI);
}

void turnL(player_t *player)
{
	player->heading += M_PI / 60;
	player->heading = fmod(player->heading, M_PI);
}

void do_actions(arg_t *arg)
{
	action_list_t *action;
	action_list_t *entry_point;

	entry_point = arg->actions;
	while (1)
	{
		action = arg->actions;
		while (action)
		{
			(*(action->func))(arg->player);
			//render
			action = action->next;
		}
		action = entry_point;
	}
}

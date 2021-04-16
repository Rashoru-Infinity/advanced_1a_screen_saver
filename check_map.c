/* ************************************************************************** */
/*                                                                            */
/*   check_map.c                                                              */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/15 21:26:49 by Keita Hagiwara                           */
/*   Updated: 2021/04/15 21:26:49 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#include <scr.h>
#include <string.h>
#include <stdlib.h>
#include <two_dimensions.h>
#include <stdio.h>

static status_e check_size(char **map)
{
	char *p;
	size_t height;

	p = *map;
	height = 0;
	while (p)
	{
		if (height++ > 10)
			return FAIL;
		if (strlen(p) > 10)
			return FAIL;
		p = *(++map);
	}
	return SUCCESS;
}

static status_e check_str(char **map)
{
	size_t offset;
	char *p;
	int player_count;

	p = *map;
	player_count = 0;
	while (p)
	{
		offset = 0;
		while (p[offset])
		{
			if (p[offset] != 'O' && p[offset] != 'X' && p[offset] != 'N' && p[offset] != 'S'
			&& p[offset] != 'E' && p[offset] != 'W')
				return FAIL;
			if (p[offset] != 'O' && p[offset] != 'X')
				++player_count;
			if (player_count > 1)
				return FAIL;
			++offset;
		}
		p = *(++map);
	}
	return SUCCESS;
}

static status_e queue_insert(int2d_list_t **queue_last, int x, int y)
{
	int2d_list_t *tmp;

	if (!(tmp = malloc(sizeof(int2d_list_t))))
		return FAIL;
	tmp->point.x = x;
	tmp->point.y = y;
	(*queue_last)->next = tmp;
	*queue_last = tmp;
	return SUCCESS;
}

static status_e bfs_map(char **map, int **vst_stat, size_t map_height)
{
	size_t curr_height;
	char *s;
	size_t curr_width;
	int2d_list_t *queue;
	int2d_list_t *tmp;
	int2d_list_t *queue_last;

	curr_height = 0;
	//search player
	while (curr_height < map_height)
	{
		s = map[curr_height];
		curr_width = 0;
		while (s[curr_width])
		{
			if (s[curr_width] != 'O' && s[curr_width] != 'X' && s[curr_width] != ' ')
				break;
			curr_width++;
		}
		if (s[curr_width] && s[curr_width] != 'O' && s[curr_width] != 'X' && s[curr_width] != ' ')
			break;
		curr_height++;
	}
	if (!(queue = malloc(sizeof(queue))))
		return FAIL;
	queue->point.x = curr_width;
	queue->point.y = curr_height;
	queue->next = NULL;
	queue_last = queue;
	while (queue)
	{
		printf("aaa\n");
		//check whther the map is closed or not
		//array index check on x axis
		printf("%s\n", map[queue->point.y]);
		if (queue->point.x == 0 || (size_t)queue->point.x + 1 == strlen(map[queue->point.y]))
		{
			list_clear(&queue);
			return FAIL;
		}
		//array index check on y axis
		if (queue->point.y == 0 || (size_t)queue->point.y + 1 == map_height)
		{
			list_clear(&queue);
			return FAIL;
		}
		//upward check
		if (strlen(map[queue->point.y - 1]) <= (size_t)queue->point.x)
		{
			list_clear(&queue);
			return FAIL;
		}
		//downward check
		if (strlen(map[queue->point.y + 1]) <= (size_t)queue->point.x)
		{
			list_clear(&queue);
			return FAIL;
		}
		//insert location on the map where bfs is not visited
		//try to visit upward
		if (vst_stat[queue->point.y - 1][queue->point.x] == 0)
		{
			if (queue_insert(&queue_last, queue->point.x, queue->point.y - 1) == FAIL)
			{
				list_clear(&queue);
				return (FAIL);
			}
			vst_stat[queue->point.y - 1][queue->point.x] = 1;
		}
		//try to visit downward
		if (vst_stat[queue->point.y + 1][queue->point.x] == 0)
		{
			if (queue_insert(&queue_last, queue->point.x, queue->point.y + 1) == FAIL)
			{
				list_clear(&queue);
				return (FAIL);
			}
			vst_stat[queue->point.y + 1][queue->point.x] = 1;
		}
		//toward the left
		if (vst_stat[queue->point.y][queue->point.x - 1] == 0)
		{
			if (queue_insert(&queue_last, queue->point.x - 1, queue->point.y) == FAIL)
			{
				list_clear(&queue);
				return (FAIL);
			}
			vst_stat[queue->point.y][queue->point.x - 1] = 1;
		}
		//toward the right
		if (vst_stat[queue->point.y][queue->point.x + 1] == 0)
		{
			if (queue_insert(&queue_last, queue->point.x + 1, queue->point.y) == FAIL)
			{
				list_clear(&queue);
				return (FAIL);
			}
			vst_stat[queue->point.y][queue->point.x + 1] = 1;
		}
		tmp = queue;
		queue = queue->next;
		free(tmp);
		printf("bbb\n");
	}
	return SUCCESS;
}

static status_e check_closed(char **map)
{
	int **vst_stat;	//remembers visit status on the map
	char *s;
	char **map_cpy;
	size_t offset;
	size_t map_height;
	size_t curr_height;

	s = *map;
	map_cpy = map;
	map_height = 0;
	//count map height
	while (s)
	{
		map_height++;
		s = *(++map);
	}
	if (!(vst_stat = malloc(sizeof(int *) * map_height)))
		return FAIL;
	map = map_cpy;
	s = *map;
	curr_height = 0;
	while (s)
	{
		//free memory address in case that malloc failed
		if (!(vst_stat[curr_height] = malloc(sizeof(int) * strlen(s))))
		{
			//free memory address that was allocated in this function
			while (1)
			{
				if (curr_height == 0)
					break;
				free(vst_stat[curr_height-- - 1]);
			}
			free(vst_stat);
			printf("exited\n");
			return FAIL;
		}
		offset = 0;
		while (s[offset])
		{
			switch(s[offset])
			{
			//blank
			case 'O':
				vst_stat[curr_height][offset++] = 0;
				break;
			//wall
			case 'X':
				vst_stat[curr_height][offset++] = 1;
				break;
			//vacuum
			case ' ':
				vst_stat[curr_height][offset++] = 2;
				break;
			//it may indicates player
			default:
				vst_stat[curr_height][offset++] = 1;
			}
		}
		curr_height++;
		s = *(++map);
	}
	map = map_cpy;
	//check the player is surrounded by wall
	return bfs_map(map, vst_stat, map_height);
}

status_e check_map(char **map)
{
	if (!map)
		return FAIL;
	if (check_size(map) == FAIL)
		return FAIL;
	if (check_str(map) == FAIL)
		return FAIL;
	if (check_closed(map) == FAIL)
		return FAIL;
	return SUCCESS;
}

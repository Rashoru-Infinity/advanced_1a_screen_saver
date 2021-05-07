/* ************************************************************************** */
/*                                                                            */
/*   render.c                                                                 */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/05/07 22:49:04 by al19136                                  */
/*   Updated: 2021/05/07 22:49:04 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#include <scr.h>
#include <gl/gl.h>
#include <world.h>
#include <two_dimensions.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <stdio.h>

static void move_point(double2d_t *ray, double curr_rad)
{
	double2d_t delta;

	memset(&delta, '\0', sizeof(double2d_t));
	if (cos(curr_rad) >= 0)
		delta.x = floor(ray->x + 1) - ray->x;
	else
		delta.x = ceil(ray->x - 1) - ray->x;
	if (sin(curr_rad) >= 0)
		delta.y = floor(ray->y + 1) - ray->y;
	else
		delta.y = ceil(ray->y - 1) - ray->y;
	if (fabs(delta.y / delta.x) < fabs(tan(curr_rad)))
	{
		ray->y += delta.y;
		ray->x += delta.y / tan(curr_rad);
	}
	else
	{
		ray->x += delta.x;
		ray->y += delta.x * tan(curr_rad);
	}
}

static void extend_ray(double2d_t *ray, double curr_rad)
{
	if (fabs(get_min_rad(curr_rad)) < DBL_EPSILON)
		ray->x += floor(ray->x) + 1 - ray->x;
	else if (fabs(get_min_rad(curr_rad - M_PI)) < DBL_EPSILON)
		ray->x += floor(ray->x) - 1 - ray->x;
	else if (fabs(get_min_rad(curr_rad - M_PI / 2)) < DBL_EPSILON)
		ray->y += floor(ray->y) + 1 - ray->y;
	else if (fabs(get_min_rad(curr_rad + M_PI / 2)) < DBL_EPSILON)
		ray->y += floor(ray->y) - 1 - ray->y;
	else
		move_point(ray, curr_rad);
}

static void inc_rad(arg_t *arg, double *curr_rad, double heading)
{
	double step;
	double fov;

	fov = (double)66/ (double)180 * M_PI;
	step = sin(fov / 2) * 2 / arg->scr_size.x;
	*curr_rad = heading + atan2(cos(fov / 2) * tan(*curr_rad - heading) + step, cos(fov / 2));
}

static double get_camera_dist(arg_t *arg, double curr_rad, double2d_t ray)
{
	double euclid_dist;
	double delta_rad;

	euclid_dist = sqrt(pow(arg->player.pos.x - ray.x, 2) + pow(arg->player.pos.y - ray.y, 2));
	delta_rad = get_min_rad(curr_rad - arg->player.heading);
	return euclid_dist * cos(delta_rad);
}

static int check_obj(arg_t *arg, double curr_rad, double2d_t ray, double2d_t prev_ray, double *camera_dist)
{
	double2d_t point;

	if (floor(ray.x) - floor(prev_ray.x) > 0.5)
	{
		point.x = floor(ray.x) + 0.5;
		point.y = floor(ray.y) + 0.5;
	}
	else if (ceil(ray.x) - ceil(prev_ray.x) < -0.5)
	{
		point.x = ceil(ray.x) - 0.5;
		point.y = floor(ray.y) + 0.5;
	}
	else if (floor(ray.y) - floor(prev_ray.y) > 0.5)
	{
		point.x = floor(ray.x) + 0.5;
		point.y = floor(ray.y) + 0.5;
	}
	else if (ceil(ray.y) - ceil(prev_ray.y) < -0.5)
	{
		point.x = floor(ray.x) + 0.5;
		point.y = ceil(ray.y) - 0.5;
	}
	if (arg->map[(int)(floor(point.y))][(int)(floor(point.x))] == 'X')
	{
		//printf("%f, %f -> ", ray.y, ray.x);
		//printf("%d, %d : ", (int)(floor(ray.y)), (int)(floor(ray.x)));
		//printf("%c\n", arg->map[(int)(floor(ray.y))][(int)(floor(ray.x))]);
		*camera_dist = get_camera_dist(arg, curr_rad, ray);
	       return 0;	
	}
	return 1;
}

static void draw_wall(arg_t *arg, double camera_dist, int px_w)
{
	//printf("%f\n", 0.5 / camera_dist * arg->scr_size.y);
	//printf("%f\n", camera_dist);
	glBegin(GL_LINES);
		if (camera_dist > 1.0)
		{
			glVertex2f(px_w, arg->scr_size.y / 2 - 0.5 / camera_dist * arg->scr_size.y);
			glVertex2f(px_w, arg->scr_size.y / 2 + 0.5 / camera_dist * arg->scr_size.y);
		}
		else
		{
			glVertex2f(px_w, 0);
			glVertex2f(px_w, arg->scr_size.y);
		}
	glEnd();
}

static void raycast(arg_t *arg)
{
	double rad;
	int px_w;
	double2d_t ray;
	double2d_t prev_ray;
	double camera_dist;

	rad = get_min_rad(arg->player.heading - (double)33 / (double)180 * M_PI);
	px_w = 0;
	while (px_w < arg->scr_size.x)
	{
		memcpy(&ray, &(arg->player.pos), sizeof(double2d_t));
		do
		{
			memcpy(&prev_ray, &ray, sizeof(double2d_t));
			extend_ray(&ray, rad);
		}while (check_obj(arg, rad, ray, prev_ray, &camera_dist));
		draw_wall(arg, camera_dist, px_w);
		inc_rad(arg, &rad, arg->player.heading);
		++px_w;
	}
}

void render(arg_t *arg)
{
	glClear(GL_COLOR_BUFFER_BIT);
	raycast(arg);
	SwapBuffers(arg->hdc);
}

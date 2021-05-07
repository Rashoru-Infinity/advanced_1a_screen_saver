/* ************************************************************************** */
/*                                                                            */
/*   radian.c                                                                 */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/05/07 23:08:45 by al19136                                  */
/*   Updated: 2021/05/07 23:08:45 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#include <scr.h>
#include <math.h>

double get_min_rad(double rad)
{
	rad = fmod(rad, M_PI * 2);
	if (rad < -M_PI)
		rad += 2 * M_PI;
	else if (rad > M_PI)
		rad -= 2 * M_PI;
	return rad;
}

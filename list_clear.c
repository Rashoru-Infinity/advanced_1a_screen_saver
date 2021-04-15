/* ************************************************************************** */
/*                                                                            */
/*   list_clear.c                                                             */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/16 00:22:06 by Keita Hagiwara                           */
/*   Updated: 2021/04/16 00:22:06 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#include <two_dimensions.h>

void list_clear(int2d_list_t **head)
{
	int2d_list_t *tmp;

	if (!head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

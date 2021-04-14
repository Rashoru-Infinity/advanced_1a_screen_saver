/* ************************************************************************** */
/*                                                                            */
/*   debug.c                                                                  */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/14 23:17:13 by Keita Hagiwara                           */
/*   Updated: 2021/04/14 23:17:13 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <scr.h>

int main(void)
{
	extstr_t content;

	extstr_init(&content);
	read_file("test.txt", &content);
	printf("%s\n", content.str);
}

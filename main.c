/* ************************************************************************** */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                           */
/*                                                                            */
/*   Created: 2021/04/28 16:10:18 by Keita Hagiwara                           */
/*   Updated: 2021/04/28 16:10:18 by Keita Hagiwara                           */
/*                                                                            */
/* ************************************************************************** */

#include <windows.h>
#include <scrnsave.h>
#include <gl/gl.h>
#include <process.h>
#include <stdio.h>
#include <scr.h>
#include <world.h>
#include <two_dimensions.h>

HDC hDC;
int2d_t scr_size;

arg_t *get_arg(const char *file_name)
{
	arg_t *arg;
	char *lines;

	if (!(lines = read_config(file_name)))
	{
		printf("fail to read file.\n");
		return NULL;
	}
	if (!(arg = set_config(lines)))
	{
		printf("fail to set configure.\n");
		free(lines);
		return NULL;
	}
	printf("%s\n", lines);
	free(lines);
	printf("success in configureing.\n");
	return arg;
}

BOOL APIENTRY RegisterDialogClasses(HANDLE hInst)
{
	return TRUE;
}

LRESULT APIENTRY ScreenSaverProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE render_th;
	static arg_t *arg;
	RECT rc;

	switch(msg)
	{
	case WM_CREATE:
		if (!(arg = get_arg("lang_model.conf")))
			exit(0);
		if (!(hDC = GetDC(hWnd)))
			exit(0);
		if (!(GetClientRect(hWnd, &rc)))
			exit(0);
		scr_size.x = rc.right - rc.left;
		scr_size.y = rc.bottom - rc.top;
		if (!(render_th = (HANDLE)_beginthreadex(NULL, 0, do_actions, arg, 0, NULL)))
			exit(0);
		break;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_DESTROY:
		

	return DefScreenSaverProc(hWnd, uMsg, wParam, lParam);
}

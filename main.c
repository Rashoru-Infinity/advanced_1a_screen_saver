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

arg_t *get_arg(const char *file_name, HWND hWnd)
{
	arg_t *arg;
	char *lines;
	RECT rc;

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
	if (!(arg->hdc = GetDC(hWnd)))
		return NULL;
	if (!(GetClientRect(hWnd, &rc)))
		return NULL;
	arg->scr_size.x = rc.right - rc.left;
	arg->scr_size.y = rc.bottom - rc.top;
	arg->hWnd = hWnd;
	free(lines);
	return arg;
}

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE render_th;
	static arg_t *arg;

	switch(uMsg)
	{
	case WM_CREATE:
		if (!(arg = get_arg("behavior.conf", hWnd)))
			exit(0);
		if (!(render_th = (HANDLE)_beginthreadex(NULL, 0, do_actions, arg, 0, NULL)))
			exit(0);
		break;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_DESTROY:
		arg->end = true;
		if (WaitForSingleObject(render_th, INFINITE) == (DWORD)0xffffffff)
			exit(0);
		CloseHandle(render_th);
		disable_gl(arg->hWnd, &(arg->hdc), &(arg->hrc));
		PostQuitMessage(0);
		return FALSE;
	default:
		break;
	}
	return DefScreenSaverProc(hWnd, uMsg, wParam, lParam);
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	(void)hDlg;
	(void)msg;
	(void)wParam;
	(void)lParam;
	return TRUE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
	(void)hInst;
	return TRUE;
}

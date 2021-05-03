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

static HANDLE draw_th;


BOOL RegisterDialogClasses(HANDLE hInst)
{
	return TRUE;
}

LRESULT APIENTRY ScreenSaverProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefScreenSaverProc(hWnd, uMsg, wParam, lParam);
}

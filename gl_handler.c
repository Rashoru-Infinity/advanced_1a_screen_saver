/* ************************************************************************** */
/*                                                                            */
/*   gl_handler.c                                                             */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/05/07 02:15:18 by al19136                                  */
/*   Updated: 2021/05/07 02:15:18 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#include <windows.h>
#include <gl/gl.h>
#include <stdlib.h>

void enable_gl(HDC *hdc, HGLRC *hrc)
{
	int format;

	PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),
	1,
	0
	| PFD_DRAW_TO_WINDOW
	| PFD_SUPPORT_OPENGL
	| PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	24,
	0, 0, 0, 0, 0, 0,
	0,
	0,
	0,
	0, 0, 0, 0,
	32,
	0,
	0,
	PFD_MAIN_PLANE,
	0,
	0, 0, 0
	};
	if (!(format = ChoosePixelFormat(*hdc, &pfd)))
		exit(0);
	if (!SetPixelFormat(*hdc, format, &pfd))
		exit(0);
	if (!(*hrc = wglCreateContext(*hdc)))
		exit(0);
	if (!wglMakeCurrent(*hdc, *hrc))
		exit(0);
}

void disable_gl(HWND hwnd, HDC *hdc, HGLRC *hrc)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(*hrc);
	ReleaseDC(hwnd, *hdc);
}

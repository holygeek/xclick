#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>

int old_x = -1, old_y = -1; // Previous mouse mosition
int new_x, new_y; // New mouse position
int x_delivered = 0, y_delivered = 0; // Last position where click was sent
Window window = 0;
Display *display;
Window window_returned;
int win_x, win_y;
unsigned int mask_return;

#define MOVEMENT_THRESHOLD 10

double distance(int x1, int y1, int x2, int y2) {
	int dx = x1 - x2;
	int dy = y1 - y2;
	return fabs(sqrt(dx * dx + dy * dy));
}

void get_mouse_pos(int *x, int *y) {
	XQueryPointer(display, window, &window_returned,
			&window_returned, x, y, &win_x, &win_y,
			&mask_return);
}

int mouse_moved(int ms) {
	get_mouse_pos(&old_x, &old_y);
	usleep(ms * 1000); // Change into microseconds
	get_mouse_pos(&new_x, &new_y);
	return old_x != new_x || old_y != new_y;
}

void click() {
	system("xdotool click 1");
}

int main(int argc, char *argv[]) {
	display = XOpenDisplay(NULL);
	if (!window)
		window = XRootWindow(display, XDefaultScreen(display));

	mouse_moved(300);
	printf("Press ctrl+c to stop\n");
	while(1) {
		while(!mouse_moved(300))
			;
		while(mouse_moved(100)) {
			continue;
		}
		if (!mouse_moved(300) && (x_delivered != new_x || y_delivered != new_y)) {
			double d = distance(x_delivered, y_delivered, new_x, new_y);
			if (d > MOVEMENT_THRESHOLD) {
				x_delivered = new_x;
				y_delivered = new_y;
				click();
			}
		}
	}

	XCloseDisplay(display);
	return 0;
}

// vim: ts=8 sts=8 sw=8 noexpandtab:

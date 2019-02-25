#include <GL/glut.h>
#include "controls_glut.h"
#include "objects_glut.h"
#include "define.h"

void keyboard_normal(unsigned char key, int x, int y)
{
    /* Surpress unused parameter compiler warning */
    UNUSED(x);
    UNUSED(y);

    if (key == VK_W ) {
        if(bar_left_y < height - bar_height) {
            bar_left_y += bar_speed;
        }
    }

    if (key == VK_S ) {
        if(bar_left_y > 0) {
            bar_left_y -= bar_speed;
        }
    }
}

void keyboard_special(int key, int x, int y)
{
    /* Surpress unused parameter compiler warning */
    UNUSED(x);
    UNUSED(y);

    if (key == GLUT_KEY_UP ) {
        if(bar_right_y < height - bar_height) {
            bar_right_y += bar_speed;
        }
    }

    if (key == GLUT_KEY_DOWN ) {
        if(bar_right_y > 0) {
            bar_right_y -= bar_speed;
        }
    }
}
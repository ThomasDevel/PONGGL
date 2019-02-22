#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<string.h>

/* Dimensions of window */
int width = 1000;
int height = 400;

/* (1000ms / 60 fps) -> framerate */
int interval = 1000 / 60;

/* Score of left and right player and the string in
 * which we will write and output the score to the screen.
*/
int score_left = 0;
int score_right = 0;
char score_string[256];

/* Loop variable */
unsigned int i;

/* Bars */
int bar_width = 20;
int bar_height = 160;
int bar_speed = 3;

float bar_left_x = 20.0f;
float bar_left_y = 50.0f;

float bar_right_x = width - bar_width - 20;
float bar_right_y = 50.0f;

void drawRect(float x, float y, float width, float height)
{
    /* Begin drawing of a quad */
    glBegin(GL_QUADS);
        /* Specify the four points of the quad */
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    /* Done drawing quad */
    glEnd();
}

void drawText(float x, float y, char *string)
{
    /* Specify the raster position for pixel operations */
    glRasterPos2f(x, y);

    /* Render each character in the string in the named bitmap font */
    for(i = 0; i<strlen(string); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

void draw(void)
{
    /* Bitwise OR of masks that indicate the buffers to be cleared.
     * There are four masks possible.
     *
     * GL_COLOR_BUFFER_BIT: Indicates the buffers currently enabled for color writing.
     * GL_DEPTH_BUFFER_BIT: Indicates the depth buffer.
    */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Replace the current matrix with the identity matrix */
    glLoadIdentity();

    /* Draw player bars */
    drawRect(bar_left_x, bar_left_y, bar_width, bar_height);
    drawRect(bar_right_x, bar_right_y, bar_width, bar_height);

    /* draw score text */
    sprintf(score_string, "%d : %d", score_left, score_right);
    drawText(width / 2 - 10, height - 30, score_string);

    /* Swap buffers of current window if double buffered */
    glutSwapBuffers();
}

void update(int value)
{
    glutTimerFunc(interval, update, 0);

    /* Redisplay frames */
    glutPostRedisplay();
}

void enable2D(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    /* initialze opengl via glut */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("PONG GAME");

    /* Register callback functions */
    glutDisplayFunc(draw);
    glutTimerFunc(interval, update, 0);

    /* 2d mode scene setup */
    enable2D(width, height);
    /* color to draw */
    glColor3f(1.0f, 1.0f, 1.0f);

    glutMainLoop();
    return 0;
}

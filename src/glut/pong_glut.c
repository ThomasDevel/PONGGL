#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

#include "define.h"
#include "pong_glut.h"
#include "objects_glut.h"
#include "controls_glut.h"
#include "view_glut.h"

/* (1000ms / 60 fps) -> framerate */
const int interval = 1000 / 60;
const int width = 1000;
const int height = 400;

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
    drawRect(bar_left_x, bar_left_y, BAR_WIDTH, bar_height);
    drawRect(bar_right_x, bar_right_y, BAR_WIDTH, bar_height);

    /* Draw the ball */
    drawCircle(ball_x - ball_size / 2, ball_y - ball_size / 2, BAR_WIDTH / 2);


    /* draw score text */
    sprintf(score_string, "%d : %d", score_left, score_right);
    drawText(width / 2 - 10, height - 30, score_string);

    /* Swap buffers of current window if double buffered */
    glutSwapBuffers();
}

void update(int value)
{
    /* Surpress unused parameter compiler warning */
    UNUSED(value);
    /* User input handling */
    /* Capture keystrokes to their ascii value */
    glutKeyboardFunc(keyboard_normal);
    /* Capture special keystrokes that have no corresponding ascii value */
    glutSpecialFunc(keyboard_special);

    /* Ball movement and collision */
    updateBall();

    /* Recall update after #interval milliseconds */
    glutTimerFunc(interval, update, 0);

    /* Redisplay frames */
    glutPostRedisplay();
}

void enable2D(int width, int height)
{
    glViewport(0, 0, width, height);
    /* GL_PROJECTION: Applies subsequent matrix operations to projection
     * matrix stack.
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* Multiply current matrix with an orthographic matrix */
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    /* GL_MODELVIEW: Applies subsequent matrix operations to modelview
     * matrix stack.
     */
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

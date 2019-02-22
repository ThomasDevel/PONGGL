#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<string.h>
#include<math.h>

/* Ascii keyboard codes */
#define VK_W    0x77
#define VK_S    0x73

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

/* Ball variables */
float ball_x = width /2;
float ball_y = height / 2;
float ball_dir_x = -1.0f;
float ball_dir_y = 0.0f;
unsigned int ball_size = 16;
unsigned ball_speed = 2;

void keyboard_normal(unsigned char key, int x, int y)
{
    if (key == VK_W ) { bar_left_y += bar_speed; }
    if (key == VK_S ) { bar_left_y -= bar_speed; }
}

void keyboard_special(int key, int x, int y)
{
    if (key == GLUT_KEY_UP )   { bar_right_y += bar_speed; }
    if (key == GLUT_KEY_DOWN ) { bar_right_y -= bar_speed; }
}

void drawCircle(float x, float y, float radius)
{
    /* number of points to 'represent' a circle */
    unsigned int triangles = 16; 

    float twicePi = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);
        /* Center of the circle */
        glVertex2f(x, y);
        for(i = 0; i <= triangles; i++) { 
            glVertex2f( x + (radius * cos(i *  twicePi / triangles)), 
                        y + (radius * sin(i * twicePi / triangles)));
        }
    glEnd();
}

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
    
    /* Draw the ball */
    drawCircle(ball_x - ball_size / 2, ball_y - ball_size / 2, bar_width / 2);
    

    /* draw score text */
    sprintf(score_string, "%d : %d", score_left, score_right);
    drawText(width / 2 - 10, height - 30, score_string);

    /* Swap buffers of current window if double buffered */
    glutSwapBuffers();
}

void update(int value)
{
    /* User input handling */ 
    /* Capture keystrokes to their ascii value */
    glutKeyboardFunc(keyboard_normal);
    /* Capture special keystrokes that have no corresponding ascii value */
    glutSpecialFunc(keyboard_special);

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

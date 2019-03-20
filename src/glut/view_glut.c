#include <GL/glut.h>
#include <math.h>
#include <string.h>

#include "view_glut.h"
#include "define.h"

void drawCircle(float x, float y, float radius)
{
    /* number of points to 'represent' a circle */
    unsigned int triangles = 16;
    unsigned int i;

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
    unsigned int i;

    /* Render each character in the string in the named bitmap font */
    for(i = 0; i<strlen(string); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
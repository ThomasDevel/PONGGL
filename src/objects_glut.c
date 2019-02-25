#include "objects_glut.h"
#include "define.h"
#include <math.h>

/* Score of left and right player and the string in
 * which we will write and output the score to the screen.
 */
int score_left = 0;
int score_right = 0;
char score_string[256];

/* Bars */
const int bar_height = 160;
const int bar_speed = 3;

float bar_left_x = 20.0f;
float bar_left_y = 50.0f;

float bar_right_x = WIDTH - BAR_WIDTH - 20;
float bar_right_y = 50.0f;

/* Ball variables */
float ball_x = WIDTH /2;
float ball_y = HEIGHT / 2;
float ball_dir_x = -1.0f;
float ball_dir_y = 0.0f;
const unsigned int ball_size = 20;
const unsigned ball_speed = 3;

void vec2_norm(float *x, float *y) {
    // sets a vectors length to 1 (which means that x + y == 1)
    float length = sqrt(((*x) *(*x)) + ((*y) * (*y)));
    if (length != 0.0f) {
        length = 1.0f / length;
        *x *= length;
        *y *= length;
    }
}

void updateBall() {
    // fly a bit
    ball_x += ball_dir_x * ball_speed;
    ball_y += ball_dir_y * ball_speed;

    // hit by left bar?
    if (ball_x < bar_left_x + (BAR_WIDTH*2) &&
        ball_x > bar_left_x &&
        ball_y < bar_left_y + bar_height &&
        ball_y > bar_left_y) {
        // set fly direction depending on where it hit the bar
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball_y - bar_left_y) / bar_height) - 0.5f;
        ball_dir_x = fabs(ball_dir_x); // force it to be positive
        ball_dir_y = t;
    }

    // hit by right bar?
    if (ball_x > bar_right_x &&
        ball_x < bar_right_x + BAR_WIDTH &&
        ball_y < bar_right_y + bar_height &&
        ball_y > bar_right_y) {
        // set fly direction depending on where it hit the bar
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball_y - bar_right_y) / bar_height) - 0.5f;
        ball_dir_x = -fabs(ball_dir_x); // force it to be negative
        ball_dir_y = t;
    }

    // hit left wall?
    if (ball_x < 0) {
        ++score_right;
        ball_x = width / 2;
        ball_y = height / 2;
        ball_dir_x = fabs(ball_dir_x); // force it to be positive
        ball_dir_y = 0;
    }

    // hit right wall?
    if (ball_x > width) {
        ++score_left;
        ball_x = width / 2;
        ball_y = height / 2;
        ball_dir_x = -fabs(ball_dir_x); // force it to be negative
        ball_dir_y = 0;
    }

    // hit top wall?
    if (ball_y > height) {
        ball_dir_y = -fabs(ball_dir_y); // force it to be negative
    }

    // hit bottom wall?
    if (ball_y < BAR_WIDTH) {
        ball_dir_y = fabs(ball_dir_y); // force it to be positive
    }

    // make sure that length of dir stays at 1
    vec2_norm(&ball_dir_x, &ball_dir_y);
}

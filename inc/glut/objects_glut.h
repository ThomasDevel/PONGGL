/* Variable declarations */

#define BAR_WIDTH 20

extern int score_left;
extern int score_right;
extern char score_string[256];

/* Bars */
extern const int bar_height;
extern const int bar_speed;

extern float bar_left_x;
extern float bar_left_y;

extern float bar_right_x;
extern float bar_right_y;

/* Ball variables */
extern float ball_x;
extern float ball_y;
extern float ball_dir_x;
extern float ball_dir_y;
extern const unsigned int ball_size;
extern const unsigned ball_speed;

/* Function prototype declarations */
void vec2_norm(float *x, float *y);
void updateBall();
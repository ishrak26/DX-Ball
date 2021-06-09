#include <stdio.h>

typedef struct RGBColor {
    int r, g, b;
} RGBColor;
RGBColor ball_def_color = {107, 107, 107}, ball_thru_color = {0, 185, 185}, shooting_color = {251, 176, 4};

typedef struct Rect {
    int left, bottom, dx, dy;
} Rect;

typedef struct Block {
    Rect body;
    int border;
    //int row, col;
    //Perks perk;
    RGBColor color;
    char isShow, isBrick;
} Block;
//Blocks
int block_width = 75, block_height = 25, block_border = 3;

typedef struct Paddle {
    int width, height;
    int left, bottom;
    int scale; //{-2, -1, 0, 1, 2} = {0.5x, 0.67x, 1x, 1.5x, 2x}
    char isGrab, isShoot;
    //int dx; //30
    //RGBColor color; 63, 63, 63
} Paddle;
Paddle paddle = {125, 15, 588, 5, 0, 0, 0};

typedef struct Game_state{
    char isPaused, isOver, isLevelUp, isWon;
    int sec;
    int score;
    int life;
    int game_over_time;
    int block_count;
    char isLoad;
} Game_state;
Game_state game_state = {0, 0, 0, 0, 0, 0, 3, 3, 0, 0};

typedef struct Ball {
    char isShow;
    double r, x, y;
    double dx, dy;
    RGBColor color;
    char isPaused;
    char isThru;
    char isFire;
} Ball;
Ball shooting_ball[2] = {{0, 3, paddle.left + paddle.width * 0.072, 30, 0, 8, shooting_color, 1, 0}, {0, 3, paddle.left + paddle.width - paddle.width * 0.072, 30, 0, 8, shooting_color, 1, 0}};

//Ball speed
double speed = 10, perk_dy = -8, speed_change = 0.05, def_speed = 10;
int ball_def_rad = 7;

int ball_sz = 1;

int music = 1;

void initializeGame();
void initializeBlockInfo();
void initializeGameInfo();
void initializePerkInfo();
void drawHomePage();
void goFullScreen();
void leaveFullScreen();
void saveGameInfo();
void loadGameInfo();
void drawGamePage();
void saveHighScore();
void loadHighScore();
void drawHighScorePage();
void drawNameInputPage();
void drawPauseMenu();
void drawBlock(Block *b);
void initializeBlocks();
void drawMaze();
void drawPaddle();
void drawBall();
//void drawPerks(Perks *perk);
void moveBall();
void paddleInteraction(double*, double*, int);
void blockInteraction(double*, double*, int);
void gameTime();
void drawScoreBar();
int highScoreComparator(const void *i, const void *j);
void gameOverTimeCount();
void movePerk();
void expandPaddle();
void shrinkPaddle();
void resetBall();
void moveShootingBall();
void drawShootingBall();
void shootingBlockInteraction(double *, double *, int);
void changeSpeed();
void checkFireball(int cnt, double *y, int i);
void drawHelpPage();
void playMusic();
void drawCreditsPage();
void savePerkInfo();
void loadPerkInfo();

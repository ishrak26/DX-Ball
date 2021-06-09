#include <stdio.h>

typedef struct Menu {
    char str[6][20];
    int x[6];
    int y[6];
    char isShow[6];
    //char isLoad;
} Menu;
Menu menu =
{
    {"LOAD GAME", "NEW GAME", "HIGH SCORES", "HOW TO PLAY", "CREDITS", "EXIT"},
    {570, 575, 562, 558, 593, 614},
    {325, 275, 225, 175, 125, 75},
    {0}
};
Menu pause_menu =
{
    {"RESUME", "HOW TO PLAY", "HIGH SCORES", "EXIT TO MAIN MENU"},
    {595, 558, 562, 517},
    {375, 325, 275, 225},
    {0}
};

typedef struct High_score {
    char name[30];
    int level;
    int time;
    int score;
} High_score;
High_score high_score[11];

typedef struct User_input {
    char name[30];
    int len;
    char isStart;
} User_input;
User_input user_input;


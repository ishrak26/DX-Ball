#include <stdio.h>

#define TOTAL_PERKS 42

typedef enum Perk_name {
    NONE,
    EIGHT_BALL,
    EXPAND_EXPLODING,
    EXPAND_PADDLE,
    EXTRA_LIFE,
    FALLING_BRICKS,
    FAST_BALL,
    FIREBALL,
    GRAB_PADDLE,
    KILL_PADDLE,
    LEVEL_WARP,
    MEGA_BALL,
    SET_OFF_EXPLODING,
    SHOOTING_PADDLE,
    SHRINK_BALL,
    SHRINK_PADDLE,
    SLOW_BALL,
    SPLIT_BALL,
    SUPER_SHRINK,
    THRU_BRICK,
    ZAP_BRICKS
} Perk_name;

typedef struct Perks {
    char isShow;
    Perk_name perk_name;
    int left, bottom;
    //int dx, dy;
    //int block_number;
} Perks;

int perk_sz;
int perk_timing[TOTAL_PERKS] = {6,12,18,24,30,36,42,48,54,60,66,72,78,84,90,96,102,108,114,120,126,132,138,144,150,156,162,168,174,180,186,192,198,204,210,216,222,228,234,240,246,252};
Perk_name perk_show[TOTAL_PERKS] =
{(Perk_name)9, (Perk_name)3, (Perk_name)5, (Perk_name)6, (Perk_name)9, (Perk_name)15, (Perk_name)11, (Perk_name)19, (Perk_name)9, (Perk_name)18, (Perk_name)16, (Perk_name)14, (Perk_name)8, (Perk_name)9, (Perk_name)4, (Perk_name)5, (Perk_name)6, (Perk_name)13,(Perk_name)9, (Perk_name)3, (Perk_name)5, (Perk_name)6, (Perk_name)9, (Perk_name)15, (Perk_name)11, (Perk_name)19, (Perk_name)9, (Perk_name)18, (Perk_name)16, (Perk_name)14, (Perk_name)8, (Perk_name)9, (Perk_name)4, (Perk_name)5, (Perk_name)6, (Perk_name)13,(Perk_name)9, (Perk_name)3, (Perk_name)5, (Perk_name)6, (Perk_name)9, (Perk_name)15};
Perks perks[TOTAL_PERKS];

//Perk_name tmp[18] = {9, 3, 5, 6, 9, 15, 11, 19, 9, 18, 16, 14, 8, 9, 4, 5, 6, 13};

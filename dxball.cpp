# include "iGraphics.h"
#include "level_design.h"
#include "perks.h"
#include "rendering.h"
#include "gameplay.h"

const double PI = 3.141592654;

/*
    {0, 1, 2, 3, 4, 5, 6, 7, 8} = {Home, Game, High_score, Help, Credits, User input, Pause menu, Pause>High score, Pause>Help}
*/
char currPage = 0;
int currLevel = 1;

Maze maze = {MAX_BLOCKS_PER_ROW * (block_width - block_border), MAX_BLOCKS_PER_COL * (block_height - block_border), (width - maze.width) / 2, height - 75 - maze.height, {0}};

Block all_blocks[LEVELS][TOTAL_BLOCKS];

Ball ball[16] = {1, ball_def_rad, paddle.left + paddle.width * (7 / 12.0), paddle.bottom + paddle.height + ball[0].r, speed * cos(75 * (PI / 180)), speed * sin(75 * (PI / 180)), ball_def_color, 1, 0, 0};

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    iClear();
    if (currPage == 0) drawHomePage();
    else if (currPage == 1) drawGamePage();
    else if (currPage == 2 || currPage == 7) drawHighScorePage();
    else if (currPage == 3 || currPage == 8) drawHelpPage();
    else if (currPage == 4) drawCreditsPage();
    else if (currPage == 5) drawNameInputPage();
    else if (currPage == 6) drawPauseMenu();
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{

}

void iPassiveMouseMove(int mx, int my)
{
    int i, tmp;
    if (currPage == 0) {
        if (my < 350 && my >= 300) {
            menu.isShow[0] = 1;
            tmp = 0;
        }
        else if (my < 300 && my >= 250) {
            menu.isShow[1] = 1;
            tmp = 1;
        }
        else if (my < 250 && my >= 200) {
            menu.isShow[2] = 1;
            tmp = 2;
        }
        else if (my < 200 && my >= 150) {
            menu.isShow[3] = 1;
            tmp = 3;
        }
        else if (my < 150 && my >= 100) {
            menu.isShow[4] = 1;
            tmp = 4;
        }
        else if (my < 100 && my >= 50) {
            menu.isShow[5] = 1;
            tmp = 5;
        }

        for (i = 0; i < 6; i++) {
            if (i != tmp) menu.isShow[i] = 0;
        }
    }
    else if (currPage == 1) {
        if (!game_state.isOver && !game_state.isWon) {
            paddle.left = mx - (paddle.width / 2);
            if (paddle.left < 25) paddle.left = 25;
            else if (paddle.left + paddle.width > width - 25) paddle.left = width - 25 - paddle.width;

            for (i = 0; i < ball_sz; i++) {
                if (ball[i].isPaused) {
                    //if (!paddle.isGrab)
                        ball[i].x = paddle.left + paddle.width * (7 / 12.0);
//                    else {
//                        double angle = atan(ball[i].dy / ball[i].dx);
//                        if (angle < 0) angle = PI + angle;
//                        ball[i].x = paddle.left + paddle.width - ((angle * paddle.width) / PI);
//                    }
                }
            }

            if (paddle.isShoot && shooting_ball[0].isPaused) {
                shooting_ball[0].x = paddle.left + 0.072 * paddle.width;
                shooting_ball[1].x = paddle.left + paddle.width - 0.072 * paddle.width;
            }
        }
    }
    else if (currPage == 6) {
        if (my < 425 && my >= 375) {
            pause_menu.isShow[0] = 1;
            tmp = 0;
        }
        else if (my < 375 && my >= 325) {
            pause_menu.isShow[1] = 1;
            tmp = 1;
        }
        else if (my < 325 && my >= 275) {
            pause_menu.isShow[2] = 1;
            tmp = 2;
        }
        else if (my < 275 && my >= 225) {
            pause_menu.isShow[3] = 1;
            tmp = 3;
        }
        for (i = 0; i < 4; i++) {
            if (i != tmp) pause_menu.isShow[i] = 0;
        }
    }
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    //printf("%d, %d\n", mx, my);
    int i;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //printf("%d %d %d\n", paddle.width, paddle.left, paddle.left + paddle.width);
        if (currPage == 0) {
            if (menu.isShow[0]) {
                //loadGameInfo();
                game_state.isLoad = 0;
                game_state.isPaused = 0;
//                PlaySound(NULL, 0, 0);
                playMusic();
                currPage = 1;
//                PlaySound("Sound\\1.wav", NULL, SND_ASYNC);
                //goFullScreen();
            }
            else if (menu.isShow[1]) {
                //New game
                menu.isShow[1] = 0;
//                PlaySound(NULL, 0, 0);
//                game_state.sec = 0;
//                game_state.score = 0;
//                game_state.life = 3;
//                game_state.block_count = 0;
                initializeBlockInfo();
                initializeGameInfo();
                initializePerkInfo();
                playMusic();
                currPage = 1;
//                PlaySound("Sound\\1.wav", NULL, SND_ASYNC);
//                goFullScreen();
            }
            else if (menu.isShow[2]) {
                menu.isShow[2] = 0;
                currPage = 2;
            }
            else if (menu.isShow[3]) {
                menu.isShow[3] = 0;
                currPage = 3;
            }
            else if (menu.isShow[4]) {
                menu.isShow[4] = 0;
                currPage = 4;
            }
            else if (menu.isShow[5]) {
                menu.isShow[5] = 0;

//                if (fwrite(&high_score, sizeof(high_score), 1, write_score) != 1) {
//                    fprintf(stderr, "Score could not be written\n");
//                    exit(1);
//                }
//                if (fclose(write_score)) {
//                    fprintf(stderr, "write_score could not be closed\n");
//                    exit(1);
//                }

                exit(0);
            }
        }
        else if (currPage == 1) {
            for (i = 0; i < ball_sz; i++) {
                if (ball[i].isPaused) {
                    ball[i].isPaused = 0;
                }
            }
            if (paddle.isShoot && shooting_ball[0].isPaused) {
                shooting_ball[0].isPaused = 0;
                shooting_ball[1].isPaused = 0;
            }
        }
        else if (currPage == 2) {
            if (mx >= 25 && mx <= 55 && my >= 590 && my <= 620) {
                currPage = 0;
            }
        }
        else if (currPage == 3) {
            if (mx >= 50 && mx <= 80 && my >= 580 && my <= 610) {
                currPage = 0;
            }
        }
        else if (currPage == 4) {
            if (mx >= 25 && mx <= 55 && my >= 580 && my <= 610) {
                currPage = 0;
            }
        }
        else if (currPage == 6) {
            if (pause_menu.isShow[0]) {
                //resume
                pause_menu.isShow[0] = 0;
                game_state.isPaused = 0;
                //PlaySound("Sound\\1.wav", NULL, SND_ASYNC);
                playMusic();
                currPage = 1;
//                goFullScreen();
            }
            else if (pause_menu.isShow[1]) {
                pause_menu.isShow[1] = 0;
                currPage = 8;
            }
            else if (pause_menu.isShow[2]) {
                //high score
                pause_menu.isShow[2] = 0;
                currPage = 7;
            }
            else if (pause_menu.isShow[3]) {
                //exit to main menu
                game_state.isLoad = 1;
                saveGameInfo();
                savePerkInfo();

                pause_menu.isShow[3] = 0;

//                PlaySound(NULL, 0, 0);
//                PlaySound("0.wav", NULL, SND_ASYNC | SND_LOOP);
                currPage = 0;
            }
        }
        else if (currPage == 7) {
            if (mx >= 25 && mx <= 55 && my >= 590 && my <= 620) {
                currPage = 6;
            }
        }
        else if (currPage == 8) {
            if (mx >= 50 && mx <= 80 && my >= 580 && my <= 610) {
                currPage = 6;
            }
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
//    if (key == 'a') {
//        if (currPage == 0) {
//            currPage = 1;
//        }
//        else if (currPage == 1) {
//            currPage = 0;
//        }
//    }
    int i;
    if (currPage == 1) {
        if (key == 'p' || key == 'P') {
            game_state.isPaused = 1;

            PlaySound(NULL, 0, 0);
            PlaySound("Sound\\0.wav", NULL, SND_ASYNC | SND_LOOP);
            currPage = 6;

//            leaveFullScreen();
        }
        else if (key == ' ') {
            for (i = 0; i < ball_sz; i++) {
                if (ball[i].isPaused) {
                    ball[i].isPaused = 0;
                }
            }
            if (paddle.isShoot && shooting_ball[0].isPaused) {
                shooting_ball[0].isPaused = 0;
                shooting_ball[1].isPaused = 0;
            }
        }
    }
    else if (currPage == 5) {
        if (user_input.isStart) {
            if (key == '\b') {
                user_input.len--;
                if (user_input.len < 0) user_input.len = 0;
                user_input.name[user_input.len] = '\0';
            }
            else if (key == '\r' && user_input.len > 0) {
//                if (game_state.isWon) {
//                    high_score[10].level = LEVELS;
//                    game_state.isWon = 0;
//                }
//                else {
//                    high_score[10].level = currLevel - 1;
//                }
                high_score[10].score = game_state.score;
                high_score[10].time = game_state.sec;
                for (i = 0; i < user_input.len; i++) {
                    high_score[10].name[i] = user_input.name[i];
                }
                user_input.len = 0;
                user_input.isStart = 0;
                high_score[10].name[i] = '\0';

                game_state.game_over_time = 3;
                game_state.isOver = 0;
                game_state.isPaused = 1;
                game_state.life = 3;
                game_state.score = 0;
                game_state.sec = 0;

                qsort(high_score, sizeof(high_score) / sizeof(high_score[0]) , sizeof(high_score[0]), highScoreComparator);
                saveHighScore();
                //saveGameInfo();
                game_state.isLoad = 0;
                currPage = 2;

            }
            else if ((isalpha(key) || key == ' ' || key == '.') && user_input.len < 29) {
                user_input.name[user_input.len++] = key;
                user_input.name[user_input.len] = '\0';
            }
        }
        else if (!user_input.isStart) {
            user_input.isStart = 1;
            if (isalpha(key)) {
                user_input.name[user_input.len++] = key;
                user_input.name[user_input.len] = '\0';
            }
        }
    }
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    int i;
    if (key == GLUT_KEY_END) {
        exit(0);
    }
//    else if (key == GLUT_KEY_F2) {
//        glutGameModeString("800x600");
//        if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
//            glutEnterGameMode();
//            init_self();
//        }
//        printf("%d\n", GLUT_GAME_MODE_POSSIBLE);
//    }
//    else if (key == GLUT_KEY_F3) {
//        glutLeaveGameMode();
//    }
    if (currPage = 1) {
        if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_LEFT) {
            if (key == GLUT_KEY_RIGHT) {
                if (!game_state.isOver && !game_state.isWon) paddle.left += 20;
            }
            else if (key == GLUT_KEY_LEFT) {
                if (!game_state.isOver && !game_state.isWon) paddle.left -= 20;
            }
            if (paddle.left < 25) paddle.left = 25;
            else if (paddle.left + paddle.width > width - 25) paddle.left = width - 25 - paddle.width;

            for (i = 0; i < ball_sz; i++) {
                if (ball[i].isPaused) {
                    if (!paddle.isGrab) ball[i].x = paddle.left + paddle.width * (7 / 12.0);
                    else {
                        double angle = atan(ball[i].dy / ball[i].dx);
                        if (angle < 0) angle = PI + angle;
                        ball[i].x = paddle.left + paddle.width - ((angle * paddle.width) / PI);
                    }
                }
            }

            if (paddle.isShoot && shooting_ball[0].isPaused) {
                shooting_ball[0].x = paddle.left + 0.072 * paddle.width;
                shooting_ball[1].x = paddle.left + paddle.width - 0.072 * paddle.width;
            }
        }
//        else if (key == GLUT_KEY_F2) {
//            game_state.block_count = block_count[currLevel - 1] - 2;
//        }

    }


}


int main()
{
    //printf("%d %d\n", game_state.isOver, game_state.isWon);
    //int i, j, k, cnt;
    //printf("Before %d %d %d\n", maze.height, maze.bottom, height - 50 - maze.height);

//    if ((read_score = fopen("Files\\High_score.txt", "rb")) == NULL) {
//        fprintf(stderr, "High_score.txt could not be opened for reading\n");
//        return 1;
//    }
//    fread(&high_score, sizeof(high_score), 1, read_score);
//    if (fclose(read_score)) {
//        fprintf(stderr, "High_score.txt could not be closed after reading\n");
//        return 1;
//    }

    //printf("%d %d %lf\n", paddle.left, paddle.width, ball[0].x);
//    if ((write_score = fopen("Files\\High_score.txt", "wb")) == NULL) {
//        fprintf(stderr, "High_score.txt could not be opened for writing\n");
//        return 1;
//    }

//    for (k = 0, cnt = 0; k < LEVELS; k++) {
//        for (i = 0; i < MAX_BLOCKS_PER_COL; i++) {
//            for (j = 0; j < MAX_BLOCKS_PER_ROW; j++, cnt++) {
//                mat[k][i][j] = rand() % 7;
//                if (mat[k][i][j]) maze.total_blocks[k]++;
//            }
//        }
//    }
//    if (!mat[0][0][3]) mat[0][0][3] = 2;
//    if (!mat[0][4][4]) mat[0][0][3] = 3;
//    //perks[EXPAND_PADDLE].block_number = 2 * MAX_BLOCKS_PER_ROW + 3;
//    all_blocks[0][0 * MAX_BLOCKS_PER_ROW + 3].perk.perk_name = EXPAND_PADDLE;
//    all_blocks[0][4 * MAX_BLOCKS_PER_ROW + 4].perk.perk_name = EXPAND_PADDLE;

    //printf("%d %d %d %d\n", width, maze.width, width - maze.width, maze.left);
    //exit(0);

    //initializeBlocks();

//    FILE *write_def = NULL;
//    if ((write_def = fopen("Files\\default_block_info.txt", "wb")) == NULL) {
//        fprintf(stderr, "default_block_info.txt could not be opened for writing\n");
//        return 1;
//    }
//    if (fwrite(all_blocks, sizeof(all_blocks), 1, write_def) != 1) {
//        fprintf(stderr, "all_blocks[][] could not be written\n");
//        return 1;
//    }
//    if (fwrite(block_count, sizeof(block_count), 1, write_def) != 1) {
//        fprintf(stderr, "block_count[] could not be written\n");
//        return 1;
//    }
//    if (fclose(write_def)) {
//        fprintf(stderr, "default_block_info.txt could not be closed\n");
//        return 1;
//    }

//    for (i = 0; i < MAX_BLOCKS_PER_ROW; i++) {
//        printf("%d\n", all_blocks[currLevel - 1][i].body.left);
//    }
    //exit(0);
    //printf("Blocks initialized successfully\n");

    //printf("After %d %d %d\n", maze.height, maze.bottom, height - 50 - maze.height);

//    FILE *read_def_block = NULL;
//    if ((read_def_block = fopen("Files\\default_state\\default_block_info.txt", "rb")) == NULL) {
//        fprintf(stderr, "default_block_info.txt could not be opened for reading\n");
//        return 1;
//    }
//    if (fread(all_blocks, sizeof(all_blocks), 1, read_def_block) != 1) {
//        fprintf(stderr, "all_blocks[][] could not be read\n");
//        return 1;
//    }
//    if (fread(block_count, sizeof(block_count), 1, read_def_block) != 1) {
//        fprintf(stderr, "block_count[] could not be read\n");
//        return 1;
//    }
//    if (fclose(read_def_block)) {
//        fprintf(stderr, "default_block_info.txt could not be closed after reading\n");
//        return 1;
//    }

//    FILE *write_def = NULL;
//    if ((write_def = fopen("Files\\default_state\\default_game_info.txt", "wb")) == NULL) {
//        fprintf(stderr, "default_game_info.txt could not be opened for writing\n");
//        return 1;
//    }
//    if (fwrite(&game_state, sizeof(game_state), 1, write_def) != 1) {
//        fprintf(stderr, "game_state could not be written\n");
//        return 1;
//    }
//    if (fwrite(&paddle, sizeof(paddle), 1, write_def) != 1) {
//        fprintf(stderr, "paddle could not be written\n");
//        return 1;
//    }
//    if (fwrite(&speed, sizeof(speed), 1, write_def) != 1) {
//        fprintf(stderr, "speed could not be written\n");
//        return 1;
//    }
//    if (fwrite(&perk_dy, sizeof(perk_dy), 1, write_def) != 1) {
//        fprintf(stderr, "perk_dy could not be written\n");
//        return 1;
//    }
//    if (fwrite(&ball_sz, sizeof(ball_sz), 1, write_def) != 1) {
//        fprintf(stderr, "ball_sz could not be written\n");
//        return 1;
//    }
//    if (fwrite(&currLevel, sizeof(currLevel), 1, write_def) != 1) {
//        fprintf(stderr, "currLevel could not be written\n");
//        return 1;
//    }
//    if (fwrite(&maze, sizeof(maze), 1, write_def) != 1) {
//        fprintf(stderr, "maze could not be written\n");
//        return 1;
//    }
//    if (fwrite(&ball, sizeof(ball), 1, write_def) != 1) {
//        fprintf(stderr, "ball could not be written\n");
//        return 1;
//    }
//    if (fwrite(&shooting_ball, sizeof(shooting_ball), 1, write_def) != 1) {
//        fprintf(stderr, "shooting ball could not be written\n");
//        return 1;
//    }
//    if (fclose(write_def)) {
//        fprintf(stderr, "default_game_info.txt could not be closed\n");
//        return 1;
//    }
//    exit(0);

//    saveGameInfo();
//    exit(0);
//    savePerkInfo();
//    exit(0);
    initializeGame();
//    printf("%d %d\n", game_state.game_over_time, game_state.isOver);
//    game_state.game_over_time = 3;
//    game_state.life = 3;

    iSetTimer(20, moveBall);
    iSetTimer(1000, changeSpeed);
    iSetTimer(1000, gameTime);
    iSetTimer(1000, gameOverTimeCount);
    iSetTimer(40, movePerk);
    iSetTimer(20, moveShootingBall);
    //test = 0;

    PlaySound("Sound\\0.wav", NULL, SND_ASYNC | SND_LOOP);

    iInitialize(width, height, "dxball");
    return 0;
}

void playMusic() {
    PlaySound(NULL, 0, 0);
    char str[30] = "Sound\\", str1[20] = {0};
    sprintf(str1, "%d.wav", music);
    music++;
    if (music > 3) music = 1;
    strcat(str, str1);
    PlaySound(str, NULL, SND_ASYNC);
}

void initializeBlockInfo() {
    FILE *read_def_block = NULL;
    if ((read_def_block = fopen("Files\\default_state\\default_block_info.txt", "rb")) == NULL) {
        fprintf(stderr, "default_block_info.txt could not be opened for reading\n");
        exit(1);
    }
    if (fread(all_blocks, sizeof(all_blocks), 1, read_def_block) != 1) {
        fprintf(stderr, "all_blocks[][] could not be read\n");
        exit(1);
    }
    if (fread(block_count, sizeof(block_count), 1, read_def_block) != 1) {
        fprintf(stderr, "block_count[] could not be read\n");
        exit(1);
    }
    if (fclose(read_def_block)) {
        fprintf(stderr, "default_block_info.txt could not be closed after reading\n");
        exit(1);
    }
}

void initializeGameInfo() {
    FILE *read_def_game = NULL;

    if ((read_def_game = fopen("Files\\default_state\\default_game_info.txt", "rb")) == NULL) {
        fprintf(stderr, "default_game_info.txt could not be opened for reading\n");
        exit(1);
    }
    if (fread(&game_state, sizeof(game_state), 1, read_def_game) != 1) {
        fprintf(stderr, "game_state could not be read\n");
        exit(1);
    }
    if (fread(&paddle, sizeof(paddle), 1, read_def_game) != 1) {
        fprintf(stderr, "paddle could not be read\n");
        exit(1);
    }
    if (fread(&speed, sizeof(speed), 1, read_def_game) != 1) {
        fprintf(stderr, "speed could not be read\n");
        exit(1);
    }
    if (fread(&perk_dy, sizeof(perk_dy), 1, read_def_game) != 1) {
        fprintf(stderr, "perk_dy could not be read\n");
        exit(1);
    }
    if (fread(&ball_sz, sizeof(ball_sz), 1, read_def_game) != 1) {
        fprintf(stderr, "ball_sz could not be read\n");
        exit(1);
    }
    if (fread(&currLevel, sizeof(currLevel), 1, read_def_game) != 1) {
        fprintf(stderr, "currLevel could not be read\n");
        exit(1);
    }
    if (fread(&maze, sizeof(maze), 1, read_def_game) != 1) {
        fprintf(stderr, "maze could not be read\n");
        exit(1);
    }
    if (fread(&ball, sizeof(ball), 1, read_def_game) != 1) {
        fprintf(stderr, "ball could not be read\n");
        exit(1);
    }
    if (fread(&shooting_ball, sizeof(shooting_ball), 1, read_def_game) != 1) {
        fprintf(stderr, "shooting ball could not be read\n");
        exit(1);
    }
    if (fclose(read_def_game)) {
        fprintf(stderr, "default_game_info.txt could not be closed\n");
        exit(1);
    }
}

void initializePerkInfo() {
    FILE *read = NULL;
    if ((read = fopen("Files\\default_state\\default_perk_info.txt", "rb")) == NULL) {
        fprintf(stderr, "default_perk_info.txt could not be opened for reading\n");
        exit(1);
    }
    if (fread(&perk_sz, sizeof(perk_sz), 1, read) != 1) {
        fprintf(stderr, "perk_sz could not be read\n");
        exit(1);
    }
    if (fread(perk_timing, sizeof(perk_timing), 1, read) != 1) {
        fprintf(stderr, "perk_timing could not be read\n");
        exit(1);
    }
    if (fread(perk_show, sizeof(perk_show), 1, read) != 1) {
        fprintf(stderr, "perk_show could not be read\n");
        exit(1);
    }
    if (fread(perks, sizeof(perks), 1, read) != 1) {
        fprintf(stderr, "perks could not be read\n");
        exit(1);
    }
    if (fclose(read)) {
        fprintf(stderr, "default_perk_info.txt could not be closed after reading\n");
        exit(1);
    }
}

void initializeGame() {
    //initializeBlockInfo();
    //initializeGameInfo();
    loadGameInfo();
    loadPerkInfo();
    loadHighScore();
}

//void initializeBlocks() {
//    int i, j, k, x, y, cnt;
//    int c;
//    //RGBColor color;
//    for (k = 0; k < LEVELS; k++) {
//        for (y = maze.bottom, i = 0, cnt = 0; i < MAX_BLOCKS_PER_COL; y += block_height - block_border, i++) {
//            for (x = maze.left, j = 0; j < MAX_BLOCKS_PER_ROW; x += block_width - block_border, j++, cnt++) {
//                c = mat[k][i][j];
//                if (c) {
//                    block_count[k]++;
//
//                    all_blocks[k][cnt].isShow = 1;
//                    all_blocks[k][cnt].body.left = x;
//                    all_blocks[k][cnt].body.bottom = y;
//                    all_blocks[k][cnt].body.dx = block_width;
//                    all_blocks[k][cnt].body.dy = block_height;
//                    all_blocks[k][cnt].border = block_border;
//
////                    if (all_blocks[k][cnt].perk.perk_name) {
////                        all_blocks[k][cnt].perk.isShow = 0;
////                        all_blocks[k][cnt].perk.left = x;
////                        all_blocks[k][cnt].perk.bottom = y;
////                        //printf("%d\n", cnt);
////                    }
//
//                    switch(c) {
//                        case 1:
//                            all_blocks[k][cnt].color.r = 240;
//                            all_blocks[k][cnt].color.g = 0;
//                            all_blocks[k][cnt].color.b = 0;
//                            break;
//                        case 2:
//                            all_blocks[k][cnt].color.r = 117;
//                            all_blocks[k][cnt].color.g = 255;
//                            all_blocks[k][cnt].color.b = 255;
//                            break;
//                        case 3:
//                            all_blocks[k][cnt].color.r = 0;
//                            all_blocks[k][cnt].color.g = 0;
//                            all_blocks[k][cnt].color.b = 240;
//                            all_blocks[k][cnt].isBrick = 1;
//                            break;
//                        case 4:
//                            all_blocks[k][cnt].color.r = 132;
//                            all_blocks[k][cnt].color.g = 255;
//                            all_blocks[k][cnt].color.b = 132;
//                            break;
//                        case 5:
//                            all_blocks[k][cnt].color.r = 62;
//                            all_blocks[k][cnt].color.g = 62;
//                            all_blocks[k][cnt].color.b = 255;
//                            break;
//                        case 6:
//                            all_blocks[k][cnt].color.r = 174;
//                            all_blocks[k][cnt].color.g = 174;
//                            all_blocks[k][cnt].color.b = 174;
//                            break;
//                        case 7:
//                            all_blocks[k][cnt].color.r = 0;
//                            all_blocks[k][cnt].color.g = 220;
//                            all_blocks[k][cnt].color.b = 0;
//                            all_blocks[k][cnt].isBrick = 1;
//                            break;
//                        case 8:
//                            all_blocks[k][cnt].color.r = 225;
//                            all_blocks[k][cnt].color.g = 225;
//                            all_blocks[k][cnt].color.b = 0;
//                            break;
//                        case 9:
//                            all_blocks[k][cnt].color.r = 210;
//                            all_blocks[k][cnt].color.g = 210;
//                            all_blocks[k][cnt].color.b = 210;
//                            all_blocks[k][cnt].isBrick = 1;
//                            break;
//                        case 10:
//                            all_blocks[k][cnt].color.r = 255;
//                            all_blocks[k][cnt].color.g = 255;
//                            all_blocks[k][cnt].color.b = 80;
//                            all_blocks[k][cnt].isBrick = 1;
//                            break;
//                        default:
//                            all_blocks[k][cnt].color.r = 255;
//                            all_blocks[k][cnt].color.g = 0;
//                            all_blocks[k][cnt].color.b = 255;
//                    }
//                }
//            }
//        }
//    }
//}

void drawHomePage() {
    int i;
    iShowBMP(0, 0, "Pics\\Background\\0.bmp");
    iShowBMP2(450, 400, "Pics\\Background\\dxball.bmp", 0xffffff);

//    iSetColor(192, 0, 0);
//    iText(570, 325, "LOAD GAME", GLUT_BITMAP_TIMES_ROMAN_24);
//    iText(575, 275, "NEW GAME", GLUT_BITMAP_TIMES_ROMAN_24);
//    iText(562, 225, "HIGH SCORES", GLUT_BITMAP_TIMES_ROMAN_24);
//    iText(613, 175, "HELP", GLUT_BITMAP_TIMES_ROMAN_24);
//    iText(593, 125, "CREDITS", GLUT_BITMAP_TIMES_ROMAN_24);
//    iText(614, 75, "EXIT", GLUT_BITMAP_TIMES_ROMAN_24);

    if (game_state.isLoad) {
        if (menu.isShow[0]) iSetColor(255, 0, 0);
        else iSetColor(175, 0, 0);
        iText(menu.x[0], menu.y[0], menu.str[0], GLUT_BITMAP_TIMES_ROMAN_24);
    }
    for (i = 1; i < 6; i++) {
        if (menu.isShow[i]) iSetColor(255, 0, 0);
        else iSetColor(175, 0, 0);
        iText(menu.x[i], menu.y[i], menu.str[i], GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void loadHighScore() {
    FILE *read_score = NULL;
    if ((read_score = fopen("Files\\load_state\\high_score.txt", "rb")) == NULL) {
        fprintf(stderr, "high_score.txt could not be opened for reading\n");
        exit(1);
    }
    if (fread(high_score, sizeof(high_score), 1, read_score) != 1) {
        fprintf(stderr, "high_score could not be read\n");
        exit(1);
    }
    if (fclose(read_score)) {
        fprintf(stderr, "high_score.txt could not be closed after reading\n");
        exit(1);
    }
}

void saveHighScore() {
    FILE *write_score = NULL;
    if ((write_score = fopen("Files\\load_state\\high_score.txt", "wb")) == NULL) {
        fprintf(stderr, "high_score.txt could not be opened for writing\n");
        exit(1);
    }
    if (fwrite(high_score, sizeof(high_score), 1, write_score) != 1) {
        fprintf(stderr, "high_score could not be written\n");
        exit(1);
    }
    if (fclose(write_score)) {
        fprintf(stderr, "high_score.txt could not be closed\n");
        exit(1);
    }
}

void drawHighScorePage() {
    int i, y, hour, minute, second;
    char str[30] = {0};

    FILE *read_score = NULL;
    if ((read_score = fopen("Files\\load_state\\high_score.txt", "rb")) == NULL) {
        fprintf(stderr, "high_score.txt could not be opened for reading\n");
        exit(1);
    }
    if (fread(high_score, sizeof(high_score), 1, read_score) != 1) {
        fprintf(stderr, "high_score could not be read\n");
        exit(1);
    }
    if (fclose(read_score)) {
        fprintf(stderr, "high_score.txt could not be closed\n");
        exit(1);
    }

    iShowBMP(0, 0, "Pics\\Background\\2.bmp");
    iShowBMP2(400, 450, "Pics\\Background\\high_scores3.bmp", 0x00ffffff);
    iShowBMP2(25, 590, "Pics\\Background\\back_icon2.bmp", 0);

    iSetColor(0, 166, 83);
    iText(100, 400, "RANK", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 180, 90);
    iText(425, 400, "NAME", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(750, 400, "LEVEL", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 166, 83);
    iText(950, 400, "TIME", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(1125, 400, "SCORE", GLUT_BITMAP_TIMES_ROMAN_24);

//    iSetColor(85, 0, 0);
    iLine(50, 385, width - 50, 385);

    //qsort(high_score, 10, sizeof(High_score), highScoreComparator);

    iSetColor(0, 174, 174);
//    for (int j = 0; j < 11; j++) {
//        printf("%s %d %d %d\n", high_score[j].name, high_score[j].level, high_score[j].score, high_score[j].time);
//    }
//    exit(0);
    for (i = 0, y = 355; i < 10; i++, y -= 35) {
        if (!strlen(high_score[i].name)) break;
        sprintf(str, "%s", high_score[i].name);
        iText(435, y, str, GLUT_BITMAP_HELVETICA_18);

        if (high_score[i].level == 0) {
            sprintf(str, "None");
            iText(760, y, str, GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if (high_score[i].level == LEVELS) {
            sprintf(str, "Won!");
            iText(760, y, str, GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else {
            sprintf(str, "%d", high_score[i].level);
            iText(780, y, str, GLUT_BITMAP_HELVETICA_18);
        }

        second = high_score[i].time;
        hour = second / 3600;
        second -= hour * 3600;
        minute = second / 60;
        second -= minute * 60;
        if (hour != 0) sprintf(str, "%02d:%02d:%02d", hour, minute, second);
        else sprintf(str, "%02d:%02d", minute, second);
        iText(960, y, str, GLUT_BITMAP_HELVETICA_18);

        sprintf(str, "%5d", high_score[i].score);
        iText(1135, y, str, GLUT_BITMAP_HELVETICA_18);

        sprintf(str, "%2d", i + 1);
        iText(122, y, str, GLUT_BITMAP_HELVETICA_18);
    }
}

void drawNameInputPage() {
    iShowBMP(0, 0, "Pics\\Background\\2.bmp");

    iSetColor(0, 166, 83);
    iLine(100, 320, width - 100, 320);

    if (!user_input.isStart) {
        iText(400, 330, "TYPE YOUR NAME (MAXIMUM 30 CHARACTERS)", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else {
        iText(590, 330, user_input.name, GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void drawPauseMenu() {
    int i;
    iShowBMP(0, 0, "Pics\\Background\\8.bmp");

    for (i = 0; i < 4; i++) {
        if (pause_menu.isShow[i]) iSetColor(0, 255, 255);
        //else iSetColor(175, 0, 0);
        else iSetColor(0, 150, 150);
        iText(pause_menu.x[i], pause_menu.y[i], pause_menu.str[i], GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void drawPerks(Perks *perk) {
    char str[50] = "Pics\\Perks\\", str2[25] = {0};
    switch(perk->perk_name) {
        case EIGHT_BALL:
            strcpy(str2, "eight_ball");
            break;
        case EXPAND_EXPLODING:
            strcpy(str2, "expand_exploding");
            break;
        case EXPAND_PADDLE:
            strcpy(str2, "expand_paddle");
            break;
        case EXTRA_LIFE:
            strcpy(str2, "extra_life");
            break;
        case FALLING_BRICKS:
            strcpy(str2, "falling_bricks");
            break;
        case FAST_BALL:
            strcpy(str2, "fast_ball");
            break;
        case FIREBALL:
            strcpy(str2, "fireball");
            break;
        case GRAB_PADDLE:
            strcpy(str2, "grab_paddle");
            break;
        case KILL_PADDLE:
            strcpy(str2, "kill_paddle");
            break;
        case LEVEL_WARP:
            strcpy(str2, "level_warp");
            break;
        case MEGA_BALL:
            strcpy(str2, "mega_ball");
            break;
        case SET_OFF_EXPLODING:
            strcpy(str2, "set_off_exploding");
            break;
        case SHOOTING_PADDLE:
            strcpy(str2, "shooting_paddle");
            break;
        case SHRINK_BALL:
            strcpy(str2, "shrink_ball");
            break;
        case SHRINK_PADDLE:
            strcpy(str2, "shrink_paddle");
            break;
        case SLOW_BALL:
            strcpy(str2, "slow_ball");
            break;
        case SPLIT_BALL:
            strcpy(str2, "split_ball");
            break;
        case SUPER_SHRINK:
            strcpy(str2, "super_shrink");
            break;
        case THRU_BRICK:
            strcpy(str2, "thru_brick");
            break;
        case ZAP_BRICKS:
            strcpy(str2, "zap_bricks");
            break;
        default:
            return;
    }
    strcat(str, str2);
    strcat(str, ".bmp");

    //iShowBMP(perks[name].left, perks[name].bottom, str);
    iShowBMP(perk->left, perk->bottom, str);
}

void goFullScreen() {
    glutDestroyWindow(glutGetWindow());

    glutGameModeString("800x400");
    glutEnterGameMode();

    init_self();
}

void leaveFullScreen() {
    glutLeaveGameMode();

    glutCreateWindow("dxball");

    init_self();
}

void saveGameInfo() {
    FILE *write_game = NULL;

    if ((write_game = fopen("Files\\load_state\\game_info.txt", "wb")) == NULL) {
        fprintf(stderr, "game_info.txt could not be opened for writing\n");
        exit(1);
    }
    if (fwrite(&game_state, sizeof(game_state), 1, write_game) != 1) {
        fprintf(stderr, "game_state could not be written\n");
        exit(1);
    }
    if (fwrite(&paddle, sizeof(paddle), 1, write_game) != 1) {
        fprintf(stderr, "paddle could not be written\n");
        exit(1);
    }
    if (fwrite(&speed, sizeof(speed), 1, write_game) != 1) {
        fprintf(stderr, "speed could not be written\n");
        exit(1);
    }
    if (fwrite(&perk_dy, sizeof(perk_dy), 1, write_game) != 1) {
        fprintf(stderr, "perk_dy could not be written\n");
        exit(1);
    }
    if (fwrite(&ball_sz, sizeof(ball_sz), 1, write_game) != 1) {
        fprintf(stderr, "ball_sz could not be written\n");
        exit(1);
    }
    if (fwrite(&currLevel, sizeof(currLevel), 1, write_game) != 1) {
        fprintf(stderr, "currLevel could not be written\n");
        exit(1);
    }
    if (fwrite(&maze, sizeof(maze), 1, write_game) != 1) {
        fprintf(stderr, "maze could not be written\n");
        exit(1);
    }
    if (fwrite(&ball, sizeof(ball), 1, write_game) != 1) {
        fprintf(stderr, "ball could not be written\n");
        exit(1);
    }
    if (fwrite(&shooting_ball, sizeof(shooting_ball), 1, write_game) != 1) {
        fprintf(stderr, "shooting ball could not be written\n");
        exit(1);
    }
    if (fwrite(&all_blocks, sizeof(all_blocks), 1, write_game) != 1) {
        fprintf(stderr, "all_blocks could not be written\n");
        exit(1);
    }
    if (fwrite(&block_count, sizeof(block_count), 1, write_game) != 1) {
        fprintf(stderr, "block_count could not be written\n");
        exit(1);
    }
    if (fclose(write_game)) {
        fprintf(stderr, "game_info.txt could not be closed\n");
        exit(1);
    }
}

void loadGameInfo() {
    FILE *read_game = NULL;

    if ((read_game = fopen("Files\\load_state\\game_info.txt", "rb")) == NULL) {
        fprintf(stderr, "game_info.txt could not be opened for reading\n");
        exit(1);
    }
    if (fread(&game_state, sizeof(game_state), 1, read_game) != 1) {
        fprintf(stderr, "game_state could not be read\n");
        exit(1);
    }
    if (fread(&paddle, sizeof(paddle), 1, read_game) != 1) {
        fprintf(stderr, "paddle could not be read\n");
        exit(1);
    }
    if (fread(&speed, sizeof(speed), 1, read_game) != 1) {
        fprintf(stderr, "speed could not be read\n");
        exit(1);
    }
    if (fread(&perk_dy, sizeof(perk_dy), 1, read_game) != 1) {
        fprintf(stderr, "perk_dy could not be read\n");
        exit(1);
    }
    if (fread(&ball_sz, sizeof(ball_sz), 1, read_game) != 1) {
        fprintf(stderr, "ball_sz could not be read\n");
        exit(1);
    }
    if (fread(&currLevel, sizeof(currLevel), 1, read_game) != 1) {
        fprintf(stderr, "currLevel could not be read\n");
        exit(1);
    }
    if (fread(&maze, sizeof(maze), 1, read_game) != 1) {
        fprintf(stderr, "maze could not be read\n");
        exit(1);
    }
    if (fread(&ball, sizeof(ball), 1, read_game) != 1) {
        fprintf(stderr, "ball could not be read\n");
        exit(1);
    }
    if (fread(&shooting_ball, sizeof(shooting_ball), 1, read_game) != 1) {
        fprintf(stderr, "shooting ball could not be read\n");
        exit(1);
    }
    if (fread(&all_blocks, sizeof(all_blocks), 1, read_game) != 1) {
        fprintf(stderr, "all_blocks could not be read\n");
        exit(1);
    }
    if (fread(&block_count, sizeof(block_count), 1, read_game) != 1) {
        fprintf(stderr, "block_count could not be read\n");
        exit(1);
    }
    if (fclose(read_game)) {
        fprintf(stderr, "game_info.txt could not be closed\n");
        exit(1);
    }
}

void drawHelpPage() {
    iShowBMP(0, 0, "Pics\\Background\\4.bmp");
    iShowBMP2(50, 580, "Pics\\Background\\back_icon2.bmp", 0);

//    iSetColor(0, 155, 155);
//    iText(50, 550, "PADDLE", GLUT_BITMAP_TIMES_ROMAN_24);

    iSetColor(0, 187, 187);
    iText(50, 540, "MOVE THE PADDLE", GLUT_BITMAP_TIMES_ROMAN_24);
    iShowBMP2(290, 540, "Pics\\Paddle\\paddle.bmp", 0);
    iText(420, 540, "USING MOUSE OR LEFT AND RIGHT ARROW KEYS OF THE KEYBOARD TO", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(50, 510, "REFLECT THE BALL IN ANY DIRECTION. LEFT-CLICK OR PRESS SPACE TO RELEASE THE BALL.", GLUT_BITMAP_TIMES_ROMAN_24);

    iText(50, 470, "KEEP HITTING THE BLOCKS AS MANY AS YOU CAN AND MOVE ON TO A NEW LEVEL. THERE ARE FOUR", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(50, 440, "LEVELS IN TOTAL. COMPLETE ALL THE LEVELS AS FAST AS YOU CAN TO BECOME THE HIGHEST SCORER.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(50, 410, "PRESS P TO PAUSE ANY TIME AND COME BACK LATER TO RESUME PLAY.", GLUT_BITMAP_TIMES_ROMAN_24);

    //iSetColor(253, 126, 0);
    //iSetColor(249, 81, 0);
    iText(50, 350, "TIME TO TIME THE FOLLOWING PERKS WILL APPEAR ON THE GAME SCREEN:", GLUT_BITMAP_TIMES_ROMAN_24);

    iShowBMP(50, 300, "Pics\\Perks\\extra_life.bmp");
    iShowBMP(50, 250, "Pics\\Perks\\slow_ball.bmp");
    iShowBMP(50, 200, "Pics\\Perks\\fireball.bmp");
    iShowBMP(50, 150, "Pics\\Perks\\thru_brick.bmp");
    iShowBMP(50, 100, "Pics\\Perks\\grab_paddle.bmp");
    iShowBMP(50, 50, "Pics\\Perks\\shooting_paddle.bmp");


    iText(100, 308, "GRANTS ONE EXTRA LIFE", GLUT_BITMAP_HELVETICA_18);
    iText(100, 258, "SLOWS DOWN THE BALL", GLUT_BITMAP_HELVETICA_18);
    iText(100, 208, "BALL WILL HIT ADJACENT BLOCKS ALSO", GLUT_BITMAP_HELVETICA_18);
    iText(100, 158, "BLOCKS WILL NOT REFLECT THE BALL", GLUT_BITMAP_HELVETICA_18);
    iText(100, 108, "PADDLE WILL HOLD THE BALL", GLUT_BITMAP_HELVETICA_18);
    iText(100, 58, "BRINGS A SHOOTING PADDLE", GLUT_BITMAP_HELVETICA_18);


    iShowBMP(495, 300, "Pics\\Perks\\mega_ball.bmp");
    iShowBMP(495, 250, "Pics\\Perks\\split_ball.bmp");
    iShowBMP(495, 200, "Pics\\Perks\\expand_paddle.bmp");
    iShowBMP(495, 150, "Pics\\Perks\\shrink_paddle.bmp");

    iText(545, 310, "INCREASES BALL SIZE", GLUT_BITMAP_HELVETICA_18);
    iText(545, 260, "SPLITS BALL INTO TWO", GLUT_BITMAP_HELVETICA_18);
    iText(545, 210, "INCREASES PADDLE SIZE", GLUT_BITMAP_HELVETICA_18);
    iText(545, 160, "DECREASES PADDLE SIZE", GLUT_BITMAP_HELVETICA_18);


    iShowBMP(820, 300, "Pics\\Perks\\super_shrink.bmp");
    iShowBMP(820, 250, "Pics\\Perks\\fast_ball.bmp");
    iShowBMP(820, 200, "Pics\\Perks\\shrink_ball.bmp");
    iShowBMP(820, 150, "Pics\\Perks\\falling_bricks.bmp");
    iShowBMP(820, 100, "Pics\\Perks\\kill_paddle.bmp");

    iText(870, 308, "SHRINKS PADDLE TO THE SMALLEST SIZE", GLUT_BITMAP_HELVETICA_18);
    iText(870, 258, "INCREASES BALL SPEED", GLUT_BITMAP_HELVETICA_18);
    iText(870, 208, "DECREASES BALL SIZE", GLUT_BITMAP_HELVETICA_18);
    iText(870, 158, "BLOCKS LOWER DOWN", GLUT_BITMAP_HELVETICA_18);
    iText(870, 108, "ENDS THE GAME", GLUT_BITMAP_HELVETICA_18);
}

void drawGamePage() {
//    iSetColor(192, 192, 192);
//    iFilledRectangle(0, 0, width, height);
    int i;
    iShowBMP(0, 0, "Pics\\Background\\01.bmp");
    iShowBMP(10, 0, "Pics\\Background\\Wall.bmp");
    iShowBMP(width - 10 - 15, 0, "Pics\\Background\\Wall.bmp");
    drawMaze();
    drawPaddle();
    drawBall();
    if (paddle.isShoot) drawShootingBall();
    drawScoreBar();

//    for (i = 0; i < 18; i++) {
//        if (perks[i].isShow) {
//            drawPerks((Perk_name)i);
//        }
//    }

    if (game_state.isOver) {
        iShowBMP2(325, 217, "Pics\\Background\\game_over.bmp", 0xffffff);
    }
    else if (game_state.isLevelUp) {
        iShowBMP2(325, 217, "Pics\\Background\\level_up.bmp", 0xffffff);
    }
    else if (game_state.isWon) {
        iShowBMP2(325, 217, "Pics\\Background\\won.bmp", 0xffffff);
    }
}

void drawBlock(Block *b) {
    iSetColor(0, 0, 0);
    iFilledRectangle(b->body.left, b->body.bottom, b->body.dx, b->body.dy);
    if (!b->isBrick) iSetColor(b->color.r, b->color.g, b->color.b);
    else iSetColor(b->color.r / 2, b->color.g / 2, b->color.b / 2);
    iFilledRectangle(b->body.left + b->border, b->body.bottom + b->border, b->body.dx - 2 * b->border, b->body.dy - 2 * b->border);
}

void drawMaze() {
    int cnt, i;
    for (cnt = 0; cnt < TOTAL_BLOCKS; cnt++) {
        if (all_blocks[currLevel - 1][cnt].isShow) {
            drawBlock(&all_blocks[currLevel - 1][cnt]);
        }
//        if (all_blocks[currLevel - 1][cnt].perk.perk_name && all_blocks[currLevel - 1][cnt].perk.isShow) {
//            drawPerks(&all_blocks[currLevel - 1][cnt].perk);
//        }
    }
    for (i = 0; i < TOTAL_PERKS; i++) {
        if (perks[i].isShow) {
            drawPerks(&perks[i]);
        }
    }
}

void drawShootingBall() {
    int i;
    //if (shooting_ball[i].isShow) {
        for (i = 0; i < 2; i++) {
            iSetColor(shooting_ball[i].color.r, shooting_ball[i].color.g, shooting_ball[i].color.b);
            iFilledCircle(shooting_ball[i].x, shooting_ball[i].y, shooting_ball[i].r, 10);
        }
    //}
}

void moveShootingBall() {
    int i;
    if (paddle.isShoot && !shooting_ball[0].isPaused) {
        for (i = 0; i < 2; i++) {
            shooting_ball[i].y += shooting_ball[i].dy;
            if (shooting_ball[i].y > height) {
                shooting_ball[i].y = 30;
                shooting_ball[i].isPaused = 1;
            }
            shootingBlockInteraction(&shooting_ball[i].x, &shooting_ball[i].y, i);
        }
    }
}

void drawPaddle() {
    //iSetColor(paddle.color.r, paddle.color.g, paddle.color.b);
    //iFilledRectangle(paddle.left, paddle.bottom, paddle.width, paddle.height);
    char flag = 0;
    int i;
    if (!paddle.isShoot) {
        for (i = 0; i < ball_sz; i++) {
            if (ball[i].isPaused) {
                flag = 1;
                break;
            }
        }
        if (flag || paddle.isGrab) {
            switch(paddle.scale) {
                case -2:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\grab_paddle_0.5x.bmp", 0);
                    break;
                case -1:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\grab_paddle_0.67x.bmp", 0);
                    break;
                case 0:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\grab_paddle.bmp", 0);
                    break;
                case 1:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\grab_paddle_1.5x.bmp", 0);
                    break;
                case 2:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\grab_paddle_2x.bmp", 0);
                    break;
                default:
                    break;
            }
        }
        else {
            switch(paddle.scale) {
                case -2:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle_0.5x.bmp", 0);
                    break;
                case -1:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle_0.67x.bmp", 0);
                    break;
                case 0:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle.bmp", 0);
                    break;
                case 1:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle_1.5x.bmp", 0);
                    break;
                case 2:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle_2x.bmp", 0);
                    break;
                default:
                    break;
            }
        }
    }
    else {
        //shooting paddle
        for (i = 0; i < ball_sz; i++) {
            if (ball[i].isPaused) {
                flag = 1;
                break;
            }
        }
        if (flag || paddle.isGrab) {
            switch(paddle.scale) {
                case -2:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_grab_paddle_0.5x.bmp", 0);
                    break;
                case -1:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_grab_paddle_0.67x.bmp", 0);
                    break;
                case 0:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_grab_paddle.bmp", 0);
                    break;
                case 1:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_grab_paddle_1.5x.bmp", 0);
                    break;
                case 2:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_grab_paddle_2x.bmp", 0);
                    break;
                default:
                    break;
            }
        }
        else {
            switch(paddle.scale) {
                case -2:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_paddle_0.5x.bmp", 0);
                    break;
                case -1:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_paddle_0.67x.bmp", 0);
                    break;
                case 0:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_paddle.bmp", 0);
                    break;
                case 1:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_paddle_1.5x.bmp", 0);
                    break;
                case 2:
                    iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\shooting_paddle_2x.bmp", 0);
                    break;
                default:
                    break;
            }
        }
    }
//    if (paddle.scale == 0) iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle.bmp", 0);
//    else if (paddle.scale == 1) iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle_1.5x.bmp", 0);
//    else if (paddle.scale == 2) iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle_2x.bmp", 0);
//    else if (paddle.scale == -1) iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle_0.67x.bmp", 0);
//    else if (paddle.scale == -2) iShowBMP2(paddle.left, paddle.bottom, "Pics\\Paddle\\paddle_0.5x.bmp", 0);
}

void drawBall() {
    int i;
    for (i = 0; i < ball_sz; i++) {
        iSetColor(ball[i].color.r, ball[i].color.g, ball[i].color.b);
        iFilledCircle(ball[i].x, ball[i].y, ball[i].r, 10);
    }
}

void changeSpeed() {
    if (!game_state.isPaused && !game_state.isOver && !game_state.isWon) {
        speed += speed_change;
    }
}

void moveBall() {
    int i, j, k;
    double x, y;
    for (i = 0; i < ball_sz; i++) {
        if (!ball[i].isPaused && !game_state.isPaused && !game_state.isOver && !game_state.isWon) {
            x = ball[i].x + ball[i].dx;
            y = ball[i].y + ball[i].dy;

            if (x > width - 25) {
                ball[i].dx = -ball[i].dx;
                x = width - 25 - ball[i].r;
            }
            else if (x < 25) {
                ball[i].dx = -ball[i].dx;
                x = 25 + ball[i].r;
            }
            if (y > height) {
                ball[i].dy = -ball[i].dy;
                y = height - ball[i].r;
            }
            else if (y < 0) {
    //        ball[0].dy = -ball[0].dy;
    //        y = ball[0].r;

                if (!i) {
//                    for (j = 1; j < ball_sz; j++) {
//                        ball[j - 1] = ball[j];
//                    }
//                    ball_sz--;

                    if (ball_sz == 1) {
//                        x = paddle.left + paddle.width * (7 / 12.0);
//                        y = paddle.bottom + paddle.height + ball[i].r;
//                        ball[i].dx = speed * cos(75 * (PI / 180));
//                        ball[i].dy = speed * sin(75 * (PI / 180));
//                        ball[i].isPaused = 1;
                        game_state.life--;
                        if (game_state.life < 0) {
                            //printf("test 3\n");
                            game_state.isOver = 1;
                            high_score[10].level = currLevel - 1;
                            continue;
                        }
                        resetBall();
                        for (j = 0; j < perk_sz; j++) {
                            if (perks[i].isShow)
                                perks[i].isShow = 0;
                        }
                        paddle.scale = 0;
                        paddle.isGrab = 0;
                        paddle.isShoot = 0;
                        continue;
//                        printf("ball reset done\n");
//                        printf("%lf %lf\n", ball[i].x, ball[i].y);
                    }
                    else {
                        /*
                            ball_sz implies all balls from 0 to sz (exclusive) are true
                        */
                        for (j = 1; j < ball_sz; j++) {
                            ball[j - 1] = ball[j];
                        }
                        ball_sz--;
                        i--; //ball[i] has been changed, so need to be checked again
                        continue;
                    }
                }
                else {
                    for (j = i + 1; j < ball_sz; j++) {
                        ball[j - 1] = ball[j];
                    }
                    ball_sz--;
                    i--;
                    continue;
                }
            }

            paddleInteraction(&x, &y, i);
            blockInteraction(&x, &y, i);

            ball[i].x = x;
            ball[i].y = y;

            //printf("This should not happen\n");
        }
    }
}

void paddleInteraction(double *x, double *y, int i) {
    double angle, dif;

    if (*y < paddle.bottom + paddle.height && *x > paddle.left && *x < paddle.left + paddle.width && *y > paddle.bottom) {
        dif = paddle.left + paddle.width - *x;
        angle = (dif / paddle.width) * PI;

        ball[i].dx = speed * cos(angle);
        ball[i].dy = speed * sin(angle);
        *y = paddle.bottom + paddle.height + ball[i].r;
        if (paddle.isGrab) {
            ball[i].isPaused = 1;
            ball[i].x = *x;
        }
    }
//    else if (*y < paddle.bottom + paddle.height) {
//
//    }

}

void shootingBlockInteraction(double *x, double *y, int i) {
    int cnt, j;
    for (cnt = 0; cnt < TOTAL_BLOCKS; cnt++) {
        if (all_blocks[currLevel - 1][cnt].isShow) {
            if (*x > all_blocks[currLevel - 1][cnt].body.left && *x < all_blocks[currLevel - 1][cnt].body.left + block_width - block_border) {
                if (*y > all_blocks[currLevel - 1][cnt].body.bottom && *y < all_blocks[currLevel - 1][cnt].body.bottom + block_height - block_border) {
                    if (!all_blocks[currLevel - 1][cnt].isBrick) {
                        all_blocks[currLevel - 1][cnt].isShow = 0;
                        game_state.score += (int)speed - 2;
                        game_state.block_count++;
                        if (game_state.block_count == block_count[currLevel - 1]) {
                            //level up
                            //printf("Before %lf\n", ball[0].y);
                            game_state.block_count = 0;
                            ball_sz = 1;
                            resetBall();
                            *y = ball[0].y;
                            for (j = 0; j < perk_sz; j++) {
                                if (perks[i].isShow)
                                    perks[i].isShow = 0;
                            }
                            paddle.scale = 0;
                            paddle.isGrab = 0;
                            paddle.isShoot = 0;
                            for (j = 0; j < 2; j++) {
                                shooting_ball[i].isShow = 0;
                                shooting_ball[i].isPaused = 1;
                                shooting_ball[i].y = 30;
                            }
                            shooting_ball[0].x = paddle.left + paddle.width * 0.072;
                            shooting_ball[1].x = paddle.left + paddle.width - paddle.width * 0.072;
                            currLevel++;
                            if (currLevel > LEVELS) {
                                currLevel--;
                                game_state.isWon = 1;
                                high_score[10].level = LEVELS;
                            }
                            else {
                                game_state.isLevelUp = 1;
                                game_state.block_count = 0;
                                perk_sz = 0;
                            }
                            continue;
                            //printf("After %lf\n", ball[0].y);
                        }

                        if (game_state.block_count == perk_timing[perk_sz]) {
                            perks[perk_sz].isShow = 1;
                            perks[perk_sz].perk_name = perk_show[perk_sz];
                            perks[perk_sz].bottom = all_blocks[currLevel - 1][cnt].body.bottom;
                            perks[perk_sz].left = all_blocks[currLevel - 1][cnt].body.left;
                            perk_sz++;
                        }
                    }
                    else {
                        all_blocks[currLevel - 1][cnt].isBrick = 0;
                        game_state.score += (int)speed / 2 - 2;
                    }
                }
            }
        }
    }
}

void checkFireball(int cnt, double *y, int i) {
    int j;
    if (!all_blocks[currLevel - 1][cnt].isBrick) {
        //printf("cnt - 1\n");
        all_blocks[currLevel - 1][cnt].isShow = 0;
        game_state.score += (int)speed - 10;
        game_state.block_count++;
        if (game_state.block_count == block_count[currLevel - 1]) {
            //level up
            //printf("Before %lf\n", ball[0].y);
            game_state.block_count = 0;
            ball_sz = 1;
            resetBall();
            *y = ball[0].y;
            for (j = 0; j < perk_sz; j++) {
                if (perks[i].isShow)
                    perks[i].isShow = 0;
            }
            paddle.scale = 0;
            paddle.isGrab = 0;
            paddle.isShoot = 0;
            for (j = 0; j < 2; j++) {
                shooting_ball[i].isShow = 0;
                shooting_ball[i].isPaused = 1;
                shooting_ball[i].y = 30;
            }
            shooting_ball[0].x = paddle.left + paddle.width * 0.072;
            shooting_ball[1].x = paddle.left + paddle.width - paddle.width * 0.072;
            currLevel++;
            if (currLevel > LEVELS) {
                currLevel--;
                game_state.isWon = 1;
                high_score[10].level = LEVELS;
            }
            else {
                game_state.isLevelUp = 1;
                game_state.block_count = 0;
                perk_sz = 0;
            }
            //return;
            //printf("After %lf\n", ball[0].y);
        }

        if (game_state.block_count == perk_timing[perk_sz]) {
            perks[perk_sz].isShow = 1;
            perks[perk_sz].perk_name = perk_show[perk_sz];
            perks[perk_sz].bottom = all_blocks[currLevel - 1][cnt].body.bottom;
            perks[perk_sz].left = all_blocks[currLevel - 1][cnt].body.left;
            perk_sz++;
        }
    }
    else {
        all_blocks[currLevel - 1][cnt].isBrick = 0;
        game_state.score += (int)speed / 2 - 2;
    }
}

void blockInteraction(double *x, double *y, int i) {
    int cnt, j;
    for (cnt = 0; cnt < TOTAL_BLOCKS; cnt++) {
        if (all_blocks[currLevel - 1][cnt].isShow) {
            if (*x > all_blocks[currLevel - 1][cnt].body.left && *x < all_blocks[currLevel - 1][cnt].body.left + block_width - block_border) {
                if (*y > all_blocks[currLevel - 1][cnt].body.bottom && *y < all_blocks[currLevel - 1][cnt].body.bottom + block_height - block_border) {
                    if (!ball[i].isThru) {
                        if (ball[i].x > all_blocks[currLevel - 1][cnt].body.left && ball[i].x < all_blocks[currLevel - 1][cnt].body.left + block_width - block_border) {
                            ball[i].dy = -ball[i].dy;
                        }
                        else {
                            ball[i].dx = -ball[i].dx;
                        }
                    }
                    if (!all_blocks[currLevel - 1][cnt].isBrick) {
                        all_blocks[currLevel - 1][cnt].isShow = 0;
                        game_state.score += (int)speed;
                        game_state.block_count++;
                        if (game_state.block_count == block_count[currLevel - 1]) {
                            //level up
                            //printf("Before %lf\n", ball[0].y);
                            game_state.block_count = 0;
                            ball_sz = 1;
                            resetBall();
                            *y = ball[0].y;
                            for (j = 0; j < perk_sz; j++) {
                                if (perks[i].isShow)
                                    perks[i].isShow = 0;
                            }
                            paddle.scale = 0;
                            paddle.isGrab = 0;
                            paddle.isShoot = 0;
                            for (j = 0; j < 2; j++) {
                                shooting_ball[i].isShow = 0;
                                shooting_ball[i].isPaused = 1;
                                shooting_ball[i].y = 30;
                            }
                            shooting_ball[0].x = paddle.left + paddle.width * 0.072;
                            shooting_ball[1].x = paddle.left + paddle.width - paddle.width * 0.072;
                            currLevel++;
                            if (currLevel > LEVELS) {
                                currLevel--;
                                game_state.isWon = 1;
                                high_score[10].level = LEVELS;
                            }
                            else {
                                game_state.isLevelUp = 1;
                                game_state.block_count = 0;
                                perk_sz = 0;
                            }
                            continue;
                            //printf("After %lf\n", ball[0].y);
                        }

                        if (game_state.block_count == perk_timing[perk_sz]) {
                            perks[perk_sz].isShow = 1;
                            perks[perk_sz].perk_name = perk_show[perk_sz];
                            perks[perk_sz].bottom = all_blocks[currLevel - 1][cnt].body.bottom;
                            perks[perk_sz].left = all_blocks[currLevel - 1][cnt].body.left;
                            perk_sz++;
                        }
                    }
                    else {
                        all_blocks[currLevel - 1][cnt].isBrick = 0;
                        game_state.score += (int)speed / 2;
                    }
                    if (ball[i].isFire) {
                        //Do for adjacent blocks
                        if (cnt - 1 >= 0 && all_blocks[currLevel - 1][cnt - 1].body.bottom == all_blocks[currLevel - 1][cnt].body.bottom) {
                            checkFireball(cnt - 1, y, i);
                        }
                        if (cnt + 1 < TOTAL_BLOCKS && all_blocks[currLevel - 1][cnt + 1].body.bottom == all_blocks[currLevel - 1][cnt].body.bottom) {
                            checkFireball(cnt + 1, y, i);
                        }
                        if (cnt - MAX_BLOCKS_PER_ROW >= 0 && all_blocks[currLevel - 1][cnt - MAX_BLOCKS_PER_ROW].body.left == all_blocks[currLevel - 1][cnt].body.left) {
                            checkFireball(cnt - MAX_BLOCKS_PER_ROW, y, i);
                        }
                        if (cnt + MAX_BLOCKS_PER_ROW < TOTAL_BLOCKS && all_blocks[currLevel - 1][cnt + MAX_BLOCKS_PER_ROW].body.left == all_blocks[currLevel - 1][cnt].body.left) {
                            checkFireball(cnt + MAX_BLOCKS_PER_ROW, y, i);
                        }
                    }
                }
            }
        }
    }
}

void gameTime() {
    if (currPage == 1 && !game_state.isPaused && !game_state.isOver && !game_state.isWon) {
        game_state.sec++;
    }
}

void drawScoreBar() {
    char str[20] = {0};
    int hour, minute, second, i, x;
    second = game_state.sec;
    hour = second / 3600;
    second -= hour * 3600;
    minute = second / 60;
    second -= minute * 60;
    if (hour != 0) {
        sprintf(str, "%02d:%02d:%02d", hour, minute, second);
    }
    else {
        sprintf(str, "%02d:%02d", minute, second);
    }
    //iSetColor(255, 255, 255);
    iSetColor(220, 0, 0);
    iText(1170, 600, str, GLUT_BITMAP_TIMES_ROMAN_24);

    iSetColor(0, 140, 0);
    sprintf(str, "LEVEL %d", currLevel);
    iText(295, 600, str, GLUT_BITMAP_TIMES_ROMAN_24);

    iSetColor(253, 126, 0);
    sprintf(str, "SCORE: %5d", game_state.score);
    iText(50, 600, str, GLUT_BITMAP_TIMES_ROMAN_24);

    for (i = 0, x = 1005; i < game_state.life; i++, x -= 135) {
        iShowBMP2(x, 600, "Pics\\Paddle\\paddle.bmp", 0);
    }
}

int highScoreComparator(const void *i, const void *j) {
    High_score a, b;
    a = *(High_score*)i;
    b = *(High_score*)j;
    if (a.level > b.level) {
        return -1;
    }
    if (a.level < b.level) {
        return 1;
    }
    if (a.level == LEVELS) {
        return a.time - b.time;
    }
    if (a.score != b.score) {
        return b.score - a.score;
    }
    return a.time - b.time;
//    if (a.time == 0) {
//        return 1;
//    }
//    if (b.time == 0) {
//        return -1;
//    }
//    if (a.time < b.time) {
//        return -1;
//    }
//    if (a.time > b.time) {
//        return 1;
//    }
//    return b.score - a.score;
    //return a.time - b.time;
}

void gameOverTimeCount() {
    //game_state.isOver = 0;
    if (game_state.isOver) {
        //printf("Test 1\n");
        game_state.game_over_time--;
        if (game_state.game_over_time < 0) {
            //game_state.game_over_time = 3;
            //printf("Test 2\n");
            game_state.isOver = 0;
            game_state.life = 3;
            //game_state.game_over_time = 3;
            //game_state.isWon = 0;
            saveGameInfo();
            savePerkInfo();
            //playMusic();
            PlaySound(NULL, 0, 0);
            PlaySound("Sound\\0.wav", NULL, SND_ASYNC | SND_LOOP);
            currPage = 5;
        }
    }
    else if (game_state.isLevelUp) {
        game_state.game_over_time--;
        if (game_state.game_over_time < 0) {
            game_state.game_over_time = 3;
            game_state.isLevelUp = 0;
        }
    }
    else if (game_state.isWon) {
        game_state.game_over_time--;
        if (game_state.game_over_time < 0) {
            //game_state.game_over_time = 3;
            game_state.isWon = 0;
            game_state.life = 3;
            saveGameInfo();
            PlaySound(NULL, 0, 0);
            PlaySound("Sound\\0.wav", NULL, SND_ASYNC | SND_LOOP);
            currPage = 5;
        }
    }
}

void movePerk() {
    int i, j, cnt;
    if (!game_state.isPaused && !game_state.isOver && !game_state.isWon) {
        for (i = 0; i < TOTAL_PERKS; i++) {
            if (perks[i].isShow) {
                perks[i].bottom += perk_dy;

                if (perks[i].bottom <= paddle.bottom + paddle.height && perks[i].left + 17 >= paddle.left && perks[i].left + 17 <= paddle.left + paddle.width) {
                    game_state.score += 50;
                    switch(perks[i].perk_name) {
                        //case EIGHT_BALL:

                        case EXPAND_PADDLE:
                            expandPaddle();
                            break;
                        case EXTRA_LIFE:
                            game_state.life++;
                            break;
                        case FAST_BALL:
                            speed += 5;
                            break;
                        case FALLING_BRICKS:
                            for (cnt = 0; cnt < TOTAL_BLOCKS; cnt++) {
                                if (all_blocks[currLevel - 1][cnt].isShow) {
                                    all_blocks[currLevel - 1][cnt].body.bottom -= block_height;
                                }
                            }
                            break;
                        case FIREBALL:
                            for (j = 0; j < ball_sz; j++) {
                                ball[j].isFire = 1;
                                ball[j].color = shooting_color;
                            }
                            break;
                        case GRAB_PADDLE:
                            paddle.isGrab = 1;
                            break;
                        case KILL_PADDLE:
                            //game_state.isOver = 1;
    //                        game_state.game_over_time = 0;
    //                        break;
                            game_state.life--;
                            if (game_state.life < 0) {
                                game_state.isOver = 1;
                            }
                            resetBall();
                            for (j = 0; j < perk_sz; j++) {
                                if (perks[i].isShow)
                                    perks[i].isShow = 0;
                            }
                            paddle.scale = 0;
                            paddle.isGrab = 0;
                            paddle.isShoot = 0;
                            ball_sz = 1;
                            break;
                        case MEGA_BALL:
                            for (j = 0; j < ball_sz; j++) {
                                ball[j].r = 10;
                            }
                            break;
                        case THRU_BRICK:
                            for (j = 0; j < ball_sz; j++) {
                                ball[j].isThru = 1;
                                ball[j].color = ball_thru_color;
    //                            ball[j].color.r = 0;
    //                            ball[j].color.g = 185;
    //                            ball[j].color.b = 185;
                            }
                            break;
                        case SHOOTING_PADDLE:
                            paddle.isShoot = 1;
                            break;
                        case SHRINK_BALL:
                            for (j = 0; j < ball_sz; j++) {
                                ball[j].r = 4;
                            }
                            break;
                        case SHRINK_PADDLE:
                            shrinkPaddle();
                            break;
                        case SLOW_BALL:
                            speed -= 5;
                            break;
                        case SPLIT_BALL:
    //                        ball_sz = 2;
    //                        ball[1] = ball[0];
    //                        ball[1].dx = -ball[1].dx;
                            ball_sz *= 2;
                            for (j = ball_sz / 2; j < ball_sz; j++) {
                                ball[j] = ball[j - ball_sz / 2];
                                ball[j].dx = -ball[j].dx;
                            }
                            break;
                        case SUPER_SHRINK:
                            paddle.scale = -2;
                            break;
                        default:
                            break;
                    }
                    perks[i].isShow = 0;
                }
                else if (perks[i].bottom < 0) {
                    perks[i].isShow = 0;
                }
            }
        }
    }
}

void expandPaddle() {
    paddle.scale++;
    if (paddle.scale == -1) {
        paddle.width = 83;
        paddle.left += 10;
    }
    else if (paddle.scale == 0) {
        paddle.width = 125;
        paddle.left += 21;
    }
    else if (paddle.scale == 1) {
        paddle.width = 187;
        paddle.left += 31;
    }
    else if (paddle.scale == 2) {
        paddle.width = 250;
        paddle.left += 31;
    }

    if (paddle.left < 25) paddle.left = 25;
    else if (paddle.left + paddle.width > width - 25) paddle.left = width - 25 - paddle.width;
}

void shrinkPaddle() {
    paddle.scale--;
    if (paddle.scale == -2) {
        paddle.width = 62;
        paddle.left -= 10;
    }
    else if (paddle.scale == -1) {
        paddle.width = 83;
        paddle.left -= 21;
    }
    else if (paddle.scale == 0) {
        paddle.width = 125;
        paddle.left -= 31;
    }
    else if (paddle.scale == 1) {
        paddle.width = 187;
        paddle.left -= 31;
    }

    if (paddle.left < 25) paddle.left = 25;
    else if (paddle.left + paddle.width > width - 25) paddle.left = width - 25 - paddle.width;
}

void resetBall() {
//    int i;
//    for (i = 0; i < ball_sz; i++) {
    int i = 0;
    ball[i].isShow = 1;
    ball[i].r = ball_def_rad;
    paddle.scale = 0;
    paddle.isGrab = 0;
    paddle.isShoot = 0;
    paddle.width = 125;
    ball[i].x = paddle.left + paddle.width * (7 / 12.0);
    ball[i].y = paddle.bottom + paddle.height + ball[i].r;
    speed = def_speed;
    ball[i].dx = speed * cos(75 * (PI / 180));
    ball[i].dy = speed * sin(75 * (PI / 180));
    ball[i].color = ball_def_color;
    ball[i].isPaused = 1;
    ball[i].isThru = 0;
//    }
}

void drawCreditsPage() {
    iShowBMP(0, 0, "Pics\\Background\\7.bmp");
    iShowBMP2(25, 580, "Pics\\Background\\back_icon2.bmp", 0);

    iSetColor(0, 179, 179);
    iText(25, 530, "DX-BALL IS A FREEWARE COMPUTER GAME FOR PC FIRST RELEASED IN 1996 BY MICHAEL P. WELCH AND", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(25, 500, "SEUMAS McNALLY. HERE IS A RE-DEVELOPMENT OF THE ORIGINAL GAME, WRITING IT IN C USING OPENGL", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(25, 470, "BASED IGRAPHICS LIBRARY BY MD. ISHRAK AHSAN, LEVEL 1-TERM 1 STUDENT (STUDENT ID: 1905045)", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(25, 440, "IN THE DEPARTMENT OF COMPUTER SCIENCE, BUET.", GLUT_BITMAP_TIMES_ROMAN_24);

    iText(25, 380, "DIFFERENT IMAGES USED IN THIS APPLICATION HAVE BEEN TAKEN FROM-", GLUT_BITMAP_TIMES_ROMAN_24);
    iFilledCircle(30, 350, 5);
    iText(45, 345, "https://www.pinterest.com/pin/254946028894494159/", GLUT_BITMAP_HELVETICA_18);
    iFilledCircle(30, 320, 5);
    iText(45, 315, "https://wallpapercave.com/black-gradient-wallpaper", GLUT_BITMAP_HELVETICA_18);
    iFilledCircle(30, 290, 5);
    iText(45, 285, "https://wallpaperaccess.com/dark-brick", GLUT_BITMAP_HELVETICA_18);
    iFilledCircle(30, 260, 5);
    iText(45, 255, "https://www.publicdomainpictures.net/en/view-image.php?image=277966&picture=dark-blue-glitter-background", GLUT_BITMAP_HELVETICA_18);

    iText(25, 190, "BACKGROUND MUSIC USED IN THIS APPLICATION ARE-", GLUT_BITMAP_TIMES_ROMAN_24);
    iFilledCircle(30, 160, 5);
    iText(45, 155, "CHILE KOTHAR SHEPAI - ARTCELL", GLUT_BITMAP_HELVETICA_18);
    iFilledCircle(30, 130, 5);
    iText(45, 125, "EI BIDAYE - ARTCELL", GLUT_BITMAP_HELVETICA_18);
    iFilledCircle(30, 100, 5);
    iText(45, 95, "BISHONNO SHUNDOR - POPEYE BANGLADESH", GLUT_BITMAP_HELVETICA_18);
    iFilledCircle(30, 70, 5);
    iText(45, 65, "HARIYE GIYECHI - ARNOB", GLUT_BITMAP_HELVETICA_18);
    iFilledCircle(30, 40, 5);
    iText(45, 35, "PURNOTA - WARFAZE", GLUT_BITMAP_HELVETICA_18);
}

void savePerkInfo() {
    FILE *write = NULL;
    if ((write = fopen("Files\\load_state\\perk_info.txt", "wb")) == NULL) {
        fprintf(stderr, "perk_info.txt could not be opened for writing\n");
        exit(1);
    }
    if (fwrite(&perk_sz, sizeof(perk_sz), 1, write) != 1) {
        fprintf(stderr, "perk_sz could not be written\n");
        exit(1);
    }
    if (fwrite(perk_timing, sizeof(perk_timing), 1, write) != 1) {
        fprintf(stderr, "perk_timing could not be written\n");
        exit(1);
    }
    if (fwrite(perk_show, sizeof(perk_show), 1, write) != 1) {
        fprintf(stderr, "perk_show could not be written\n");
        exit(1);
    }
    if (fwrite(perks, sizeof(perks), 1, write) != 1) {
        fprintf(stderr, "perks could not be written\n");
        exit(1);
    }
    if (fclose(write)) {
        fprintf(stderr, "perk_info.txt could not be closed after writing\n");
        exit(1);
    }
}

void loadPerkInfo() {
    FILE *read = NULL;
    if ((read = fopen("Files\\load_state\\perk_info.txt", "rb")) == NULL) {
        fprintf(stderr, "perk_info.txt could not be opened for reading\n");
        exit(1);
    }
    if (fread(&perk_sz, sizeof(perk_sz), 1, read) != 1) {
        fprintf(stderr, "perk_sz could not be read\n");
        exit(1);
    }
    if (fread(perk_timing, sizeof(perk_timing), 1, read) != 1) {
        fprintf(stderr, "perk_timing could not be read\n");
        exit(1);
    }
    if (fread(perk_show, sizeof(perk_show), 1, read) != 1) {
        fprintf(stderr, "perk_show could not be read\n");
        exit(1);
    }
    if (fread(perks, sizeof(perks), 1, read) != 1) {
        fprintf(stderr, "perks could not be read\n");
        exit(1);
    }
    if (fclose(read)) {
        fprintf(stderr, "perk_info.txt could not be closed after reading\n");
        exit(1);
    }
}

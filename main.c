//Header Files
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h> 
#include <time.h>
#include <ctype.h>

//Constants
#define red "red";
#define yellow "yello";
#define green "green";
#define blue "blue";
#define purple "purpl";
#define white "white";
#define black "black";
#define right 77
#define left 75
#define up 72
#define down 80

/*Functions*/
/*---------------------------------*/
//Main
int start();
int set_rows_main();
int start_check_s();

//Game Play
int game_play();

//Setting
int gotomain();
int setting();
int set_rows_setting();
int setting_s();
int setting_r();
int setting_w();
int change_setting();
int setting_save();

//Quit
int quit_game();

//Thread
int start_work_thread();
DWORD WINAPI print(LPVOID);
DWORD WINAPI get_arrow(LPVOID);

//Public
int reset_rows();
int reset_setting_variables();
int setting_color(char *st);
int color(int c_t, int c_b);
/*---------------------------------*/

/*Variables*/
/*---------------------------------*/
//Local Variables
char display[15][70];
int start_check = 1; //1 : Play, 2 : Setting, 3 : Quit
int display_type = 1; //1 : Main, 2 : Play, 3 : Setting
int setting_n = 0; //1 ~ 5 : Settings, 6 : Go Back Button

//Structs
struct setting_rt {
    char sound_effect[10];
    char back_music[10];
    char back_color[10];
    char letter_color[10];
    char auto_screen[10];
}set;
struct set_ch {
    char s1[30];
    char s2[30];
    char s3[30];
    char s4[30];
    char s5[30];
    char s6[30];
    char s7[30];
    char s8[30];
    char s9[30];
    char s10[30];
    char s11[30];
}ch;

//File
FILE* options;
/*---------------------------------*/

int reset_rows() {
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 70; j++) {
            display[i][j] = ' ';
        }
    }
}

int reset_setting_variables() {
    strcpy(ch.s1, " ");
    strcpy(ch.s2, " ");
    strcpy(ch.s3, " ");
    strcpy(ch.s4, " ");
    strcpy(ch.s5, " ");
    strcpy(ch.s6, " ");
    strcpy(ch.s7, " ");
    strcpy(ch.s8, " ");
    strcpy(ch.s9, " ");
    strcpy(ch.s10, " ");
    strcpy(ch.s11, " ");
    
    strcpy(set.sound_effect, " ");
    strcpy(set.back_music, " ");
    strcpy(set.back_color, " ");
    strcpy(set.letter_color, " ");
    strcpy(set.auto_screen, " ");
}

int setting_color(char *st) {
    int eq = 0;
    char *c1 = red;
    char *c2 = yellow;
    char *c3 = green;
    char *c4 = blue;
    char *c5 = purple;
    char *c6 = white;
    char *c7 = black;

    eq = strcmp(st, c1);
    if(eq == 0) {
        return 1;
    }
    else {
        eq = strcmp(st, c2);
        if(eq == 0) {
            return 2;
        }
        else {
            eq = strcmp(st, c3);
            if(eq == 0) {
                return 3;
            }
            else {
                eq = strcmp(st, c4);
                if(eq == 0) {
                    return 4;
                }
                else {
                    eq = strcmp(st, c5);
                    if(eq == 0) {
                        return 5;
                    }
                    else {
                        eq = strcmp(st, c6);
                        if(eq == 0) {
                            return 6;
                        }
                        else {
                            eq = strcmp(st, c7);
                            if(eq == 0) {
                                return 7;
                            }
                        }
                    }
                }
            }
        }
    }
}

int color(int c_t, int c_b) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c_t | c_b << 4);
    return 0;
}

void main() {
    start();
}

int start() {
    display_type = 1;
    system("title Snake Game - by Lemon");
    system("mode con:cols=70 lines=16");
    reset_rows();
    set_rows_main();
    start_check_s();
    setting_r();
    change_setting();
    reset_setting_variables();
    start_work_thread();
}

int set_rows_main() {
    display[0][30] = 'S';
    display[0][31] = 'N';
    display[0][32] = 'A';
    display[0][33] = 'K';
    display[0][34] = 'E';
    display[0][36] = 'G';
    display[0][37] = 'A';
    display[0][38] = 'M';
    display[0][39] = 'E';

    for (int i = 22; i < 33; i++) {
        display[2][i] = '-';
    }
    for (int i = 37; i < 48; i++) {
        display[2][i] = '-';
    }
    
    display[3][21] = '|';
    display[3][33] = '|';
    display[3][36] = '|';
    display[3][48] = '|';

    display[4][21] = '|';
    display[4][25] = 'P';
    display[4][26] = 'L';
    display[4][27] = 'A';
    display[4][28] = 'Y';
    display[4][29] = '!';
    display[4][33] = '|';
    display[4][36] = '|';
    display[4][39] = 'S';
    display[4][40] = 'E';
    display[4][41] = 'T';
    display[4][42] = 'T';
    display[4][43] = 'I';
    display[4][44] = 'N';
    display[4][45] = 'G';
    display[4][48] = '|';

    display[5][21] = '|';
    display[5][33] = '|';
    display[5][36] = '|';
    display[5][48] = '|';

    for (int i = 22; i < 33; i++) {
        display[6][i] = '-';
    }
    for (int i = 37; i < 48; i++) {
        display[6][i] = '-';
    }

    for (int i = 25; i < 45; i++) {
        display[8][i] = '-';
    }

    display[9][24] = '|';
    display[9][45] = '|';

    display[10][24] = '|';
    display[10][28] = 'Q';
    display[10][29] = 'U';
    display[10][30] = 'I';
    display[10][31] = 'T';
    display[10][33] = 'T';
    display[10][34] = 'H';
    display[10][35] = 'I';
    display[10][36] = 'S';
    display[10][38] = 'G';
    display[10][39] = 'A';
    display[10][40] = 'M';
    display[10][41] = 'E';
    display[10][45] = '|';

    display[11][24] = '|';
    display[11][45] = '|';

    for (int i = 25; i < 45; i++) {
        display[12][i] = '-';
    }

    display[14][28] = '_';
    display[14][29] = 'M';
    display[14][30] = 'a';
    display[14][31] = 'd';
    display[14][32] = 'e';
    display[14][34] = 'b';
    display[14][35] = 'y';
    display[14][37] = 'L';
    display[14][38] = 'e';
    display[14][39] = 'm';
    display[14][40] = 'o';
    display[14][41] = 'n';
}

int start_check_s() {
    if (start_check == 1) {
        for (int i = 22; i < 33; i++) {
            display[3][i] = '*';
            display[5][i] = '*';
        }
        for (int i = 37; i < 48; i++) {
            display[3][i] = ' ';
            display[5][i] = ' ';
        }
        for (int i = 25; i < 45; i++) {
            display[9][i] = ' ';
            display[11][i] = ' ';
        }
    }
    else if (start_check == 2) {
        for (int i = 22; i < 33; i++) {
            display[3][i] = ' ';
            display[5][i] = ' ';
        }
        for (int i = 37; i < 48; i++) {
            display[3][i] = '*';
            display[5][i] = '*';
        }
        for (int i = 25; i < 45; i++) {
            display[9][i] = ' ';
            display[11][i] = ' ';
        }
    }
    else if (start_check == 3) {
        for (int i = 22; i < 33; i++) {
            display[3][i] = ' ';
            display[5][i] = ' ';
        }
        for (int i = 37; i < 48; i++) {
            display[3][i] = ' ';
            display[5][i] = ' ';
        }
        for (int i = 25; i < 45; i++) {
            display[9][i] = '*';
            display[11][i] = '*';
        }
    }
}

int start_work_thread() {
    HANDLE print_t;
    DWORD threadId1;
    int i_t;
    print_t = CreateThread(NULL, 0, print, (LPVOID)i_t, 0, &threadId1);
    if (print_t) CloseHandle(print_t);
    HANDLE get_arrow_t;
    DWORD threadId2;
    int j_t;
    get_arrow_t = CreateThread(NULL, 0, get_arrow, (LPVOID)j_t, 0, &threadId2);
    if (get_arrow_t) CloseHandle(get_arrow_t);
    while(1) Sleep(1000);
    return EXIT_SUCCESS;
}

DWORD WINAPI print(LPVOID n) {
    static HANDLE g_hScreen[2];
    while(1) {
        g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

        DWORD dw;
        COORD CursorPosition = {0, 0};
        SetConsoleCursorPosition(g_hScreen[0], CursorPosition);
        WriteFile(g_hScreen[0], display, strlen(*display), &dw, NULL);
        SetConsoleActiveScreenBuffer(g_hScreen[0]);
    }
}

DWORD WINAPI get_arrow(LPVOID n) {
    int gch = 0;
    while(1) {
        gch = _getch();
        if (gch == 224) {
            gch = _getch();
            if (display_type == 1) {
                switch (gch) {
                    case right:
                        if (start_check == 1) start_check = 2;
                        else if (start_check == 2) start_check = 3;
                        else if (start_check == 3) start_check = 1;
                        break;
                    case left:
                        if (start_check == 1) start_check = 3;
                        else if (start_check == 2) start_check = 1;
                        else if (start_check == 3) start_check = 2;            
                        break;
                    case up:
                        start_check = 1;
                        break;
                    case down:
                        start_check = 3;
                        break;
                }
                start_check_s();
            }
            else if (display_type == 2) {

            }
            else if (display_type == 3) {
                char *t = "True";
                switch (gch) {
                    case down:
                        if (setting_n == 6) setting_n = 1;
                        else setting_n++;
                        break;
                    case up:
                        if (setting_n == 1) setting_n = 6;
                        else setting_n--;
                        break;
                    case left:
                        if (setting_n == 1) {
                            int eq = strcmp(set.sound_effect, t);
                            if (eq == 0) {
                                strcpy(set.sound_effect, "False");
                                display[2][40] = 'F';
                                display[2][41] = 'a';
                                display[2][42] = 'l';
                                display[2][43] = 's';
                                display[2][44] = 'e';
                            }
                            else {
                                strcpy(set.sound_effect, "True");
                                display[2][40] = 'T';
                                display[2][41] = 'r';
                                display[2][42] = 'u';
                                display[2][43] = 'e';
                                display[2][44] = ' ';
                            }
                        }
                        else if (setting_n == 2) {
                            int eq = strcmp(set.back_music, t);
                            if (eq == 0) {
                                strcpy(set.back_music, "False");
                                display[3][40] = 'F';
                                display[3][41] = 'a';
                                display[3][42] = 'l';
                                display[3][43] = 's';
                                display[3][44] = 'e';
                            }
                            else {
                                strcpy(set.back_music, "True");
                                display[3][40] = 'T';
                                display[3][41] = 'r';
                                display[3][42] = 'u';
                                display[3][43] = 'e';
                                display[3][44] = ' ';
                            }
                        }
                        else if (setting_n == 3) {
                            int bc = setting_color(set.back_color);
                            if (bc == 1) {
                                strcpy(set.back_color, "black");
                                display[4][40] = 'B';
                                display[4][41] = 'l';
                                display[4][42] = 'a';
                                display[4][43] = 'c';
                                display[4][44] = 'k';
                                display[4][45] = ' ';
                            }
                            else if (bc == 2) {
                                strcpy(set.back_color, "red");
                                display[4][40] = 'R';
                                display[4][41] = 'e';
                                display[4][42] = 'd';
                                display[4][43] = ' ';
                                display[4][44] = ' ';
                                display[4][45] = ' ';
                            }
                            else if (bc == 3) {
                                strcpy(set.back_color, "yello");
                                display[4][40] = 'Y';
                                display[4][41] = 'e';
                                display[4][42] = 'l';
                                display[4][43] = 'l';
                                display[4][44] = 'o';
                                display[4][45] = 'w';
                            }
                            else if (bc == 4) {
                                strcpy(set.back_color, "green");
                                display[4][40] = 'G';
                                display[4][41] = 'r';
                                display[4][42] = 'e';
                                display[4][43] = 'e';
                                display[4][44] = 'n';
                                display[4][45] = ' ';
                            }
                            else if (bc == 5) {
                                strcpy(set.back_color, "blue");
                                display[4][40] = 'B';
                                display[4][41] = 'l';
                                display[4][42] = 'u';
                                display[4][43] = 'e';
                                display[4][44] = ' ';
                                display[4][45] = ' ';
                            }
                            else if (bc == 6) {
                                strcpy(set.back_color, "purpl");
                                display[4][40] = 'P';
                                display[4][41] = 'u';
                                display[4][42] = 'r';
                                display[4][43] = 'p';
                                display[4][44] = 'l';
                                display[4][45] = 'e';
                            }
                            else if (bc == 7) {
                                strcpy(set.back_color, "white");
                                display[4][40] = 'W';
                                display[4][41] = 'h';
                                display[4][42] = 'i';
                                display[4][43] = 't';
                                display[4][44] = 'e';
                                display[4][45] = ' ';
                            }
                        }
                        else if (setting_n == 4) {
                            int lc = setting_color(set.letter_color);
                            if (lc == 1) {
                                strcpy(set.letter_color, "black");
                                display[5][40] = 'B';
                                display[5][41] = 'l';
                                display[5][42] = 'a';
                                display[5][43] = 'c';
                                display[5][44] = 'k';
                                display[5][45] = ' ';
                            }
                            else if (lc == 2) {
                                strcpy(set.letter_color, "red");
                                display[5][40] = 'R';
                                display[5][41] = 'e';
                                display[5][42] = 'd';
                                display[5][43] = ' ';
                                display[5][44] = ' ';
                                display[5][45] = ' ';
                            }
                            else if (lc == 3) {
                                strcpy(set.letter_color, "yello");
                                display[5][40] = 'Y';
                                display[5][41] = 'e';
                                display[5][42] = 'l';
                                display[5][43] = 'l';
                                display[5][44] = 'o';
                                display[5][45] = 'w';
                            }
                            else if (lc == 4) {
                                strcpy(set.letter_color, "green");
                                display[5][40] = 'G';
                                display[5][41] = 'r';
                                display[5][42] = 'e';
                                display[5][43] = 'e';
                                display[5][44] = 'n';
                                display[5][45] = ' ';
                            }
                            else if (lc == 5) {
                                strcpy(set.letter_color, "blue");
                                display[5][40] = 'B';
                                display[5][41] = 'l';
                                display[5][42] = 'u';
                                display[5][43] = 'e';
                                display[5][44] = ' ';
                                display[5][45] = ' ';
                            }
                            else if (lc == 6) {
                                strcpy(set.letter_color, "purpl");
                                display[5][40] = 'P';
                                display[5][41] = 'u';
                                display[5][42] = 'r';
                                display[5][43] = 'p';
                                display[5][44] = 'l';
                                display[5][45] = 'e';
                            }
                            else if (lc == 7) {
                                strcpy(set.letter_color, "white");
                                display[5][40] = 'W';
                                display[5][41] = 'h';
                                display[5][42] = 'i';
                                display[5][43] = 't';
                                display[5][44] = 'e';
                                display[5][45] = ' ';
                            }
                        }
                        else if (setting_n == 5) {
                            int eq = strcmp(set.auto_screen, t);
                            if (eq == 0) {
                                strcpy(set.auto_screen, "False");
                                display[6][40] = 'F';
                                display[6][41] = 'a';
                                display[6][42] = 'l';
                                display[6][43] = 's';
                                display[6][44] = 'e';
                            }
                            else {
                                strcpy(set.auto_screen, "True");
                                display[6][40] = 'T';
                                display[6][41] = 'r';
                                display[6][42] = 'u';
                                display[6][43] = 'e';
                                display[6][44] = ' ';
                            }
                        }
                        break;
                    case right:
                        if (setting_n == 1) {
                            int eq = strcmp(set.sound_effect, t);
                            if (eq == 0) {
                                strcpy(set.sound_effect, "False");
                                display[2][40] = 'F';
                                display[2][41] = 'a';
                                display[2][42] = 'l';
                                display[2][43] = 's';
                                display[2][44] = 'e';
                            }
                            else {
                                strcpy(set.sound_effect, "True");
                                display[2][40] = 'T';
                                display[2][41] = 'r';
                                display[2][42] = 'u';
                                display[2][43] = 'e';
                                display[2][44] = ' ';
                            }
                        }
                        else if (setting_n == 2) {
                            int eq = strcmp(set.back_music, t);
                            if (eq == 0) {
                                strcpy(set.back_music, "False");
                                display[3][40] = 'F';
                                display[3][41] = 'a';
                                display[3][42] = 'l';
                                display[3][43] = 's';
                                display[3][44] = 'e';
                            }
                            else {
                                strcpy(set.back_music, "True");
                                display[3][40] = 'T';
                                display[3][41] = 'r';
                                display[3][42] = 'u';
                                display[3][43] = 'e';
                                display[3][44] = ' ';
                            }
                        }
                        else if (setting_n == 3) {
                            int bc = setting_color(set.back_color);
                            if (bc == 1) {
                                strcpy(set.back_color, "yello");
                                display[4][40] = 'Y';
                                display[4][41] = 'e';
                                display[4][42] = 'l';
                                display[4][43] = 'l';
                                display[4][44] = 'o';
                                display[4][45] = 'w';
                            }
                            else if (bc == 2) {
                                strcpy(set.back_color, "green");
                                display[4][40] = 'G';
                                display[4][41] = 'r';
                                display[4][42] = 'e';
                                display[4][43] = 'e';
                                display[4][44] = 'n';
                                display[4][45] = ' ';
                            }
                            else if (bc == 3) {
                                strcpy(set.back_color, "blue");
                                display[4][40] = 'B';
                                display[4][41] = 'l';
                                display[4][42] = 'u';
                                display[4][43] = 'e';
                                display[4][44] = ' ';
                                display[4][45] = ' ';
                            }
                            else if (bc == 4) {
                                strcpy(set.back_color, "purpl");
                                display[4][40] = 'P';
                                display[4][41] = 'u';
                                display[4][42] = 'r';
                                display[4][43] = 'p';
                                display[4][44] = 'l';
                                display[4][45] = 'e';
                            }
                            else if (bc == 5) {
                                strcpy(set.back_color, "white");
                                display[4][40] = 'W';
                                display[4][41] = 'h';
                                display[4][42] = 'i';
                                display[4][43] = 't';
                                display[4][44] = 'e';
                                display[4][45] = ' ';
                            }
                            else if (bc == 6) {
                                strcpy(set.back_color, "black");
                                display[4][40] = 'B';
                                display[4][41] = 'l';
                                display[4][42] = 'a';
                                display[4][43] = 'c';
                                display[4][44] = 'k';
                                display[4][45] = ' ';
                            }
                            else if (bc == 7) {
                                strcpy(set.back_color, "red");
                                display[4][40] = 'R';
                                display[4][41] = 'e';
                                display[4][42] = 'd';
                                display[4][43] = ' ';
                                display[4][44] = ' ';
                                display[4][45] = ' ';
                            }
                        }
                        else if (setting_n == 4) {
                            int lc = setting_color(set.letter_color);
                            if (lc == 1) {
                                strcpy(set.letter_color, "yello");
                                display[5][40] = 'Y';
                                display[5][41] = 'e';
                                display[5][42] = 'l';
                                display[5][43] = 'l';
                                display[5][44] = 'o';
                                display[5][45] = 'w';
                            }
                            else if (lc == 2) {
                                strcpy(set.letter_color, "green");
                                display[5][40] = 'G';
                                display[5][41] = 'r';
                                display[5][42] = 'e';
                                display[5][43] = 'e';
                                display[5][44] = 'n';
                                display[5][45] = ' ';
                            }
                            else if (lc == 3) {
                                strcpy(set.letter_color, "blue");
                                display[5][40] = 'B';
                                display[5][41] = 'l';
                                display[5][42] = 'u';
                                display[5][43] = 'e';
                                display[5][44] = ' ';
                                display[5][45] = ' ';
                            }
                            else if (lc == 4) {
                                strcpy(set.letter_color, "purpl");
                                display[5][40] = 'P';
                                display[5][41] = 'u';
                                display[5][42] = 'r';
                                display[5][43] = 'p';
                                display[5][44] = 'l';
                                display[5][45] = 'e';
                            }
                            else if (lc == 5) {
                                strcpy(set.letter_color, "white");
                                display[5][40] = 'W';
                                display[5][41] = 'h';
                                display[5][42] = 'i';
                                display[5][43] = 't';
                                display[5][44] = 'e';
                                display[5][45] = ' ';
                            }
                            else if (lc == 6) {
                                strcpy(set.letter_color, "black");
                                display[5][40] = 'B';
                                display[5][41] = 'l';
                                display[5][42] = 'a';
                                display[5][43] = 'c';
                                display[5][44] = 'k';
                                display[5][45] = ' ';
                            }
                            else if (lc == 7) {
                                strcpy(set.letter_color, "red");
                                display[5][40] = 'R';
                                display[5][41] = 'e';
                                display[5][42] = 'd';
                                display[5][43] = ' ';
                                display[5][44] = ' ';
                                display[5][45] = ' ';
                            }
                        }
                        else if (setting_n == 5) {
                            int eq = strcmp(set.auto_screen, t);
                            if (eq == 0) {
                                strcpy(set.auto_screen, "False");
                                display[6][40] = 'F';
                                display[6][41] = 'a';
                                display[6][42] = 'l';
                                display[6][43] = 's';
                                display[6][44] = 'e';
                            }
                            else {
                                strcpy(set.auto_screen, "True");
                                display[6][40] = 'T';
                                display[6][41] = 'r';
                                display[6][42] = 'u';
                                display[6][43] = 'e';
                                display[6][44] = ' ';
                            }
                            break;
                        }
                }
                setting_s();
            }
        }
        else if (gch == 13) {
            if (display_type == 1) {
                if (start_check == 1) game_play();
                else if (start_check == 2) setting();
                else if (start_check == 3) quit_game();
            }
            else if (display_type == 3) {
                if (setting_n == 6) {
                    setting_save();
                    gotomain();
                }
            }
        }
    }
}

int game_play() {

}

int gotomain() {
    display_type = 1;
    start_check = 2;
    setting_n = 0;
    set_rows_main();
    start_check_s();
}

int setting() {
    display_type = 3;
    reset_rows();
    set_rows_setting();
    setting_r();
    char *t = "True";
    int eq = strcmp(set.sound_effect, t);
    if(eq == 0) {
        display[2][40] = 'T';
        display[2][41] = 'r';
        display[2][42] = 'u';
        display[2][43] = 'e';
    }
    else {
        display[2][40] = 'F';
        display[2][41] = 'a';
        display[2][42] = 'l';
        display[2][43] = 's';
        display[2][44] = 'e';
    }

    eq = strcmp(set.back_music, t);
    if(eq == 0) {
        display[3][40] = 'T';
        display[3][41] = 'r';
        display[3][42] = 'u';
        display[3][43] = 'e';
    }
    else {
        display[3][40] = 'F';
        display[3][41] = 'a';
        display[3][42] = 'l';
        display[3][43] = 's';
        display[3][44] = 'e';
    }

    eq = strcmp(set.auto_screen, t);
    if(eq == 0) {
        display[6][40] = 'T';
        display[6][41] = 'r';
        display[6][42] = 'u';
        display[6][43] = 'e';
    }
    else {
        display[6][40] = 'F';
        display[6][41] = 'a';
        display[6][42] = 'l';
        display[6][43] = 's';
        display[6][44] = 'e';
    }

    int bc = setting_color(set.back_color);
    int lc = setting_color(set.letter_color);

    if (bc == 1) {
        display[4][40] = 'R';
        display[4][41] = 'e';
        display[4][42] = 'd';
    }
    else if (bc == 2) {
        display[4][40] = 'Y';
        display[4][41] = 'e';
        display[4][42] = 'l';
        display[4][43] = 'l';
        display[4][44] = 'o';
        display[4][45] = 'w';
    }
    else if (bc == 3) {
        display[4][40] = 'G';
        display[4][41] = 'r';
        display[4][42] = 'e';
        display[4][43] = 'e';
        display[4][44] = 'n';
    }
    else if (bc == 4) {
        display[4][40] = 'B';
        display[4][41] = 'l';
        display[4][42] = 'u';
        display[4][43] = 'e';
    }
    else if (bc == 5) {
        display[4][40] = 'P';
        display[4][41] = 'u';
        display[4][42] = 'r';
        display[4][43] = 'p';
        display[4][44] = 'l';
        display[4][45] = 'e';
    }
    else if (bc == 6) {
        display[4][40] = 'W';
        display[4][41] = 'h';
        display[4][42] = 'i';
        display[4][43] = 't';
        display[4][44] = 'e';
    }
    else if (bc == 7) {
        display[4][40] = 'B';
        display[4][41] = 'l';
        display[4][42] = 'a';
        display[4][43] = 'c';
        display[4][44] = 'k';
    }

    if (lc == 1) {
        display[5][40] = 'R';
        display[5][41] = 'e';
        display[5][42] = 'd';
    }
    else if (lc == 2) {
        display[5][40] = 'Y';
        display[5][41] = 'e';
        display[5][42] = 'l';
        display[5][43] = 'l';
        display[5][44] = 'o';
        display[5][45] = 'w';
    }
    else if (lc == 3) {
        display[5][40] = 'G';
        display[5][41] = 'r';
        display[5][42] = 'e';
        display[5][43] = 'e';
        display[5][44] = 'n';
    }
    else if (lc == 4) {
        display[5][40] = 'B';
        display[5][41] = 'l';
        display[5][42] = 'u';
        display[5][43] = 'e';
    }
    else if (lc == 5) {
        display[5][40] = 'P';
        display[5][41] = 'u';
        display[5][42] = 'r';
        display[5][43] = 'p';
        display[5][44] = 'l';
        display[5][45] = 'e';
    }
    else if (lc == 6) {
        display[5][40] = 'W';
        display[5][41] = 'h';
        display[5][42] = 'i';
        display[5][43] = 't';
        display[5][44] = 'e';
    }
    else if (lc == 7) {
        display[5][40] = 'B';
        display[5][41] = 'l';
        display[5][42] = 'a';
        display[5][43] = 'c';
        display[5][44] = 'k';
    }
}

int setting_s() {
    if (setting_n == 1) {
        for (int i = 27; i < 43; i++) display[10][i] = ' ';
        for (int i = 27; i < 43; i++) display[12][i] = ' ';
        display[2][17] = '*';
        display[3][17] = ' ';
        display[4][17] = ' ';
        display[5][17] = ' ';
        display[6][17] = ' ';
    }
    else if (setting_n == 2) {
        for (int i = 27; i < 43; i++) display[10][i] = ' ';
        for (int i = 27; i < 43; i++) display[12][i] = ' ';
        display[2][17] = ' ';
        display[3][17] = '*';
        display[4][17] = ' ';
        display[5][17] = ' ';
        display[6][17] = ' ';
    }
    else if (setting_n == 3) {
        for (int i = 27; i < 43; i++) display[10][i] = ' ';
        for (int i = 27; i < 43; i++) display[12][i] = ' ';
        display[2][17] = ' ';
        display[3][17] = ' ';
        display[4][17] = '*';
        display[5][17] = ' ';
        display[6][17] = ' ';
    }
    else if (setting_n == 4) {
        for (int i = 27; i < 43; i++) display[10][i] = ' ';
        for (int i = 27; i < 43; i++) display[12][i] = ' ';
        display[2][17] = ' ';
        display[3][17] = ' ';
        display[4][17] = ' ';
        display[5][17] = '*';
        display[6][17] = ' ';
    }
    else if (setting_n == 5) {
        for (int i = 27; i < 43; i++) display[10][i] = ' ';
        for (int i = 27; i < 43; i++) display[12][i] = ' ';
        display[2][17] = ' ';
        display[3][17] = ' ';
        display[4][17] = ' ';
        display[5][17] = ' ';
        display[6][17] = '*';
    }
    else if (setting_n == 6) {
        for (int i = 27; i < 43; i++) display[10][i] = '*';
        for (int i = 27; i < 43; i++) display[12][i] = '*';
        display[2][17] = ' ';
        display[3][17] = ' ';
        display[4][17] = ' ';
        display[5][17] = ' ';
        display[6][17] = ' ';
    }
}

int setting_r() {
    options = fopen("setting.txt", "r");
    fscanf(options, "%s %s %s %s %s %s %s %s %s %s %s %s %s", &ch.s1, &ch.s2, &ch.s3, &ch.s4, &ch.s5, &ch.s6, &ch.s7, &ch.s8, &ch.s9, &ch.s10, &ch.s11);
    fclose(options);
    strcpy(set.sound_effect, ch.s3);
    strcpy(set.back_music, ch.s5);
    strcpy(set.back_color, ch.s7);
    strcpy(set.letter_color, ch.s9);
    strcpy(set.auto_screen, ch.s11);
}

int set_rows_setting() {
    display[0][31] = 'S';
    display[0][32] = 'E';
    display[0][33] = 'T';
    display[0][34] = 'T';
    display[0][35] = 'I';
    display[0][36] = 'N';
    display[0][37] = 'G';

    display[2][25] = 'S';
    display[2][26] = 'O';
    display[2][27] = 'U';
    display[2][28] = 'N';
    display[2][29] = 'D';
    display[2][31] = 'E';
    display[2][32] = 'F';
    display[2][33] = 'F';
    display[2][34] = 'E';
    display[2][35] = 'F';
    display[2][36] = 'T';
    display[2][38] = ':';
    //True | False

    display[3][21] = 'B';
    display[3][22] = 'A';
    display[3][23] = 'C';
    display[3][24] = 'K';
    display[3][25] = 'G';
    display[3][26] = 'R';
    display[3][27] = 'O';
    display[3][28] = 'U';
    display[3][29] = 'N';
    display[3][30] = 'D';
    display[3][32] = 'M';
    display[3][33] = 'U';
    display[3][34] = 'S';
    display[3][35] = 'I';
    display[3][36] = 'C';
    display[3][38] = ':';
    //True | False

    display[4][21] = 'B';
    display[4][22] = 'A';
    display[4][23] = 'C';
    display[4][24] = 'K';
    display[4][25] = 'G';
    display[4][26] = 'R';
    display[4][27] = 'O';
    display[4][28] = 'U';
    display[4][29] = 'N';
    display[4][30] = 'D';
    display[4][32] = 'C';
    display[4][33] = 'O';
    display[4][34] = 'L';
    display[4][35] = 'O';
    display[4][36] = 'R';
    display[4][38] = ':';
    //Color

    display[5][25] = 'L';
    display[5][26] = 'E';
    display[5][27] = 'T';
    display[5][28] = 'T';
    display[5][29] = 'E';
    display[5][30] = 'R';
    display[5][32] = 'C';
    display[5][33] = 'O';
    display[5][34] = 'L';
    display[5][35] = 'O';
    display[5][36] = 'R';
    display[5][38] = ':';
    //Color

    display[6][19] = 'A';
    display[6][20] = 'U';
    display[6][21] = 'T';
    display[6][22] = 'O';
    display[6][24] = 'R';
    display[6][25] = 'E';
    display[6][26] = 'S';
    display[6][27] = 'I';
    display[6][28] = 'Z';
    display[6][29] = 'E';
    display[6][31] = 'S';
    display[6][32] = 'C';
    display[6][33] = 'R';
    display[6][34] = 'E';
    display[6][35] = 'E';
    display[6][36] = 'N';
    display[6][38] = ':';
    //True | False

    for(int i = 27; i < 43; i++) display[9][i] = '-';
    
    display[10][26] = '|';
    display[10][43] = '|';

    display[11][26] = '|';
    display[11][28] = 'S';
    display[11][29] = 'a';
    display[11][30] = 'v';
    display[11][31] = 'e';
    display[11][33] = '&';
    display[11][35] = 'G';
    display[11][36] = 'o';
    display[11][38] = 'B';
    display[11][39] = 'a';
    display[11][40] = 'c';
    display[11][41] = 'k';
    display[11][43] = '|';

    display[12][26] = '|';
    display[12][43] = '|';

    for(int i = 27; i < 43; i++) display[13][i] = '-';
}

int setting_w() {
    options = fopen("setting.txt", "wt");
    fprintf(options, "%s\n\n%s %s\n\n%s %s\n\n%s %s\n\n%s %s\n\n%s %s", ch.s1, ch.s2, set.sound_effect, ch.s4, set.back_music, ch.s6, set.back_color, ch.s8, set.letter_color, ch.s10, set.auto_screen);
    fclose(options);
}

int change_setting() {
    int bc = setting_color(set.back_color);
    int c_t = 0;
    int c_b = 0;
    if (bc == 1) {
        c_b = 12;
    }
    else if (bc == 2) {
        c_b = 14;
    }
    else if (bc == 3) {
        c_b = 10;
    }
    else if (bc == 4) {
        c_b = 9;
    }
    else if (bc == 5) {
        c_b = 5;
    }
    else if (bc == 6) {
        c_b = 15;
    }
    else if (bc == 7) {
        c_b = 0;
    }

    int lc = setting_color(set.letter_color);
    if (lc == 1) {
        c_t = 12;
    }
    else if (lc == 2) {
        c_t = 14;
    }
    else if (lc == 3) {
        c_t = 10;
    }
    else if (lc == 4) {
        c_t = 9;
    }
    else if (lc == 5) {
        c_t = 5;
    }
    else if (lc == 6) {
        c_t = 15;
    }
    else if (lc == 7) {
        c_t = 0;
    }
    color(c_t, c_b);
}

int setting_save() {
    reset_rows();
    change_setting();
    setting_w();
    reset_setting_variables();
}

int quit_game() {
    exit(1);
}

// Samsung Go Tournament Form C Connect6Algo Header (g++-4.8.3)

// <--------------- 이 Code를 수정하면  작동하지 않을 수 있습니다 ------------------>

#pragma once
extern int width, height;
extern int terminateAI;
extern unsigned s_time;

extern FILE *fp;


extern int isFree(int x, int y);
extern int showBoard(int x, int y);
extern void init();
extern void restart();
extern void mymove(int x[], int y[], int cnt = 2);
extern void opmove(int x[], int y[], int cnt = 2);
extern void block(int, int);
extern int setLine(char *fmt, ...);
extern void domymove(int x[], int y[], int cnt = 2);
extern void writeLog(char *log);

void myturn(int cnt = 2);
char info[];

// 추가한 것
extern int enemyLog[2][2];
extern int myLog[2][2];

void setMyWeight(int cnt);
int searchMyTree(int x, int y, int incX, int incY, int level);
void setEnemyWeight(int cnt);
int searchEnemyTree(int x, int y, int incX, int incY, int level);

bool empty();
bool line_check(int bx, int by, int cx, int cy, int level);
void set_opposition(int x, int y);
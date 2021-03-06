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
#include <vector>

class Position {
private:
	int x;
	int y;
public:
	Position() {}
	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() { return this->x; }
	int getY() { return this->y; }

	Position &operator =(const Position &Other) {
		this->x = Other.x;
		this->y = Other.y;
	}
};

extern std::vector<Position> myLog;
extern std::vector<Position> enemyLog;


void setMyWeight();
void searchMyTree(int x, int y, int level);
void setEnemyWeight();
void searchEnemyTree(int x, int y, int level);

bool empty();
bool lineCheck(int bx, int by, int cx, int cy, int level);
void set_opposition(int x, int y);

// ver0809
void check();
void checkMyWin();
void checkEnemyWin();
void checkMyPromising(int curX, int curY, int level);
void checkEnemyPromising(int curX, int curY, int level);
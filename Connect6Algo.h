// Samsung Go Tournament Form C Connect6Algo Header (g++-4.8.3)

// <--------------- �� Code�� �����ϸ�  �۵����� ���� �� �ֽ��ϴ� ------------------>

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

// Add 
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
	~Position() {}
};

#include <vector>
extern std::vector<Position> myLog;
extern std::vector<Position> enemyLog;
// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI 코드 작성 방법]

1. char info[]의 배열 안에					"TeamName:자신의 팀명,Department:자신의 소속"					순서로 작성합니다.
( 주의 ) Teamname:과 Department:는 꼭 들어가야 합니다.
"자신의 팀명", "자신의 소속"을 수정해야 합니다.

2. 아래의 myturn() 함수 안에 자신만의 AI 코드를 작성합니다.

3. AI 파일을 테스트 하실 때는 "육목 알고리즘대회 툴"을 사용합니다.

4. 육목 알고리즘 대회 툴의 연습하기에서 바둑돌을 누른 후, 자신의 "팀명" 이 들어간 알고리즘을 추가하여 테스트 합니다.



[변수 및 함수]
myturn(int cnt) : 자신의 AI 코드를 작성하는 메인 함수 입니다.
int cnt (myturn()함수의 파라미터) : 돌을 몇 수 둬야하는지 정하는 변수, cnt가 1이면 육목 시작 시  한 번만  두는 상황(한 번), cnt가 2이면 그 이후 돌을 두는 상황(두 번)
int  x[0], y[0] : 자신이 둘 첫 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
int  x[1], y[1] : 자신이 둘 두 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
void domymove(int x[], int y[], cnt) : 둘 돌들의 좌표를 저장해서 출력


//int board[BOARD_SIZE][BOARD_SIZE]; 바둑판 현재상황 담고 있어 바로사용 가능함. 단, 원본데이터로 수정 절대금지
// 놓을수 없는 위치에 바둑돌을 놓으면 실격패 처리.

boolean ifFree(int x, int y) : 현재 [x,y]좌표에 바둑돌이 있는지 확인하는 함수 (없으면 true, 있으면 false)
int showBoard(int x, int y) : [x, y] 좌표에 무슨 돌이 존재하는지 보여주는 함수 (1 = 자신의 돌, 2 = 상대의 돌, 3 = 블럭킹)


<-------AI를 작성하실 때, 같은 이름의 함수 및 변수 사용을 권장하지 않습니다----->
*/

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"
#include <cmath>
#include <algorithm>


using namespace std;

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:1234567890,Department:AI부서[C]" };

float inclination;
int gx = -1, gy = -1;		// good
int lx, ly;					// last
int val[19][19];			// weight_val
int center_x, center_y;


void myturn(int cnt) {
	//int x[2], y[2];

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	int maxVal = 1;
	int x[2], y[2];
	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\YC\\Desktop\\c++\\육목\\fuck.txt","w");

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			val[i][j] = 0;
		}
	}

	srand((unsigned)time(NULL));

	if (cnt == 1) {
		do {
			x[0] = rand() % width;
			y[0] = rand() % height;
			if (terminateAI) return;
		} while (!isFree(x[0], y[0]));
	}
	else {
		if (enemyLog[1][0] == -1 && myLog[1][0] == -1)
		{
			setEnemyWeight(1);
		}
		else if (myLog[1][0] == -1)
		{
			setMyWeight(1);
			setEnemyWeight(cnt);
		}
		else
		{
			setEnemyWeight(cnt);
			setMyWeight(cnt);
		}
		
		for (int z = 0; z < 19; z++)
		{
			for (int q = 0; q < 19; q++)
			{
				fprintf(file_pointer, "%d ", val[z][q]);
			}
			fprintf(file_pointer, "\n");
		}

		for (int i = 0; i < cnt; i++)
		{
			maxVal = 1;
			for (int j = 0; j < 19; j++)
			{
				for (int k = 0; k < 19; k++)
				{
					if (maxVal < val[j][k])
					{
						maxVal = val[j][k];
						y[i] = j;
						x[i] = k;
					}
				}

			}

			val[y[i]][x[i]] = -1;

			if (terminateAI) return;
		}
	}
	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);
}
 

// 내 돌 검사.

void setMyWeight(int cnt) {
	int weight = 0;

	for (int i = 0; i < cnt; i++) {
		int x = myLog[i][0];
		int y = myLog[i][1];
		center_x = x;
		center_y = y;

		val[y][x] = -1;

		for (int j = y -1; j <= y + 1; j++) {
			for (int k = x -1; k <= x + 1; k++) {
				int pos = showBoard(k, j);
				if (j == y && k == x) continue;
				if (pos == 0) {						// 0일때
					val[j][k] += 50;				// 가중치 50
				}
				else if (pos == 1 || pos == 3) {	// 내 돌이 있을 때
					val[j][k] = -1;					// 가중치 -1
					searchMyTree(x, y, k, j, 2);	// level = 2로 searchTree로 넘김
				}
				else {								// 적 돌이 있을 때
					val[j][k] = -10;				// 가중치 -10
					set_opposition(k, j);			// 그 반대돌은 가능하면 안 놓도록
				}
			}
		}
	}
}

void searchMyTree(int bx, int by, int x, int y, int level) {
	for (int j = y - 1; j <= y + 1; j++) {							// 3x3 검사
		for (int i = x - 1; i <= x + 1; i++) {
			if ((i == x && j == y) || (i == bx && j == by)) continue;
			
			int pos = showBoard(i, j);								
			bool line = line_check(x, y, i, j, level+1);
			
			if (pos == 0) {
				val[j][i] += 50;
				if (line == true) val[j][i] += 200 * level;
			}
			else if (pos == 1 || pos == 3) {
				val[j][i] = -1;
				if (line == true) searchMyTree(x, y, i, j, level+1);
				else searchMyTree(x, y, i, j, 1);	
			}
			else {
				if (line == true) {
					val[j][i] = -20;
					set_opposition(i, j);
				}
				else val[j][i] = -10;
			}
		}
	}
}

void set_opposition(int x, int y) {
	for (int i = center_x - 1; i <= center_x + 1; i++) {
		for (int j = center_y - 1; j <= center_y + 1; j++) {
			if (line_check(center_x, center_y, i, j, 3) && showBoard(i, j) == 0) {
				val[j][i] = -50;
			}
		}
	}
}

void searchEnemyTree(int bx, int by, int x, int y, int level) {
	for (int j = y - 1; j <= y + 1; j++) {
		for (int i = x - 1; i <= x + 1; i++) {
			if ((i == x && j == y) || (i == bx && j == by)) continue;

			int pos = showBoard(i, j);
			bool line = line_check(x, y, i, j, level + 1);

			if (pos == 0) {
				val[j][i] += 50;
				if (line == true) val[j][i] += 200 * level;
			}
			else if (pos == 2 || pos == 3) {
				val[j][i] = -1;
				if (line == true) searchMyTree(x, y, i, j, level + 1);
				else searchMyTree(x, y, i, j, 1);
			}
			else {
				if (line == true) {
					val[j][i] = -20;
					set_opposition(i, j);
				}
				else val[j][i] = -10;
			}
		}
	}
}

// 적 돌 검사

void setEnemyWeight(int cnt) {
	int weight = 0;

	for (int i = 0; i < cnt; i++) {
		int x = enemyLog[i][0];
		int y = enemyLog[i][1];

		val[y][x] = -10;

		for (int j = y - 1; j <= y + 1; j++) {
			for (int k = x - 1; k <= x + 1; k++) {
				int pos = showBoard(k, j);
				if (j == y && k == x) continue;
				if (pos == 0) {			// 0일때
					val[j][k] += 20;				// 가중치 20
				}
				else if (pos == 2 || pos == 3) {
					val[j][k] = -10;
					searchMyTree(x, y, k, j, 2);
				}
				else {
					val[j][k] = -1;
				}
			}
		}
	}
}

// 선형성을 검사하는 함수
bool line_check(int bx, int by, int cx, int cy, int level) {
	if (level <= 2) {
		inclination = (cx - bx) / (cy - by);
		
		if (inclination == 0 || inclination == 1.0 || inclination == -1.0) return true;
		else false;
	}
	else if (level > 2) {
		double temp = (cx - bx) / (cy - by);
		if (inclination == temp) return true;
		else return false;
	}
	else {
		return true;
	}
	return false;
}

// 처음 공백 init 상태를 확인
bool empty() {
	int count = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (showBoard(i, j) != 0) return false;
		}
	}

	return true;
}

// 2차원 배열 가중치 최대값 찾고 좌표 대입
void m_find() {
	int max = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (val[i][j] > max) {
				max = val[i][j];
				gx = i;
				gy = j;
			}
		}
	}
}


/*
void next() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			val[i][j] = 0;
		}
	}

	if (empty()) {
		gx = 9, gy = 9;
		return;
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (showBoard(x, y) == 1) {			// 내 돌을 먼저 검사.
				around(x, y, 1);				// count 1부터 시작하여 주변 돌을 검사.
			}
		}
	}

	m_find();
	return;
}

void around(int x, int y, int count) {
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= j + 1; j++) {
			if ((i == x && j == y ) || (i == lx && j == ly)) continue;
			if (count < 6 && line_check(x, y, i, j, count++)) {
				if (showBoard(i, j) == 0) {
					val[i][j] += 1;
				}
				else if (showBoard(i, j) == 1) {
					lx = x; ly = y;
					around(i, j, count);
				}
				else {
					val[i][j] -= 1;
				}
			}
		}
	}
}
*/

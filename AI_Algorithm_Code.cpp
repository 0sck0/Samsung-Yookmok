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

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:1234567890,Department:AI부서[C]" };

float inclination;			// 바둑돌 선형성 검사 변수
int val[19][19] = { 0, };			// 전체 가중치를 나타내는 배열
int center_x, center_y;		// 중심이 되는 x, y 좌표 값

void myturn(int cnt) {

	int x[2], y[2];
	int maxVal = 1;			// 가중치 중 가장 큰 값

	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\최대준\\Desktop\\R\\log.txt", "a");

	// 입출력으로 log 확인


	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	srand((unsigned)time(NULL));

	// 가중치 0으로 초기화
	/*
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++){
			val[i][j] = 0;
		}
	}
	*/
	if (cnt == 1) {			// 첫 수 둘 경우
		x[0] = 9;			// 9, 9 를 기본
		y[0] = 9;

		while (!isFree(x[0], y[0])) {		// 돌이 다른 것이 있을 경우(block)
			int sign = rand() % 2;			// 부호를 음수로 할 지, 양수로 할 지

			if (sign) {						// 양수일 경우 랜덤하게 좌표를 더함
				x[0] += rand() % 2;
				y[0] += rand() % 2;
			}
			else {							// 음수일 경우 랜덤하게 좌표를 뺌
				x[0] -= rand() % 2;
				y[0] -= rand() % 2;
			}
		}
	}
	else {
		if (enemyLog[1][0] == -1 && myLog[1][0] == -1) {
			setEnemyWeight(1);
		}
		else if (myLog[1][0] == -1) {
			setMyWeight(1);
			setEnemyWeight(cnt);
		}
		else {
			setEnemyWeight(cnt);
			setMyWeight(cnt);
		}
	}

	// 로그 출력
	fprintf(file_pointer, "\n");
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fprintf(file_pointer, "%.4d ", val[i][j]);
		}
		fprintf(file_pointer, "\n");
	}

	for (int k = 0; k < cnt; k++) {
		maxVal = 1;
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				if (maxVal < val[j][i]) {
					maxVal = val[j][i];

					x[k] = i;
					y[k] = j;
				}
			}
		}

		val[y[k]][x[k]] = -1;

		if (terminateAI) return;

	}
	fclose(file_pointer);

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);

}

// 내 돌 검사
void setMyWeight(int cnt) {
	int weight = 0;

	for (int i = 0; i < cnt; i++) {
		int x = myLog[i][0];
		int y = myLog[i][1];
		center_x = x;
		center_y = y;

		val[y][x] = -1;

		searchMyTree(x, y, 0, 0, 1);	// level 1부터 시작
	}
}

int searchMyTree(int x, int y, int incX, int incY, int level) {

	for (int j = -1; j <=  1; j++) {
		for (int i = -1; i <= 1; i++) {
			int pos = showBoard(x + i, y + j);
			int mipos = showBoard(x - i, y - j);
			if ((i == 0 && j == 0) || (i == incX * -1 && j == incY * -1)) continue;

			if (pos == 0) {
				val[y + j][x + i] += 10;
				if (incX == i && incY == j)
				{
					val[y + j][x + i] = 200 * level;
					if (level >= 2 && showBoard(x + (-i * (level)), y + (-j * (level ))) == 0)
						val[y + (-j * level)][x + (-i * level)] = 200 * level;
				}

			}
			else if (pos == 1 || pos == 3) {
				val[y + j][x + i] = -1;
				if (level == 1)
					return searchEnemyTree(x + i, y + j, i, j, level + 1);
				else if (incX == i && incY == j) return searchMyTree(x + i, y + j, i, j, level + 1);
				else if (mipos == 1 || mipos == 3)
				{
					int end = searchMyTree(x + i, y + j, i, j, 2);
					int end1 = searchMyTree(x - i, y - j, -i, -j, 2);
					if (showBoard(x + (i * end), y + (j * end)) == 0)
						val[y + (j * end)][x + (i * end)] = (end + end1 - 1) * 200;
					if (showBoard(x + (-i * end), y + (-j * end)) == 0)
						val[y + (-j * end1)][x + (-i * end1)] = (end + end1 - 1) * 200;
				}
			}
			else {
				if (incX == i && incY == j) {
					val[y + j][x + i] = -2;
					if (level >= 2 && showBoard(x + (-i * (level)), y + (-j * (level))) == 0)
						val[y + (-j * level)][x + (-i * level)] = 200 * level;
				}
				else val[y + j][x + i] = -2;
			}
		}
	}
	return level;
}


// 적 돌 검사
void setEnemyWeight(int cnt) {
	int weight = 0;

	for (int i = 0; i < cnt; i++) {
		int x = enemyLog[i][0];
		int y = enemyLog[i][1];

		val[y][x] = -1;

		searchEnemyTree(x, y, 0, 0, 1);	// level 1부터 시작
	}
}

int searchEnemyTree(int x, int y, int incX, int incY, int level) {

	for (int j = -1; j <= 1; j++) {
		for (int i = -1; i <= 1; i++) {
			int pos = showBoard(x + i, y + j);
			int mipos = showBoard(x - i, y - j);
			if ((i == 0 && j == 0) || (i == incX * -1 && j == incY * -1)) continue;

			if (pos == 0) {
				val[y + j][x + i] += 10;
				if (incX == i && incY == j)
				{
					val[y + j][x + i] = 200 * level;
					if (level >= 2 && showBoard(x + (-i * (level)), y + (-j * (level))) == 0)
						val[y + (-j * level)][x + (-i * level)] = 200 * level;
				}
			}
			else if (pos == 2 || pos == 3) {
				val[y + j][x + i] = -2;
				if (level == 1)
					return searchEnemyTree(x + i, y + j, i, j, level + 1);
				else if (incX == i && incY == j) return searchEnemyTree(x + i, y + j, i, j, level + 1);
				else if (mipos == 2 || mipos == 3)
				{
					int end = searchEnemyTree(x + i, y + j, i, j, 2);
					int end1 = searchEnemyTree(x - i, y - j, -i, -j, 2);
					if (showBoard(x + (i * end), y + (j * end)) == 0)
						val[y + (j * end)][x + (i * end)] = (end + end1-1) * 200;
					if (showBoard(x + (-i * end), y + (-j * end)) == 0)
						val[y + (-j * end1)][x + (-i * end1)] = (end + end1-1) * 200;
				}
			}
			else {
				if (incX == i && incY == j) {
					val[y + j][x + i] = -1;
					if (level >= 2 && showBoard(x + (-i * (level)), y + (-j * (level))) == 0)
						val[y + (-j * level)][x + (-i * level)] = 200 * level;
				}
				else val[y + j][x + i] = -1;
			}
		}
	}
	return level;
}

// 부가적인 함수들

// 보드가 빈 상태인지 확인
bool empty() {
	int count = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (showBoard(i, j) != 0) return false;
		}
	}

	return true;
}

// 선형성 검사 함수
bool line_check(int bx, int by, int cx, int cy, int level) {

	// level이 2 이하면 돌을 2개째 검사하는 것을 의미
	if (level <= 2) {
		if ((cy - by) == 0)
			inclination = 10000.0;	// 분모가 0 인 경우
		else
			inclination = (cx - bx) / (cy - by);

		if (inclination == 0.0 || inclination == 1.0 || inclination == -1.0 || inclination == 10000.0) return true;
		else false;
	}
	else if (level > 2) {
		double temp;
		if ((cy - by) == 0) {
			temp == 10000.0;
		}
		else {
			temp = (cx - bx) / (cy - by);
		}

		if (inclination == temp) return true;
		else return false;
	}
	return false;
}

// 적돌의 반대편 위치 가중치 설정
void set_opposition(int x, int y) {
	for (int j = center_y - 1; j <= center_y + 1; j++) {
		for (int i = center_x - 1; i <= center_x + 1; i++) {
			if (line_check(center_x, center_y, i, j, 3) && showBoard(i, j) == 0) {
				val[j][i] -= 50;
			}
		}
	}
}
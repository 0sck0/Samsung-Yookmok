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
#include <vector>

using namespace std;

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:1234567890,Department:AI부서[C]" };

float inclination;			// 바둑돌 선형성 검사 변수
int val[19][19];			// 전체 가중치를 나타내는 배열
int center_x, center_y;		// 중심이 되는 x, y 좌표 값
int myTracker[19][19];
int opTracker[19][19];

void myturn(int cnt) {

	int x[2], y[2];
	int maxVal = 1;			// 가중치 중 가장 큰 값

							// 입출력으로 log 확인
	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\YC\\Desktop\\c++\\육목\\삼성전자DS부문육목SW알고리즘대회\\SamsungGo_AI_Code_C_C++\\log.txt", "a");

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	srand((unsigned)time(NULL));

	// 가중치 0으로 초기화
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			val[i][j] = 0;
		}
	}

	if (empty()) {			// 첫 수 둘 경우
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
		setMyWeight();
		setEnemyWeight();
	}

	// 로그 출력
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fprintf(file_pointer, "%d ", val[i][j]);
		}
		fprintf(file_pointer, "\n");
	}
	fprintf(file_pointer, "\n\n");

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

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);

}

// 내 돌 검사
void setMyWeight() {
	for(Position &p : myLog) {
		int x = p.getX();
		int y = p.getY();
		center_x = x;
		center_y = y;

		val[y][x] = -1;

		// 검사했던 곳을 다시 검사하지 않도록 myTracker 사용
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				myTracker[i][j] = 0;				// 초기화
			}
		}

		searchMyTree(x, y, 1);						// level 1부터 시작
	}
}

void searchMyTree(int x, int y, int level) {
	// 3x3 검사
	for (int j = y - 1; j <= y + 1; j++) {
		for (int i = x - 1; i <= x + 1; i++) {

			int pos = showBoard(i, j);
			bool line = line_check(x, y, i, j, level + 1);

			if (i == x && j == y) continue;				// 전에 뒀던 x, y 좌표 pass
			else if (myTracker[i][j] == 1) continue;	// tracker를 이용해서 전에 검사했던 부분을 pass
			else myTracker[i][j] = 1;					// 검사하지 않으면 지금 검사했으므로 이제 1을 대입

			if (pos == 0) {
				val[j][i] += 50;
				if (line == true) val[j][i] += 200 * level;
			}
			else if (pos == 1 || pos == 3) {
				val[j][i] = -1;
				if (line == true) searchMyTree(i, j, level + 1);
				else searchMyTree(i, j, 1);
			}
			else {
				if (line == true) {
					val[j][i] -= 20;
					set_opposition(i, j);
				}
				else val[j][i] -= 10;
			}
		}
	}
}


// 적 돌 검사
void setEnemyWeight() {
	for (Position &p : enemyLog) {
		int x = p.getX();
		int y = p.getY();

		val[y][x] = -1;

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				opTracker[i][j] = 0;
			}
		}

		searchEnemyTree(x, y, 1);	// level 1부터 시작
	}
}

void searchEnemyTree(int x, int y, int level) {

	for (int j = y - 1; j <= y + 1; j++) {
		for (int i = x - 1; i <= x + 1; i++) {
			int pos = showBoard(i, j);
			bool line = line_check(x, y, i, j, level + 1);

			if (i == x && j == y) continue;
			else if (opTracker[i][j] == 1) continue;
			else opTracker[i][j] = 1;

			if (pos == 0) {
				val[j][i] += 50;
				if (line == true) val[j][i] += 200 * level;
			}
			else if (pos == 2 || pos == 3) {
				val[j][i] = -1;
				if (line == true) searchEnemyTree(i, j, level + 1);
				else searchEnemyTree(i, j, 1);
			}
			else {
				if (line == true) {
					val[j][i] -= 20;
					set_opposition(i, j);
				}
				else val[j][i] -= 10;
			}
		}
	}
}

// 부가적인 함수들

// 보드가 빈 상태인지 확인
bool empty() {
	int count = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (showBoard(i, j) == 1 || showBoard(i, j) == 2) return false;
		}
	}

	return true;
}

// 선형성 검사 함수
bool line_check(int bx, int by, int cx, int cy, int level) {
	bool check = false;

	// level이 2 이하면 돌을 2개째 검사하는 것을 의미
	if (level <= 2) {
		if ((cx - bx) == 0)
			inclination = 10000.0;	// 분모가 0 인 경우
		else
			inclination = (cy - by) / (cx - bx);

		if (inclination == 0.0 || inclination == 1.0 || inclination == -1.0 || inclination == 10000.0) check = true;
	}
	else if (level > 2) {
		double temp;
		if ((cx - bx) == 0) 
			temp = 10000.0;
		else 
			temp = (cy - by) / (cx - bx);

		if (inclination == temp) check = true;
	}

	return check;
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
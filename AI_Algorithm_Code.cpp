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
int gx, gy;
int val[19][19];

void myturn(int cnt) {

	//int x[2], y[2];

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	int x[2], y[2];

	srand((unsigned)time(NULL));

	for (int i = 0; i < cnt; i++) {
		do {
			next();
			x[i] = gx;
			y[i] = gy;
			if (terminateAI) return;
		} while (!isFree(x[i], y[i]));

		if (x[1] == x[0] && y[1] == y[0]) i--;
	}

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);
}

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
			else if (showBoard(x, y) == 2) {	// 적 돌을 검사.
				around(x, y, 0);
			}
		}
	}

	m_find();
	return;
}

void around(int x, int y, int count) {
	cout << "횟수: " << count << endl;
	for (int i = x - 1; i <= x + 1, i != x; i++) {
		for (int j = y - 1; j <= j + 1, j != y; j++) {
			if (count <= 6 && line_check(x, y, i, j, count++)) {
				if (showBoard(i, j) == 0) {
					val[i][j] += 1;
				}
				else if (showBoard(i, j) == 1) {
					around(i, j, count);
				}
				else {
					val[i][j] -= 1;
				}
			}
		}
	}
}

// 선형성을 검사하는 함수
bool line_check(int bx, int by, int cx, int cy, int count) {
	if (count == 2) {
		inclination = (cx - bx) / (cy - by);
		
		if (inclination == 0 || inclination == 1.0 || inclination == -1.0) return true;
		else false;
	}
	else if (count > 2) {
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

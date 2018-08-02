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

boolean isFree(int x, int y) : 현재 [x,y]좌표에 바둑돌이 있는지 확인하는 함수 (없으면 true, 있으면 false)
int showBoard(int x, int y) : [x, y] 좌표에 무슨 돌이 존재하는지 보여주는 함수 (1 = 자신의 돌, 2 = 상대의 돌, 3 = 블럭킹)


<-------AI를 작성하실 때, 같은 이름의 함수 및 변수 사용을 권장하지 않습니다----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:모자란 녀석들,Department:KOREATECH" };

int lastBoard[20][20];

void myturn(int cnt) {

	int x[2], y[2];

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	srand((unsigned)time(NULL));

	int opx[2], opy[2];
	getLastOpMove(opx, opy);

	/*
	for (int i = 0; i < cnt; i++) {
		do {
			x[i] = rand() % width;
			y[i] = rand() % height;
			if (terminateAI) return;
		} while (!isFree(x[i], y[i]));

		if (x[1] == x[0] && y[1] == y[0]) i--;
	}
	*/
	if (cnt == 1) {
		x[0] = width / 2;
		y[0] = height / 2;
	}
	else {
		/*
		if (opx[0] == 0)
			x[0] = opx[0] + 1;
		else if (opx[0] == width - 1)
			x[0] = opx[0] - 1;
		else {
			if (opx[0] < width - opx[0])
				x[0] = opx[0] + 1;
			else if (opx[0] > width - opx[0])
				x[0] = opx[0] - 1;
			else
				x[0] = opx[0] + (-1) * (rand() % 2);
		}

		if (opy[0] == 0)
			y[0] = opy[0] + 1;
		else if (opy[0] == height - 1)
			y[0] = opy[0] - 1;
		else {
			y[0] = opy[0] - 1 + (rand() % 3);
		}
		*/
		if (check5x5(opx[0], opy[0])) {
			while (true) {
				x[0] = opx[0] - 1 + (rand() % 3);
				y[0] = opy[0] - 1 + (rand() % 3);
				if (isFree(x[0], y[0])) break;
			}
			while (true) {
				x[1] = x[0] + (-1) * (rand() % 2);
				y[1] = y[0] + (-1) * (rand() % 2);
				if (isFree(x[1], y[1])) break;
			}
		}

	}

	setLastOpMove();

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);
}

// 현재 바둑판 상태 저장
void setLastOpMove() {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			lastBoard[i][j] = showBoard(i, j);
}

// 마지막 바둑판 상태 불러오기
void getLastOpMove(int* x, int* y) {
	for (int n = 0; n < 2; n++) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (lastBoard[i][j] != showBoard(i, j)) {
					*(x+n) = i;
					*(y+n) = j;
				}
			}
		}
	}
}

// 주변 5x5 체크
bool check5x5(int x, int y) {
	for (int i = x - 2; i <= x + 2; i++)
		for (int j = y - 2; j <= y + 2; j++)
			if (!isFree(i, j)) return false;
	return true;
}
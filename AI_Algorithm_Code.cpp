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

#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:모자란 녀석들,Department:KOREATECH" };

// 내가 마지막으로 착수한 돌의 위치 (-1로 초기화)
int myx[2] = { -1, -1 }, myy[2] = { -1, -1 };

// 상대방이 마지막으로 착수한 돌의 위치 (-1로 초기화)
int opx[2] = { -1, -1 }, opy[2] = { -1, -1 };

// (가중치, (x좌표, y좌표))를 나타내는 자료형 valued_point 정의
// first: 가중치, second.first: x 좌표, second.second: y 좌표
typedef pair<int, pair<int, int>> valued_point;

// 최적의 수의 가중치와 좌표(순서쌍)를 저장하는 우선순위 큐
priority_queue<valued_point> myQueue;

void checkAround(int px, int py);
int setPriority(string s);
void debugPrint();		// 우선순위 큐 디버그용

void myturn(int cnt) {

	int x[2], y[2];

	srand((unsigned)time(NULL));

	if (cnt == 1) {		// 첫 수일 경우 정가운데 3x3 중 랜덤으로 착수
		while (true) {
			x[0] = 8 + (rand() % 3);
			y[0] = 8 + (rand() % 3);
			if (isFree(x[0], y[0])) break;
		}
	}
	else {				// 첫 수를 제외한 모든 경우
		if (opx[1] == -1 && opy[1] == -1) {		// 다음 착수자의 첫 수일 경우
			while (true) {
				x[0] = opx[0] - 1 + (rand() % 3);
				y[0] = opy[0] - 1 + (rand() % 3);
				if (isFree(x[0], y[0])) break;
			}
			while (true) {
				switch (rand() % 4) {
				case 0:
					x[1] = x[0] - 1;
					y[1] = y[0];
					break;
				case 1:
					x[1] = x[0];
					y[1] = y[0] - 1;
					break;
				case 2:
					x[1] = x[0] + 1;
					y[1] = y[0];
					break;
				case 3:
					x[1] = x[0];
					y[1] = y[0] + 1;
					break;
				}

				if (((opx[0] == x[0]) && (x[0] == x[1])) || ((opy[0] == y[0]) && (y[0] == y[1]))) continue;
				if (isFree(x[1], y[1])) break;
			}
		}
		else {		// 그 외의 모든 경우
			checkAround(myx[0], myy[0]);
			checkAround(myx[1], myy[1]);
			checkAround(opx[0], opy[0]);
			checkAround(opx[1], opy[1]);

			debugPrint();		// 우선순위 큐 디버그용

			valued_point candidate;
			for (int i = 0; i < cnt; i++) {
				candidate = myQueue.top();
				myQueue.pop();
				x[i] = candidate.second.first;
				y[i] = candidate.second.second;

				if (!isFree(x[i], y[i]) || ((x[0] == x[1]) && (y[0] == y[1]))) i--;
				if (terminateAI) return;
			}

			valued_point vp;

		}
	}

	// 디버그용
	char dd[200] = { " " };
	sprintf_s(dd, "--- opx[0]: %d, opy[0]: %d, opx[1]: %d, opy[1]: %d ---\n", opx[0], opy[0], opx[1], opy[1]);
	writeLog(dd);

	//while (!myQueue.empty())
	//	myQueue.pop();

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);
}

// 특정 돌의 8 방향을 문자열화하여 각 라인을 검사, 돌을 놓을 좌표의 우선순위를 선정하는 함수
void checkAround(int px, int py) {
	string str = "";
	valued_point pos;		// 검사할 돌의 가중치(value)와 좌표 순서쌍 (x, y)
	unordered_map<string, int> tokens;
	vector<valued_point> tempQueue;		// 각 좌표와 가중치를 임시 저장하는 큐

	int firstIndex = 0, lastIndex = 0;
	int x_begin = -1, y_begin = -1;

	if (px == -1 && py == -1) return;

	// 상/하(0) -> 좌상/우하(1) -> 좌/우(2) -> 좌하/우상(3) 순으로 검사
	for (int incl = 0; incl < 4; incl++) {
		switch (incl) {
		case 0:		// 상 -> 하
			x_begin = px;
			y_begin = 0;

			for (int i = 0; i < height; i++)
				str.append(to_string(showBoard(px, i)));
			break;
		case 1:		// 좌상 -> 우하
			if (px > py) {
				x_begin = px - py;
				y_begin = 0;
			}
			else {
				x_begin = 0;
				y_begin = py - px;
			}

			for (int i = 0; i < height - abs(px - py); i++)
				if (px > py)	// 대각선 위
					str.append(to_string(showBoard((px - py) + i, i)));
				else			// 대각선 아래
					str.append(to_string(showBoard(i, (py - px) + i)));
			break;
		case 2:		// 좌 -> 우
			x_begin = 0;
			y_begin = py;

			for (int i = 0; i < width; i++)
				str.append(to_string(showBoard(i, py)));
			break;
		case 3:		// 좌하 -> 우상
			if (px + py < height) {		// 대각선 위
				x_begin = 0;
				y_begin = px + py;

				for (int i = 0; i < (px + py + 1); i++)
					str.append(to_string(showBoard(i, (px + py) - i)));
			}
			else {						// 대각선 아래
				x_begin = (px + py) - height + 1;
				y_begin = height - 1;
				for (int i = 0; i < (height * 2 - (px + py + 1)); i++)
					str.append(to_string(showBoard((px + py) - height + 1 + i, height - 1 - i)));
			}
			break;
		}

		// 디버그용
		fp = fopen("myLog.txt", "a");
		if (fp != NULL) {
			string tmp = to_string(incl) + string(" : ") + str;
			fprintf(fp, tmp.c_str());
			fprintf(fp, "\n");
		}
		fclose(fp);

		// 문자열 토큰화
		while (true) {
			firstIndex = str.find("0", lastIndex);
			lastIndex = str.find("0", firstIndex + 1);

			if (firstIndex == -1 && lastIndex == -1) break;
			if (lastIndex == -1 || lastIndex >= str.size()) lastIndex = str.size() - 1;
			if (lastIndex - firstIndex > 1 || (lastIndex == str.size() - 1 && firstIndex != str.size() - 1)) {
				string temp = str.substr(firstIndex, lastIndex - firstIndex + 1);
				//tokens.push_back(temp);
				tokens.emplace(make_pair(temp, firstIndex));
			}

			if (lastIndex == str.size() - 1) break;
		}
		firstIndex = 0, lastIndex = 0;

		for (auto s : tokens) {
			int value = setPriority(s.first);
			int qx[2] = { -1, -1 }, qy[2] = { -1, -1 };
			int startNum = (s.first.at(0) == '0') ? 0 : 1;
			int endNum = (s.first.at(s.first.size() - 1) == '0') ? 2 : 1;

			for (int i = startNum; i < endNum; i++) {
				fp = fopen("myLog.txt", "a");
				if (fp != NULL) {
					string ss = string("<") + s.first + string(", ") + to_string(s.second) + string("> ");
					fprintf(fp, ss.c_str());
				}
				fclose(fp);

				switch (incl) {
				case 0:		// 상 -> 하
					qx[i] = x_begin;
					if (i == 0) qy[i] = s.second;
					else qy[i] = s.second + s.first.size() - 1;
					break;
				case 1:		// 좌상 -> 우하
					if (i == 0) {
						qx[i] = x_begin + s.second;
						qy[i] = y_begin + s.second;
					}
					else {
						qx[i] = x_begin + s.second + s.first.size() - 1;
						qy[i] = y_begin + s.second + s.first.size() - 1;
					}
					break;
				case 2:		// 좌 -> 우
					if (i == 0) qx[i] = s.second;
					else qx[i] = s.second + s.first.size() - 1;
					qy[i] = y_begin;
					break;
				case 3:		// 좌하 -> 우상
					if (i == 0) {
						qx[i] = x_begin + s.second;
						qy[i] = y_begin - s.second;
					}
					else {
						qx[i] = x_begin + s.second + s.first.size() - 1;
						qy[i] = y_begin - (s.second + s.first.size() - 1);
					}
					break;
				}

				pos = make_pair(value, make_pair(qx[i], qy[i]));
				tempQueue.push_back(pos);

				fp = fopen("myLog.txt", "a");
				if (fp != NULL) {
					string ss = s.first + string(":") + to_string(pos.first) + string("_(") + to_string(pos.second.first) + string(",") + to_string(pos.second.second) + string(")  ");
					fprintf(fp, ss.c_str());
				}
				fclose(fp);

			}
		}
		writeLog("\n");
		str.clear();			// 문자열 초기화
		tokens.clear();			// 토큰 임시 저장 큐 초기화
	}
	
	while (!myQueue.empty()) {
		tempQueue.push_back(myQueue.top());
		myQueue.pop();
	}

	// 가중치 가산이 끝난 임시 저장 큐의 모든 원소를 정리(압축) 후 우선순위 큐로 이동
	valued_point tempPoint;
	vector<int> ban;
	int newValue, nx, ny;
	for (int i = 0; i < tempQueue.size(); i++) {
		tempPoint = tempQueue.at(i);
		newValue = tempPoint.first;
		bool isDuplicated = false, isBanned = false;

		for (auto a : ban) {
			if (i == a) {
				isBanned = true;
				break;
			}
		}
		if (isBanned) continue;

		for (int j = i + 1; j < tempQueue.size(); j++) {
			valued_point s = tempQueue.at(j);
			if (s != tempQueue.at(i)) {
				if (tempPoint.second.first == s.second.first && tempPoint.second.second == s.second.second) {
					for (auto a : ban) {
						if (j == a) {
							isBanned = true;
							break;
						}
					}
					
					if (!isBanned) {
						isDuplicated = true;
						newValue += s.first;
						nx = tempPoint.second.first;
						ny = tempPoint.second.second;

						ban.push_back(j);
					}
				}
			}
		}
		if (isDuplicated)
			myQueue.push(make_pair(newValue, make_pair(nx, ny)));
		else
			myQueue.push(tempPoint);
	}
}

// 문자열 토큰의 검사하여 가중치를 부여하는 함수
int setPriority(string s) {
	int value, tempValue;

	// 가중치 부여
	if (s == "010")				value = 20;
	else if (s == "0110")		value = 100;
	else if (s == "01110")		value = 500;
	else if (s == "011110")		value = 15000;
	else if (s == "0111110")	value = 1000000;
	else if (s == "020")		value = 10;
	else if (s == "0220")		value = 50;
	else if (s == "02220")		value = 200;
	else if (s == "022220")		value = 1000;
	else if (s == "0222220")	value = 6500;
	else {
		if (s.at(1) == '1') {
			value = 5;
			for (int i = 2; i <= 6; i++) {
				if (s.at(i) == '1' || s.at(i) == '3')
					value *= 5;
				else
					break;
			}
		}
		else if (s.at(1) == '2') {
			value = 2;
			for (int i = 2; i <= 6; i++) {
				if (s.at(i) == '2' || s.at(i) == '3')
					value *= 5;
				else
					break;
			}
		}
		else if (s.at(1) == '3') {
			if (s.at(2) == '1') {
				value = 5;
				for (int i = 3; i <= 6; i++) {
					if (s.at(i) == '1' || s.at(i) == '3')
						value *= 5;
					else
						break;
				}
			}
			else if (s.at(2) == '2') {
				value = 2;
				for (int i = 3; i <= 6; i++) {
					if (s.at(i) == '2' || s.at(i) == '3')
						value *= 5;
					else
						break;
				}
			}
			else
				value = 0;
		}
		else
			value = 0;

		if (s.at(s.size() - 2) == '1') {
			tempValue = 5;
			for (int i = s.size() - 3; i >= s.size() - 7; i--) {
				if (s.at(i) == '1' || s.at(i) == '3')
					tempValue *= 5;
				else
					break;
			}
		}
		else if (s.at(s.size() - 2) == '2') {
			tempValue = 2;
			for (int i = s.size() - 3; i >= s.size() - 7; i--) {
				if (s.at(i) == '2' || s.at(i) == '3')
					tempValue *= 5;
				else
					break;
			}
		}
		else if (s.at(s.size() - 2) == '3') {
			if (s.at(s.size() - 3) == '1') {
				tempValue = 5;
				for (int i = s.size() - 4; i >= s.size() - 7; i--) {
					if (s.at(i) == '1' || s.at(i) == '3')
						tempValue *= 5;
					else
						break;
				}
			}
			else if (s.at(s.size() - 3) == '2') {
				tempValue = 2;
				for (int i = s.size() - 4; i >= s.size() - 7; i--) {
					if (s.at(i) == '2' || s.at(i) == '3')
						tempValue *= 5;
					else
						break;
				}
			}
			else
				tempValue = 0;
		}
		else
			tempValue = 0;

		if (value < tempValue)
			value = tempValue;
	}

	return value;
}

// 우선순위 큐 디버그용
void debugPrint() {
	vector<valued_point> vp;
	string tmp;

	while (!myQueue.empty()) {
		vp.push_back(myQueue.top());
		myQueue.pop();
	}

	fp = fopen("myLog.txt", "a");
	fprintf(fp, "debug: ");
	for (auto a : vp) {
		if (fp != NULL) {
			tmp = to_string(a.first) + string("_(") + to_string(a.second.first) + string(", ") + to_string(a.second.second) + string(")   ");
			fprintf(fp, tmp.c_str());
		}
		myQueue.push(a);
	}
	if (fp != NULL)
		fprintf(fp, "\n");
	fclose(fp);
}
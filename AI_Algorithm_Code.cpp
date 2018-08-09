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

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:1234567890,Department:AI부서[C]" };

double inclination;
int searchLimit = 100;
int currentCount;

// 한 좌표가 가지는 노드
class Node {
private:
	int x, y;
	int count = 0, weight = 0;
	Node *parent = nullptr;
public:
	std::vector<Node *> child;

	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	int getCount() {
		return this->count;
	}
	int getWeight() {
		return this->weight;
	}
	Node getParent() {
		return *this->parent;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setChild(Node *n) {
		child.push_back(n);
	}
	void setParent(Node *p) {
		parent = p;
	}
	void setCount(int count) {
		this->count = count;
	}
	void setWeight(int weight) {
		this->weight = weight;
	}
	void update(int weight) {
		this->count += 1;
		this->weight += weight;
	}
	Node() {}
	Node(int x, int y, int count = 0) {
		this->x = x;
		this->y = y;
		this->count = count;
	}
	Node(int x, int y, int count, int weight) {
		this->x = x;
		this->y = y;
		this->count = count;
		this->weight = weight;
	}
	~Node() {}
	void operator =(Node *other) {
		this->x = (*other).x;
		this->y = (*other).y;
		this->count = (*other).count;
		this->weight = (*other).weight;
	}
};

std::vector<Node> bestChildren;

void myturn(int cnt) {

	int x[2], y[2];

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	srand((unsigned)time(NULL));

	if (cnt == 1) {
		x[0] = 9; y[0] = 9;

		while (!isFree(x[0], y[0])) {		
			int sign = rand() % 2;			

			if (sign == 1) {						
				x[0] += rand() % 2;
				y[0] += rand() % 2;
			}
			else {							
				x[0] -= rand() % 2;
				y[0] -= rand() % 2;
			}
		}
	}
	else {

	}

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);
}

void MCTS() {
	int virtualBoard[19][19];
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			virtualBoard[i][j] = 0;
		}
	}

	for (Position &p : myLog) {
		int x = p.getX();
		int y = p.getY();
		Node root(x, y);
		virtualBoard[x][y] = 1;
		currentCount = 0;
		
		selection(root, virtualBoard, 0);

		bestChildren.push_back(bestChild(root));
	}
}

void selection(Node parent, int vB[19][19], int level) {
	for (int x = parent.getX() - 1; x <= parent.getX() + 1; x++) {
		for (int y = parent.getY() - 1; y <= parent.getY() + 1; y++) {
			if (vB[x][y] != 0) continue;

			Node child(x, y);
			child.setParent(&parent);
			parent.setChild(&child);

			int pos = showBoard(x, y);
			bool line = lineCheck(parent.getX(), parent.getY(), x, y, level + 1);

			if (currentCount >= searchLimit) {
				// 검사횟수 초과시 최고의 자식노드를 찾기 위해 selection을 모두 빠져나간다.
				return;
			}
			else {
				currentCount++;
				if (promising(child, line, pos)) {
					selection(child, )
				}
			}
		}
	}
}
bool promising(Node child, bool line, int pos) {
	
}

void expansion(Node parent) {
	
}

Node bestChild(Node parent) {
	// 최고의 자식 노드를 찾는다.
	Node best(-1, -1);

	// 노드의 가중치 / 노드의 방문 횟수 : 방문횟수에 따른 추가된 가중치량이 많을수록 중요.
	double rate = 0.0;
	for (Node *child : parent.child) {
		double temp = child->getWeight() / child->getCount();
		if (rate > temp) {
			rate = temp;
			best = child;
		}
	}

	return best;
}



// sub function
bool empty(int pos) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (showBoard(i, j) == pos) return false;
			return true;
		}
	}
}

bool lineCheck(int bx, int by, int cx, int cy, int level) {
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


/*
// 우선순위 1 : 내 돌이 6개가 될 수 있는지 검사
// 우선순위 2 : 적 돌이 6개가 될 수 있는지 검사
if (pos == 0) {
if (line) {
// 가정1-1 : 빈 공간에 돌을 놓을 경우와 상대방이 놓을 경우로 나눈다.
vB[x][y] = 1; // 내 돌을 놓을 경우
child.setWeight(100 * level);
selection(child, vB, level);
vB[x][y] = 2; // 내 돌을 놓지 않을 경우
child.setWeight(-100 * level);
selection(child, vB, level);
}
// 나중에 else문 추가
else {
// 가정1-2 : 선형성이 안되는 빈 공간에서는 돌을 놓음으로써 다른 방향으로 영향을 줄 수 있는지 확인해야 한다.
vB[x][y] = 1;
//child.setWeight(0);
selection(child, vB, level);
vB[x][y] = 2;
child.setWeight(-100);
selection(child, vB, level);
}
}
else if (pos == 1) {
vB[x][y] = 1;
if (line) {
// 가정 2-1 : 내 돌이 선형성을 유지하면서 있을 때는 선형성 방향에 있는 공간을 확인해야 한다.
selection(child, vB, level);
}
else {
// 가정 2-2 : 내 돌이 선형성을 유지하지 않으면 그 돌을 기준으로 유리한 지점이 있는지 검사한다.
selection(child, vB, 1);
}
}
else if (pos == 2) {
vB[x][y] = 2;
if (line) {
selection(child);
}
}

*/
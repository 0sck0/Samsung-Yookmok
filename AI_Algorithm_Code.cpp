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

using namespace std;

vector<Position> myLog;
vector<Position> enemyLog;
double inclination;
int virtualBoard[19][19];

void myturn(int cnt) {

	int x[2], y[2];

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	srand((unsigned)time(NULL));

	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\노유찬\\Desktop\\육목\\Version\\2018_08_09\\log.txt", "a");

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
		for(int i=0; i<cnt; i++) {
			Node *solution = yukmok();
			x[i] = solution->getX();
			y[i] = solution->getY();
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fprintf(file_pointer, "%d ", virtualBoard[j][i]);
		}
		fprintf(file_pointer, "\n");
	}
	fprintf(file_pointer, "\n\n");
	
	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);
}

Node* yukmok() {
	// 출력용 virtualBoard
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			virtualBoard[i][j] = showBoard(i, j);
		}
	}

	// 마지막으로 뒀던 수를 기반으로 MCTS
	Position &p = myLog.back();
	myLog.pop_back();
	Node *root = new Node(p.getX(), p.getY());
	root->setUnit(showBoard(p.getX(), p.getY()));
	virtualBoard[p.getX()][p.getY()] = showBoard(p.getX(), p.getY());
	return MCTS(root);
}

Node* MCTS(Node* root) {
	int turn = -1, count = 2;
	if (root->getUnit() == 1) {
		turn = 1; count = 1;
	}
	Node *child = new Node();
	for (int i = 0; i < 50; i++) {
		child = selection(root, &turn, &count);
		int simulation_result = simulation(child);
		backpropagate(child, simulation_result);
	}

	return best_child(root->child);
}

Node* selection(Node* node, int *turn, int *count) {
	// 자식 노드를 최대한 만든다.
	while (non_terminal(node)) {
		if (!fully_expanded(node)) {
			node = expand(node, turn, count);
		}
		else {
			node = best_child(node->child);
		}
	}
	
	// 자식노드를 다 만들면 방문하지 않은 자식노드를 찾아서 반환한다.
	return pick_unvisited(node->child);
}

// root가 들어오면 Tree를 구성하도록 함
Node* expand(Node *node, int *turn, int *count) {
	for (int y = node->getY() - 1; y <= node->getY() + 1; y++) {
		for (int x = node->getX() - 1; x <= node->getX() + 1; x++) {
			// 확장 중에서 중복 방지
			bool overlap = false;
			for (Node *p : node->child) {
				if (x == p->getX() && y == p->getY()) overlap = true;
			}
			if (overlap) continue;

			// 중복 아닌 자식 노드는 추가됨
			int pos = showBoard(x, y);
			Node *child = new Node(x, y);

			node->setChild(child);
			child->setParent(node);

			if (*count == 0) {
				*turn *= -1;
				*count = 2;
			}

			if (pos == 0) {
				if (*turn == 1) {
					child->setUnit(1);
					virtualBoard[x][y] = 1;
				}
				else {
					child->setUnit(2);
					virtualBoard[x][y] = 2;
				}
			}
			else if (pos == 1) {
				child->setUnit(1);
			}
			else if (pos == 2) {
				child->setUnit(2);
			}
			else {
				if (*turn == 1) {
					child->setUnit(1);
				}
				else {
					child->setUnit(2);
				}
			}
		}
	}
	*count -= 1;
	return node;
}

Node* pick_unvisited(vector<Node*> child) {
	// 방문하지 않은 자식 노드 찾기
	for (Node *p : child) {
		if (p->getCount() == 0) return p;
	}
}

bool fully_expanded(Node* node) {
	// 확장 최대크기 지정
	if (node->child.size() == 8) return true;
	else return false;
}

bool non_terminal(Node *node) {
	return is_gameEnd(node);
}

int simulation(Node *node) {
	while (non_terminal(node)) {
		node = policy(node);
	}

	return result(node);
}

Node* pick_random(vector<Node*> child) {
	// 랜덤 시뮬을 위해
	srand((unsigned)time(NULL));
	return child[rand() % child.size()];
}

// 가능하면 유망한 것을 찾아야 할듯
Node* policy(Node *node) {
	return pick_random(node->child);
}

void backpropagate(Node* node, int result) {
	// 마지막에 게임이 끝난 부분에서 root 까지 올라가면서 result를 부여해준다.
	if (node->getParent() == nullptr) return;
	node->update(result);
	backpropagate(node->getParent(), result);
}

Node* best_child(vector<Node*> child, double cnode_parameter) {
	double maxVal = 0.0;

	// weight가 가장 높은 자식노드를 선택
	for (Node *c : child) {
		c->setWeight((c->getWin() / c->getCount()) + cnode_parameter * sqrt((2 * log(c->getCount())) / c->getCount()));

		if (maxVal < c->getWeight()) {
			maxVal = c->getWeight();
		}
	}

	for (Node *c : child) {
		if (maxVal == c->getWeight()) {
			return c;
		}
	}
}

bool is_gameEnd(Node* node) {
	return result(node) == 1;
}


int result(Node* node) {

	if (checkSix(node, 1, 1) || checkSix(node, -1, 1) || checkSix(node, 0, 1) || checkSix(node, 1, 0)) {
		return 1;
	}
	return 0;
}

bool checkSix(Node* node, int incX, int incY) {
	int pos = node->getUnit();;
	int x = node->getX();
	int y = node->getY();
	int six = 1;
	
	while (true) {
		if (showBoard(x + incX, y + incY) == pos) six++;
		else if (showBoard(x - incX, y - incY) == pos) six++;
		
		if (six > 6) return false;
		else {
			if (six == 6) return true;
		}
	}
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



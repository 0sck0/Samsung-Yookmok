// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI �ڵ� �ۼ� ���]

1. char info[]�� �迭 �ȿ�					"TeamName:�ڽ��� ����,Department:�ڽ��� �Ҽ�"					������ �ۼ��մϴ�.
( ���� ) Teamname:�� Department:�� �� ���� �մϴ�.
"�ڽ��� ����", "�ڽ��� �Ҽ�"�� �����ؾ� �մϴ�.

2. �Ʒ��� myturn() �Լ� �ȿ� �ڽŸ��� AI �ڵ带 �ۼ��մϴ�.

3. AI ������ �׽�Ʈ �Ͻ� ���� "���� �˰����ȸ ��"�� ����մϴ�.

4. ���� �˰��� ��ȸ ���� �����ϱ⿡�� �ٵϵ��� ���� ��, �ڽ��� "����" �� �� �˰����� �߰��Ͽ� �׽�Ʈ �մϴ�.



[���� �� �Լ�]
myturn(int cnt) : �ڽ��� AI �ڵ带 �ۼ��ϴ� ���� �Լ� �Դϴ�.
int cnt (myturn()�Լ��� �Ķ����) : ���� �� �� �־��ϴ��� ���ϴ� ����, cnt�� 1�̸� ���� ���� ��  �� ����  �δ� ��Ȳ(�� ��), cnt�� 2�̸� �� ���� ���� �δ� ��Ȳ(�� ��)
int  x[0], y[0] : �ڽ��� �� ù �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
int  x[1], y[1] : �ڽ��� �� �� �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
void domymove(int x[], int y[], cnt) : �� ������ ��ǥ�� �����ؼ� ���


//int board[BOARD_SIZE][BOARD_SIZE]; �ٵ��� �����Ȳ ��� �־� �ٷλ�� ������. ��, ���������ͷ� ���� �������
// ������ ���� ��ġ�� �ٵϵ��� ������ �ǰ��� ó��.

boolean ifFree(int x, int y) : ���� [x,y]��ǥ�� �ٵϵ��� �ִ��� Ȯ���ϴ� �Լ� (������ true, ������ false)
int showBoard(int x, int y) : [x, y] ��ǥ�� ���� ���� �����ϴ��� �����ִ� �Լ� (1 = �ڽ��� ��, 2 = ����� ��, 3 = ��ŷ)


<-------AI�� �ۼ��Ͻ� ��, ���� �̸��� �Լ� �� ���� ����� �������� �ʽ��ϴ�----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:1234567890,Department:AI�μ�[C]" };

using namespace std;

vector<Position> myLog;
vector<Position> enemyLog;
double inclination;
int virtualBoard[19][19];

void myturn(int cnt) {

	int x[2], y[2];

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	srand((unsigned)time(NULL));

	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\������\\Desktop\\����\\Version\\2018_08_09\\log.txt", "a");

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
	
	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);
}

Node* yukmok() {
	// ��¿� virtualBoard
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			virtualBoard[i][j] = showBoard(i, j);
		}
	}

	// ���������� �״� ���� ������� MCTS
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
	// �ڽ� ��带 �ִ��� �����.
	while (non_terminal(node)) {
		if (!fully_expanded(node)) {
			node = expand(node, turn, count);
		}
		else {
			node = best_child(node->child);
		}
	}
	
	// �ڽĳ�带 �� ����� �湮���� ���� �ڽĳ�带 ã�Ƽ� ��ȯ�Ѵ�.
	return pick_unvisited(node->child);
}

// root�� ������ Tree�� �����ϵ��� ��
Node* expand(Node *node, int *turn, int *count) {
	for (int y = node->getY() - 1; y <= node->getY() + 1; y++) {
		for (int x = node->getX() - 1; x <= node->getX() + 1; x++) {
			// Ȯ�� �߿��� �ߺ� ����
			bool overlap = false;
			for (Node *p : node->child) {
				if (x == p->getX() && y == p->getY()) overlap = true;
			}
			if (overlap) continue;

			// �ߺ� �ƴ� �ڽ� ���� �߰���
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
	// �湮���� ���� �ڽ� ��� ã��
	for (Node *p : child) {
		if (p->getCount() == 0) return p;
	}
}

bool fully_expanded(Node* node) {
	// Ȯ�� �ִ�ũ�� ����
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
	// ���� �ù��� ����
	srand((unsigned)time(NULL));
	return child[rand() % child.size()];
}

// �����ϸ� ������ ���� ã�ƾ� �ҵ�
Node* policy(Node *node) {
	return pick_random(node->child);
}

void backpropagate(Node* node, int result) {
	// �������� ������ ���� �κп��� root ���� �ö󰡸鼭 result�� �ο����ش�.
	if (node->getParent() == nullptr) return;
	node->update(result);
	backpropagate(node->getParent(), result);
}

Node* best_child(vector<Node*> child, double cnode_parameter) {
	double maxVal = 0.0;

	// weight�� ���� ���� �ڽĳ�带 ����
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

	// level�� 2 ���ϸ� ���� 2��° �˻��ϴ� ���� �ǹ�
	if (level <= 2) {
		if ((cx - bx) == 0)
			inclination = 10000.0;	// �и� 0 �� ���
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



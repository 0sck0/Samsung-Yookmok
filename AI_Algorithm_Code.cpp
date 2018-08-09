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

double inclination;
int searchLimit = 100;
int currentCount;

// �� ��ǥ�� ������ ���
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

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

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

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
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
				// �˻�Ƚ�� �ʰ��� �ְ��� �ڽĳ�带 ã�� ���� selection�� ��� ����������.
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
	// �ְ��� �ڽ� ��带 ã�´�.
	Node best(-1, -1);

	// ����� ����ġ / ����� �湮 Ƚ�� : �湮Ƚ���� ���� �߰��� ����ġ���� �������� �߿�.
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


/*
// �켱���� 1 : �� ���� 6���� �� �� �ִ��� �˻�
// �켱���� 2 : �� ���� 6���� �� �� �ִ��� �˻�
if (pos == 0) {
if (line) {
// ����1-1 : �� ������ ���� ���� ���� ������ ���� ���� ������.
vB[x][y] = 1; // �� ���� ���� ���
child.setWeight(100 * level);
selection(child, vB, level);
vB[x][y] = 2; // �� ���� ���� ���� ���
child.setWeight(-100 * level);
selection(child, vB, level);
}
// ���߿� else�� �߰�
else {
// ����1-2 : �������� �ȵǴ� �� ���������� ���� �������ν� �ٸ� �������� ������ �� �� �ִ��� Ȯ���ؾ� �Ѵ�.
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
// ���� 2-1 : �� ���� �������� �����ϸ鼭 ���� ���� ������ ���⿡ �ִ� ������ Ȯ���ؾ� �Ѵ�.
selection(child, vB, level);
}
else {
// ���� 2-2 : �� ���� �������� �������� ������ �� ���� �������� ������ ������ �ִ��� �˻��Ѵ�.
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
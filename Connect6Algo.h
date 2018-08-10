// Samsung Go Tournament Form C Connect6Algo Header (g++-4.8.3)

// <--------------- 이 Code를 수정하면  작동하지 않을 수 있습니다 ------------------>

#pragma once
extern int width, height;
extern int terminateAI;
extern unsigned s_time;

extern FILE *fp;


extern int isFree(int x, int y);
extern int showBoard(int x, int y);
extern void init();
extern void restart();
extern void mymove(int x[], int y[], int cnt = 2);
extern void opmove(int x[], int y[], int cnt = 2);
extern void block(int, int);
extern int setLine(char *fmt, ...);
extern void domymove(int x[], int y[], int cnt = 2);
extern void writeLog(char *log);

void myturn(int cnt = 2);
char info[];

// Add 
class Position {
private:
	int x;
	int y;
public:
	Position() {}
	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() { return this->x; }
	int getY() { return this->y; }
	~Position() {}
};

#include <vector>
extern std::vector<Position> myLog;
extern std::vector<Position> enemyLog;

// 한 좌표가 가지는 노드
class Node {
private:
	int x, y;
	int count = 0, win = 0;
	int unit;
	double weight = 0.0;
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
	int getWin() {
		return this->win;
	}
	int getWeight() {
		return this->weight;
	}
	int getUnit() {
		return this->unit;
	}
	Node* getParent() {
		return this->parent;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setWeight(double weight) {
		this->weight = weight;
	}
	void setChild(Node *n) {
		child.push_back(n);
	}
	void setParent(Node *p) {
		parent = p;
	}
	void setUnit(int unit) {
		this->unit = unit;
	}
	void addCount(int count) {
		this->count += count;
	}
	// result는 시뮬 결과 이기면 1, 지면 0이 들어온다.
	void update(int result) {
		this->count += 1;
		this->win += result;
	}
	Node() {}
	Node(int x, int y, int count = 0) {
		this->x = x;
		this->y = y;
		this->count = count;
	}
	Node(int x, int y, int count, int win) {
		this->x = x;
		this->y = y;
		this->count = count;
		this->win = win;
	}
	~Node() {}
	void operator =(Node *other) {
		this->x = (*other).x;
		this->y = (*other).y;
		this->count = (*other).count;
		this->win = (*other).win;
	}
	bool operator ==(Node &other) {
		if (this->x == other.getX() && this->y == other.getY()) return true;
		else return false;
	}
};

// MCTS
Node* yukmok();
Node* MCTS(Node* root);
Node* selection(Node* node, int turn);
Node* expand(Node *node, int turn);
Node* pick_unvisited(std::vector<Node*> child);
bool fully_expanded(Node* node);
bool non_terminal(Node *node);
int simulation(Node *node);
Node* pick_random(std::vector<Node*> child);
Node* policy(Node *node);
void backpropagate(Node* node, int result);
Node* best_child(std::vector<Node*> child, double cnode_parameter = 1.4);
bool is_gameEnd(Node* node);
int result(Node* node);
bool checkSix(Node* node, int incX, int incY);


// Sub Function
bool empty(int pos);
bool line_check(int bx, int by, int cx, int cy, int level);
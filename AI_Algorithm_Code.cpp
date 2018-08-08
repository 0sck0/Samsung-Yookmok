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

#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:1234567890,Department:AI�μ�[C]" };

float inclination;			// �ٵϵ� ������ �˻� ����
int val[19][19];			// ��ü ����ġ�� ��Ÿ���� �迭
int center_x, center_y;		// �߽��� �Ǵ� x, y ��ǥ ��
int myTracker[19][19];
int opTracker[19][19];

void myturn(int cnt) {

	int x[2], y[2];
	int maxVal = 1;			// ����ġ �� ���� ū ��

							// ��������� log Ȯ��
	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\YC\\Desktop\\c++\\����\\�Ｚ����DS�ι�����SW�˰����ȸ\\SamsungGo_AI_Code_C_C++\\log.txt", "a");

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	srand((unsigned)time(NULL));

	// ����ġ 0���� �ʱ�ȭ
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			val[i][j] = 0;
		}
	}

	if (empty()) {			// ù �� �� ���
		x[0] = 9;			// 9, 9 �� �⺻
		y[0] = 9;

		while (!isFree(x[0], y[0])) {		// ���� �ٸ� ���� ���� ���(block)
			int sign = rand() % 2;			// ��ȣ�� ������ �� ��, ����� �� ��

			if (sign) {						// ����� ��� �����ϰ� ��ǥ�� ����
				x[0] += rand() % 2;
				y[0] += rand() % 2;
			}
			else {							// ������ ��� �����ϰ� ��ǥ�� ��
				x[0] -= rand() % 2;
				y[0] -= rand() % 2;
			}
		}
	}
	else {
		setMyWeight();
		setEnemyWeight();
	}

	// �α� ���
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

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);

}

// �� �� �˻�
void setMyWeight() {
	for(Position &p : myLog) {
		int x = p.getX();
		int y = p.getY();
		center_x = x;
		center_y = y;

		val[y][x] = -1;

		// �˻��ߴ� ���� �ٽ� �˻����� �ʵ��� myTracker ���
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				myTracker[i][j] = 0;				// �ʱ�ȭ
			}
		}

		searchMyTree(x, y, 1);						// level 1���� ����
	}
}

void searchMyTree(int x, int y, int level) {
	// 3x3 �˻�
	for (int j = y - 1; j <= y + 1; j++) {
		for (int i = x - 1; i <= x + 1; i++) {

			int pos = showBoard(i, j);
			bool line = line_check(x, y, i, j, level + 1);

			if (i == x && j == y) continue;				// ���� �״� x, y ��ǥ pass
			else if (myTracker[i][j] == 1) continue;	// tracker�� �̿��ؼ� ���� �˻��ߴ� �κ��� pass
			else myTracker[i][j] = 1;					// �˻����� ������ ���� �˻������Ƿ� ���� 1�� ����

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


// �� �� �˻�
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

		searchEnemyTree(x, y, 1);	// level 1���� ����
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

// �ΰ����� �Լ���

// ���尡 �� �������� Ȯ��
bool empty() {
	int count = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (showBoard(i, j) == 1 || showBoard(i, j) == 2) return false;
		}
	}

	return true;
}

// ������ �˻� �Լ�
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

// ������ �ݴ��� ��ġ ����ġ ����
void set_opposition(int x, int y) {
	for (int j = center_y - 1; j <= center_y + 1; j++) {
		for (int i = center_x - 1; i <= center_x + 1; i++) {
			if (line_check(center_x, center_y, i, j, 3) && showBoard(i, j) == 0) {
				val[j][i] -= 50;
			}
		}
	}
}
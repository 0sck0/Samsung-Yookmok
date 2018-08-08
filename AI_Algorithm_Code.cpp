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
#include <limits>

using namespace std;

// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:1234567890,Department:AI�μ�[C]" };

float inclination;			// �ٵϵ� ������ �˻� ����
int val[19][19] = { 0, };			// ��ü ����ġ�� ��Ÿ���� �迭
int center_x, center_y;		// �߽��� �Ǵ� x, y ��ǥ ��

void myturn(int cnt) {

	int x[2], y[2];
	int maxVal = 1;			// ����ġ �� ���� ū ��

	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\�ִ���\\Desktop\\R\\log.txt", "a");

	// ��������� log Ȯ��


	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	srand((unsigned)time(NULL));

	// ����ġ 0���� �ʱ�ȭ
	/*
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++){
			val[i][j] = 0;
		}
	}
	*/
	if (cnt == 1) {			// ù �� �� ���
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
		if (enemyLog[1][0] == -1 && myLog[1][0] == -1) {
			setEnemyWeight(1);
		}
		else if (myLog[1][0] == -1) {
			setMyWeight(1);
			setEnemyWeight(cnt);
		}
		else {
			setEnemyWeight(cnt);
			setMyWeight(cnt);
		}
	}

	// �α� ���
	fprintf(file_pointer, "\n");
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fprintf(file_pointer, "%.4d ", val[i][j]);
		}
		fprintf(file_pointer, "\n");
	}

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
	fclose(file_pointer);

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);

}

// �� �� �˻�
void setMyWeight(int cnt) {
	int weight = 0;

	for (int i = 0; i < cnt; i++) {
		int x = myLog[i][0];
		int y = myLog[i][1];
		center_x = x;
		center_y = y;

		val[y][x] = -1;

		searchMyTree(x, y, 0, 0, 1);	// level 1���� ����
	}
}

int searchMyTree(int x, int y, int incX, int incY, int level) {

	for (int j = -1; j <=  1; j++) {
		for (int i = -1; i <= 1; i++) {
			int pos = showBoard(x + i, y + j);
			int mipos = showBoard(x - i, y - j);
			if ((i == 0 && j == 0) || (i == incX * -1 && j == incY * -1)) continue;

			if (pos == 0) {
				val[y + j][x + i] += 10;
				if (incX == i && incY == j)
				{
					val[y + j][x + i] = 200 * level;
					if (level >= 2 && showBoard(x + (-i * (level)), y + (-j * (level ))) == 0)
						val[y + (-j * level)][x + (-i * level)] = 200 * level;
				}

			}
			else if (pos == 1 || pos == 3) {
				val[y + j][x + i] = -1;
				if (level == 1)
					return searchEnemyTree(x + i, y + j, i, j, level + 1);
				else if (incX == i && incY == j) return searchMyTree(x + i, y + j, i, j, level + 1);
				else if (mipos == 1 || mipos == 3)
				{
					int end = searchMyTree(x + i, y + j, i, j, 2);
					int end1 = searchMyTree(x - i, y - j, -i, -j, 2);
					if (showBoard(x + (i * end), y + (j * end)) == 0)
						val[y + (j * end)][x + (i * end)] = (end + end1 - 1) * 200;
					if (showBoard(x + (-i * end), y + (-j * end)) == 0)
						val[y + (-j * end1)][x + (-i * end1)] = (end + end1 - 1) * 200;
				}
			}
			else {
				if (incX == i && incY == j) {
					val[y + j][x + i] = -2;
					if (level >= 2 && showBoard(x + (-i * (level)), y + (-j * (level))) == 0)
						val[y + (-j * level)][x + (-i * level)] = 200 * level;
				}
				else val[y + j][x + i] = -2;
			}
		}
	}
	return level;
}


// �� �� �˻�
void setEnemyWeight(int cnt) {
	int weight = 0;

	for (int i = 0; i < cnt; i++) {
		int x = enemyLog[i][0];
		int y = enemyLog[i][1];

		val[y][x] = -1;

		searchEnemyTree(x, y, 0, 0, 1);	// level 1���� ����
	}
}

int searchEnemyTree(int x, int y, int incX, int incY, int level) {

	for (int j = -1; j <= 1; j++) {
		for (int i = -1; i <= 1; i++) {
			int pos = showBoard(x + i, y + j);
			int mipos = showBoard(x - i, y - j);
			if ((i == 0 && j == 0) || (i == incX * -1 && j == incY * -1)) continue;

			if (pos == 0) {
				val[y + j][x + i] += 10;
				if (incX == i && incY == j)
				{
					val[y + j][x + i] = 200 * level;
					if (level >= 2 && showBoard(x + (-i * (level)), y + (-j * (level))) == 0)
						val[y + (-j * level)][x + (-i * level)] = 200 * level;
				}
			}
			else if (pos == 2 || pos == 3) {
				val[y + j][x + i] = -2;
				if (level == 1)
					return searchEnemyTree(x + i, y + j, i, j, level + 1);
				else if (incX == i && incY == j) return searchEnemyTree(x + i, y + j, i, j, level + 1);
				else if (mipos == 2 || mipos == 3)
				{
					int end = searchEnemyTree(x + i, y + j, i, j, 2);
					int end1 = searchEnemyTree(x - i, y - j, -i, -j, 2);
					if (showBoard(x + (i * end), y + (j * end)) == 0)
						val[y + (j * end)][x + (i * end)] = (end + end1-1) * 200;
					if (showBoard(x + (-i * end), y + (-j * end)) == 0)
						val[y + (-j * end1)][x + (-i * end1)] = (end + end1-1) * 200;
				}
			}
			else {
				if (incX == i && incY == j) {
					val[y + j][x + i] = -1;
					if (level >= 2 && showBoard(x + (-i * (level)), y + (-j * (level))) == 0)
						val[y + (-j * level)][x + (-i * level)] = 200 * level;
				}
				else val[y + j][x + i] = -1;
			}
		}
	}
	return level;
}

// �ΰ����� �Լ���

// ���尡 �� �������� Ȯ��
bool empty() {
	int count = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (showBoard(i, j) != 0) return false;
		}
	}

	return true;
}

// ������ �˻� �Լ�
bool line_check(int bx, int by, int cx, int cy, int level) {

	// level�� 2 ���ϸ� ���� 2��° �˻��ϴ� ���� �ǹ�
	if (level <= 2) {
		if ((cy - by) == 0)
			inclination = 10000.0;	// �и� 0 �� ���
		else
			inclination = (cx - bx) / (cy - by);

		if (inclination == 0.0 || inclination == 1.0 || inclination == -1.0 || inclination == 10000.0) return true;
		else false;
	}
	else if (level > 2) {
		double temp;
		if ((cy - by) == 0) {
			temp == 10000.0;
		}
		else {
			temp = (cx - bx) / (cy - by);
		}

		if (inclination == temp) return true;
		else return false;
	}
	return false;
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
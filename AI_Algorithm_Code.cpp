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

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"
#include <cmath>
#include <algorithm>


using namespace std;

// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:1234567890,Department:AI�μ�[C]" };

float inclination;
int gx = -1, gy = -1;		// good
int lx, ly;					// last
int val[19][19];			// weight_val
int center_x, center_y;


void myturn(int cnt) {
	//int x[2], y[2];

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	int maxVal = 1;
	int x[2], y[2];
	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\YC\\Desktop\\c++\\����\\fuck.txt","w");

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			val[i][j] = 0;
		}
	}

	srand((unsigned)time(NULL));

	if (cnt == 1) {
		do {
			x[0] = rand() % width;
			y[0] = rand() % height;
			if (terminateAI) return;
		} while (!isFree(x[0], y[0]));
	}
	else {
		if (enemyLog[1][0] == -1 && myLog[1][0] == -1)
		{
			setEnemyWeight(1);
		}
		else if (myLog[1][0] == -1)
		{
			setMyWeight(1);
			setEnemyWeight(cnt);
		}
		else
		{
			setEnemyWeight(cnt);
			setMyWeight(cnt);
		}
		
		for (int z = 0; z < 19; z++)
		{
			for (int q = 0; q < 19; q++)
			{
				fprintf(file_pointer, "%d ", val[z][q]);
			}
			fprintf(file_pointer, "\n");
		}

		for (int i = 0; i < cnt; i++)
		{
			maxVal = 1;
			for (int j = 0; j < 19; j++)
			{
				for (int k = 0; k < 19; k++)
				{
					if (maxVal < val[j][k])
					{
						maxVal = val[j][k];
						y[i] = j;
						x[i] = k;
					}
				}

			}

			val[y[i]][x[i]] = -1;

			if (terminateAI) return;
		}
	}
	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);
}
 

// �� �� �˻�.

void setMyWeight(int cnt) {
	int weight = 0;

	for (int i = 0; i < cnt; i++) {
		int x = myLog[i][0];
		int y = myLog[i][1];
		center_x = x;
		center_y = y;

		val[y][x] = -1;

		for (int j = y -1; j <= y + 1; j++) {
			for (int k = x -1; k <= x + 1; k++) {
				int pos = showBoard(k, j);
				if (j == y && k == x) continue;
				if (pos == 0) {						// 0�϶�
					val[j][k] += 50;				// ����ġ 50
				}
				else if (pos == 1 || pos == 3) {	// �� ���� ���� ��
					val[j][k] = -1;					// ����ġ -1
					searchMyTree(x, y, k, j, 2);	// level = 2�� searchTree�� �ѱ�
				}
				else {								// �� ���� ���� ��
					val[j][k] = -10;				// ����ġ -10
					set_opposition(k, j);			// �� �ݴ뵹�� �����ϸ� �� ������
				}
			}
		}
	}
}

void searchMyTree(int bx, int by, int x, int y, int level) {
	for (int j = y - 1; j <= y + 1; j++) {							// 3x3 �˻�
		for (int i = x - 1; i <= x + 1; i++) {
			if ((i == x && j == y) || (i == bx && j == by)) continue;
			
			int pos = showBoard(i, j);								
			bool line = line_check(x, y, i, j, level+1);
			
			if (pos == 0) {
				val[j][i] += 50;
				if (line == true) val[j][i] += 200 * level;
			}
			else if (pos == 1 || pos == 3) {
				val[j][i] = -1;
				if (line == true) searchMyTree(x, y, i, j, level+1);
				else searchMyTree(x, y, i, j, 1);	
			}
			else {
				if (line == true) {
					val[j][i] = -20;
					set_opposition(i, j);
				}
				else val[j][i] = -10;
			}
		}
	}
}

void set_opposition(int x, int y) {
	for (int i = center_x - 1; i <= center_x + 1; i++) {
		for (int j = center_y - 1; j <= center_y + 1; j++) {
			if (line_check(center_x, center_y, i, j, 3) && showBoard(i, j) == 0) {
				val[j][i] = -50;
			}
		}
	}
}

void searchEnemyTree(int bx, int by, int x, int y, int level) {
	for (int j = y - 1; j <= y + 1; j++) {
		for (int i = x - 1; i <= x + 1; i++) {
			if ((i == x && j == y) || (i == bx && j == by)) continue;

			int pos = showBoard(i, j);
			bool line = line_check(x, y, i, j, level + 1);

			if (pos == 0) {
				val[j][i] += 50;
				if (line == true) val[j][i] += 200 * level;
			}
			else if (pos == 2 || pos == 3) {
				val[j][i] = -1;
				if (line == true) searchMyTree(x, y, i, j, level + 1);
				else searchMyTree(x, y, i, j, 1);
			}
			else {
				if (line == true) {
					val[j][i] = -20;
					set_opposition(i, j);
				}
				else val[j][i] = -10;
			}
		}
	}
}

// �� �� �˻�

void setEnemyWeight(int cnt) {
	int weight = 0;

	for (int i = 0; i < cnt; i++) {
		int x = enemyLog[i][0];
		int y = enemyLog[i][1];

		val[y][x] = -10;

		for (int j = y - 1; j <= y + 1; j++) {
			for (int k = x - 1; k <= x + 1; k++) {
				int pos = showBoard(k, j);
				if (j == y && k == x) continue;
				if (pos == 0) {			// 0�϶�
					val[j][k] += 20;				// ����ġ 20
				}
				else if (pos == 2 || pos == 3) {
					val[j][k] = -10;
					searchMyTree(x, y, k, j, 2);
				}
				else {
					val[j][k] = -1;
				}
			}
		}
	}
}

// �������� �˻��ϴ� �Լ�
bool line_check(int bx, int by, int cx, int cy, int level) {
	if (level <= 2) {
		inclination = (cx - bx) / (cy - by);
		
		if (inclination == 0 || inclination == 1.0 || inclination == -1.0) return true;
		else false;
	}
	else if (level > 2) {
		double temp = (cx - bx) / (cy - by);
		if (inclination == temp) return true;
		else return false;
	}
	else {
		return true;
	}
	return false;
}

// ó�� ���� init ���¸� Ȯ��
bool empty() {
	int count = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (showBoard(i, j) != 0) return false;
		}
	}

	return true;
}

// 2���� �迭 ����ġ �ִ밪 ã�� ��ǥ ����
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


/*
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
			if (showBoard(x, y) == 1) {			// �� ���� ���� �˻�.
				around(x, y, 1);				// count 1���� �����Ͽ� �ֺ� ���� �˻�.
			}
		}
	}

	m_find();
	return;
}

void around(int x, int y, int count) {
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= j + 1; j++) {
			if ((i == x && j == y ) || (i == lx && j == ly)) continue;
			if (count < 6 && line_check(x, y, i, j, count++)) {
				if (showBoard(i, j) == 0) {
					val[i][j] += 1;
				}
				else if (showBoard(i, j) == 1) {
					lx = x; ly = y;
					around(i, j, count);
				}
				else {
					val[i][j] -= 1;
				}
			}
		}
	}
}
*/

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
int gx, gy;
int val[19][19];

void myturn(int cnt) {

	//int x[2], y[2];

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	int x[2], y[2];

	srand((unsigned)time(NULL));

	for (int i = 0; i < cnt; i++) {
		do {
			next();
			x[i] = gx;
			y[i] = gy;
			if (terminateAI) return;
		} while (!isFree(x[i], y[i]));

		if (x[1] == x[0] && y[1] == y[0]) i--;
	}

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);
}

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
			else if (showBoard(x, y) == 2) {	// �� ���� �˻�.
				around(x, y, 0);
			}
		}
	}

	m_find();
	return;
}

void around(int x, int y, int count) {
	cout << "Ƚ��: " << count << endl;
	for (int i = x - 1; i <= x + 1, i != x; i++) {
		for (int j = y - 1; j <= j + 1, j != y; j++) {
			if (count <= 6 && line_check(x, y, i, j, count++)) {
				if (showBoard(i, j) == 0) {
					val[i][j] += 1;
				}
				else if (showBoard(i, j) == 1) {
					around(i, j, count);
				}
				else {
					val[i][j] -= 1;
				}
			}
		}
	}
}

// �������� �˻��ϴ� �Լ�
bool line_check(int bx, int by, int cx, int cy, int count) {
	if (count == 2) {
		inclination = (cx - bx) / (cy - by);
		
		if (inclination == 0 || inclination == 1.0 || inclination == -1.0) return true;
		else false;
	}
	else if (count > 2) {
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

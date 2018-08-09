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

boolean isFree(int x, int y) : ���� [x,y]��ǥ�� �ٵϵ��� �ִ��� Ȯ���ϴ� �Լ� (������ true, ������ false)
int showBoard(int x, int y) : [x, y] ��ǥ�� ���� ���� �����ϴ��� �����ִ� �Լ� (1 = �ڽ��� ��, 2 = ����� ��, 3 = ��ŷ)


<-------AI�� �ۼ��Ͻ� ��, ���� �̸��� �Լ� �� ���� ����� �������� �ʽ��ϴ�----->
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

// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:���ڶ� �༮��,Department:KOREATECH" };

// ���� ���������� ������ ���� ��ġ (-1�� �ʱ�ȭ)
int myx[2] = { -1, -1 }, myy[2] = { -1, -1 };

// ������ ���������� ������ ���� ��ġ (-1�� �ʱ�ȭ)
int opx[2] = { -1, -1 }, opy[2] = { -1, -1 };

// (����ġ, (x��ǥ, y��ǥ))�� ��Ÿ���� �ڷ��� valued_point ����
// first: ����ġ, second.first: x ��ǥ, second.second: y ��ǥ
typedef pair<int, pair<int, int>> valued_point;

// ������ ���� ����ġ�� ��ǥ(������)�� �����ϴ� �켱���� ť
priority_queue<valued_point> myQueue;

void checkAround(int px, int py);
int setPriority(string s);
void debugPrint();		// �켱���� ť ����׿�

void myturn(int cnt) {

	int x[2], y[2];

	srand((unsigned)time(NULL));

	if (cnt == 1) {		// ù ���� ��� ������� ����
		x[0] = width / 2;
		y[0] = height / 2;
	}
	else {				// ù ���� ������ ��� ���
		if (opx[1] == -1 && opy[1] == -1) {		// ���� �������� ù ���� ���
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
		else {		// �� ���� ��� ���
			checkAround(myx[0], myy[0]);
			checkAround(myx[1], myy[1]);
			checkAround(opx[0], opy[0]);
			checkAround(opx[1], opy[1]);

			debugPrint();		// �켱���� ť ����׿�

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

	// ����׿�
	char dd[200] = { " " };
	sprintf_s(dd, "--- opx[0]: %d, opy[0]: %d, opx[1]: %d, opy[1]: %d ---\n", opx[0], opy[0], opx[1], opy[1]);
	writeLog(dd);

	//	while (!myQueue.empty())
	//		myQueue.pop();

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);
}

// Ư�� ���� 8 ������ ���ڿ�ȭ�Ͽ� �� ������ �˻�, ���� ���� ��ǥ�� �켱������ �����ϴ� �Լ�
void checkAround(int px, int py) {
	string str = "";
	valued_point pos;		// �˻��� ���� ����ġ(value)�� ��ǥ ������ (x, y)
	unordered_map<string, int> tokens;
	vector<valued_point> tempQueue;		// �� ��ǥ�� ����ġ�� �ӽ� �����ϴ� ť

	int firstIndex = 0, lastIndex = 0;
	int x_begin = -1, y_begin = -1;

	if (px == -1 && py == -1) return;

	// ��/��(0) -> �»�/����(1) -> ��/��(2) -> ����/���(3) ������ �˻�
	for (int incl = 0; incl < 4; incl++) {
		switch (incl) {
		case 0:		// �� -> ��
			x_begin = px;
			y_begin = 0;

			for (int i = 0; i < height; i++)
				str.append(to_string(showBoard(px, i)));
			break;
		case 1:		// �»� -> ����
			if (px > py) {
				x_begin = px - py;
				y_begin = 0;
			}
			else {
				x_begin = 0;
				y_begin = py - px;
			}

			for (int i = 0; i < height - abs(px - py) + 1; i++)
				if (px > py)	// �밢�� ��
					str.append(to_string(showBoard((px - py) + i, i)));
				else			// �밢�� �Ʒ�
					str.append(to_string(showBoard(i, (py - px) + i)));
			break;
		case 2:		// �� -> ��
			x_begin = 0;
			y_begin = py;

			for (int i = 0; i < width; i++)
				str.append(to_string(showBoard(i, py)));
			break;
		case 3:		// ���� -> ���
			if (px + py < height) {		// �밢�� ��
				x_begin = 0;
				y_begin = px + py;

				for (int i = 0; i < (px + py + 1); i++)
					str.append(to_string(showBoard(i, (px + py) - i)));
			}
			else {						// �밢�� �Ʒ�
				x_begin = (px + py) - height;
				y_begin = height - 1;
				for (int i = 0; i < (height * 2 - (px + py)) + 1; i++)
					str.append(to_string(showBoard((px + py) - height + i, height - i)));
			}
			break;
		}

		// ����׿�
		fp = fopen("myLog.txt", "a");
		if (fp != NULL) {
			string tmp = to_string(incl) + string(" : ") + str;
			fprintf(fp, tmp.c_str());
			fprintf(fp, "\n");
		}
		fclose(fp);

		// ���ڿ� ��ūȭ
		while (true) {
			firstIndex = str.find("0", lastIndex);
			lastIndex = str.find("0", firstIndex + 1);

			if (lastIndex == -1) lastIndex = str.size() - 1;
			if (lastIndex - firstIndex > 1) {
				string temp = str.substr(firstIndex, lastIndex - firstIndex + 1);
				//tokens.push_back(temp);
				tokens.emplace(make_pair(temp, firstIndex));
			}

			if (lastIndex == str.size() - 1) break;
		}

		for (auto s : tokens) {
			int value = setPriority(s.first);
			int qx[2] = { -1, -1 }, qy[2] = { -1, -1 };

			for (int i = 0; i < 2; i++) {
				switch (incl) {
				case 0:		// �� -> ��
					qx[i] = x_begin;
					if (i == 0) qy[i] = s.second;
					else qy[i] = s.second + s.first.size() - 1;
					break;
				case 1:		// �»� -> ����
					if (i == 0) {
						qx[i] = x_begin + s.second;
						qy[i] = y_begin + s.second;
					}
					else {
						qx[i] = x_begin + s.second + s.first.size() - 1;
						qy[i] = y_begin + s.second + s.first.size() - 1;
					}
					break;
				case 2:		// �� -> ��
					if (i == 0) qx[i] = s.second;
					else qx[i] = s.second + s.first.size() - 1;
					qy[i] = y_begin;
					break;
				case 3:		// ���� -> ���
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
				writeLog("0 ");
			}
		}

		str.clear();			// ���ڿ� �ʱ�ȭ
	}
	writeLog("\n");

	while (!myQueue.empty()) {
		tempQueue.push_back(myQueue.top());
		myQueue.pop();
	}

	// ����ġ ������ ���� �ӽ� ���� ť�� ��� ���Ҹ� ����(����) �� �켱���� ť�� �̵�
	for (auto a = tempQueue.begin(); a != tempQueue.end(); a++) {
		auto tmp = *a;
		writeLog("1 ");
		if (tempQueue.empty()) break;
		else tempQueue.erase(a);
		writeLog("2 ");
		for (auto b = a; b != tempQueue.end(); b++) {
			writeLog("3 ");
			if ((*b).second.first == tmp.second.first && (*b).second.second == tmp.second.second) {
				writeLog("4 ");
				tmp.first += (*b).first;
				tempQueue.erase(b);
				writeLog("5 ");
			}
		}
		myQueue.push(tmp);
		writeLog("\n");
	}
}

// ���ڿ� ��ū�� �˻��Ͽ� ����ġ�� �ο��ϴ� �Լ�
int setPriority(string s) {
	int value;

	// ����ġ �ο�
	if (s == "010")				value = 20;
	else if (s == "0110")		value = 100;
	else if (s == "01110")		value = 500;
	else if (s == "011110")		value = 2000;
	else if (s == "0111110")	value = 10000;
	else if (s == "020")		value = 10;
	else if (s == "0220")		value = 50;
	else if (s == "02220")		value = 200;
	else if (s == "022220")		value = 1000;
	else if (s == "0222220")	value = 5000;
	else						value = 0;

	return value;
}

// �켱���� ť ����׿�
void debugPrint() {
	vector<valued_point> vp;
	string tmp;

	while (!myQueue.empty()) {
		vp.push_back(myQueue.top());
		myQueue.pop();
	}

	fp = fopen("myLog.txt", "a");
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
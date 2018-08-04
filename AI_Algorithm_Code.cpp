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
int myLog[2][2] = { { -1, -1 }, {-1, -1} };
int count = 0;
int weight[19][19] = {0, };
using namespace std;

int searchTree(int incX, int incY, int x, int y, int i, boolean my = false, int level = 1)
{
		if (incX == 1 && incY == 0)
		{
			if (my == false)
			{
				if (showBoard(x + incX, y + incY) == 1)
				{
					return level * 100;
				}
				else if (showBoard(x + incX, y + incY) == 2 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 100;
					return weight[y + incY][x + incX];
				}
					
			}
			else
			{
				if (showBoard(x + incX, y + incY) == 2)
				{
					return level * 200;
				}
				else if (showBoard(x + incX, y + incY) == 1 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 200;
					return weight[y + incY][x + incX];
				}

			}
		}
		else if (incX == 1 && incY == 1)
		{
			if (my == false)
			{
				if (showBoard(x + incX, y + incY) == 1)
				{
					return level * 100;
				}
				else if (showBoard(x + incX, y + incY) == 2 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 100;
					return weight[y + incY][x + incX];
				}

			}
			else
			{
				if (showBoard(x + incX, y + incY) == 2)
				{
					return level * 200;
				}
				else if (showBoard(x + incX, y + incY) == 1 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 200;
					return weight[y + incY][x + incX];
				}

			}
		}
		else if (incX == 1 && incY == -1)
		{
			if (my == false)
			{
				if (showBoard(x + incX, y + incY) == 1)
				{
					return level * 100;
				}
				else if (showBoard(x + incX, y + incY) == 2 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 100;
					return weight[y + incY][x + incX];
				}

			}
			else
			{
				if (showBoard(x + incX, y + incY) == 2)
				{
					return level * 200;
				}
				else if (showBoard(x + incX, y + incY) == 1 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 200;
					return weight[y + incY][x + incX];
				}

			}
		}
		else if (incX == 0 && incY == 1)
		{
			if (my == false)
			{
				if (showBoard(x + incX, y + incY) == 1)
				{
					return level * 100;
				}
				else if (showBoard(x + incX, y + incY) == 2 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 100;
					return weight[y + incY][x + incX];
				}

			}
			else
			{
				if (showBoard(x + incX, y + incY) == 2)
				{
					return level * 200;
				}
				else if (showBoard(x + incX, y + incY) == 1 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 200;
					return weight[y + incY][x + incX];
				}

			}
		}
		else if (incX == 0 && incY == -1)
		{
			if (my == false)
			{
				if (showBoard(x + incX, y + incY) == 1)
				{
					return level * 100;
				}
				else if (showBoard(x + incX, y + incY) == 2 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 100;
					return weight[y + incY][x + incX];
				}

			}
			else
			{
				if (showBoard(x + incX, y + incY) == 2)
				{
					return level * 200;
				}
				else if (showBoard(x + incX, y + incY) == 1 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 200;
					return weight[y + incY][x + incX];
				}

			}
		}
		else if (incX == -1 && incY == -1)
		{
			if (my == false)
			{
				if (showBoard(x + incX, y + incY) == 1)
				{
					return level * 100;
				}
				else if (showBoard(x + incX, y + incY) == 2 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 100;
					return weight[y + incY][x + incX];
				}

			}
			else
			{
				if (showBoard(x + incX, y + incY) == 2)
				{
					return level * 200;
				}
				else if (showBoard(x + incX, y + incY) == 1 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 200;
					return weight[y + incY][x + incX];
				}

			}
		}
		else if (incX == -1 && incY == 0)
		{
			if (my == false)
			{
				if (showBoard(x + incX, y + incY) == 1)
				{
					return level * 100;
				}
				else if (showBoard(x + incX, y + incY) == 2 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 100;
					return weight[y + incY][x + incX];
				}

			}
			else
			{
				if (showBoard(x + incX, y + incY) == 2)
				{
					return level * 200;
				}
				else if (showBoard(x + incX, y + incY) == 1 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 200;
					return weight[y + incY][x + incX];
				}

			}
		}
		else if (incX == -1 && incY == 1)
		{
			if (my == false)
			{
				if (showBoard(x + incX, y + incY) == 1)
				{
					return level * 100;
				}
				else if (showBoard(x + incX, y + incY) == 2 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 100;
					return weight[y + incY][x + incX];
				}

			}
			else
			{
				if (showBoard(x + incX, y + incY) == 2)
				{
					return level * 200;
				}
				else if (showBoard(x + incX, y + incY) == 1 || showBoard(x + incX, y + incY) == 3)
					return searchTree(incX, incY, x + incX, y + incY, i, my, level++);
				else
				{
					weight[y + incY][x + incX] = level * 200;
					return weight[y + incY][x + incX];
				}

			}
		}
}


void setEnemyWeight(int cnt)
{
	int Weight = 0;
	for (int j = 0; j < cnt; j++)
	{
			weight[enemyLog[j][1]][enemyLog[j][0]] = -1;
			if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1]) == 0)
			{
				weight[enemyLog[j][1]][enemyLog[j][0] + 1] += 10;
			}
			else if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1]) == 2 || showBoard(enemyLog[j][0] + 1, enemyLog[j][1]) == 3)
			{	//showBoard�� 1�� 0���� �ٲ����. showBoard������ x,y���̹Ƿ�..
				weight[enemyLog[j][1]][enemyLog[j][0] + 1] = -1;
				Weight = searchTree(1, 0, enemyLog[j][0] + 1, enemyLog[j][1], j);
				if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1]) == 0)
					weight[enemyLog[j][1]][enemyLog[j][0] - 1] += Weight;
			}
			else
				weight[enemyLog[j][1]][enemyLog[j][0] + 1] = -1;

			if (showBoard(enemyLog[j][0], enemyLog[j][1] + 1) == 0)
			{
				weight[enemyLog[j][1] + 1][enemyLog[j][0]] += 10;
			}
			else if (showBoard(enemyLog[j][0], enemyLog[j][1] + 1) == 2 || showBoard(enemyLog[j][0], enemyLog[j][1] + 1) == 3)
			{
				weight[enemyLog[j][1] + 1][enemyLog[j][0]] = -1;
				Weight = searchTree(0, 1, enemyLog[j][0], enemyLog[j][1] + 1, j);
				if (showBoard(enemyLog[j][0], enemyLog[j][1] - 1) == 0)
					weight[enemyLog[j][1] - 1][enemyLog[j][0]] += Weight;
			}
			else
				weight[enemyLog[j][1] + 1][enemyLog[j][0]] = -1;

			if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1] + 1) == 0)
			{
				weight[enemyLog[j][1] + 1][enemyLog[j][0] + 1] += 10;
			}
			else if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1] + 1) == 2 || showBoard(enemyLog[j][0] + 1, enemyLog[j][1] + 1) == 3)
			{
				weight[enemyLog[j][1] + 1][enemyLog[j][0] + 1] = -1;
				Weight = searchTree(1, 1, enemyLog[j][0] + 1, enemyLog[j][1] + 1, j);
				if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1] - 1) == 0)
					weight[enemyLog[j][1] - 1][enemyLog[j][0] - 1] += Weight;
			}
			else
				weight[enemyLog[j][1] + 1][enemyLog[j][0] + 1] = -1;

			if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1] - 1) == 0)
			{
				weight[enemyLog[j][1] - 1][enemyLog[j][0] + 1] += 10;
			}
			else if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1] - 1) == 2 || showBoard(enemyLog[j][0] + 1, enemyLog[j][1] - 1) == 3)
			{
				weight[enemyLog[j][1] - 1][enemyLog[j][0] + 1] = -1;
				Weight = searchTree(1, -1, enemyLog[j][0] + 1, enemyLog[j][1] - 1, j);
				if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1] + 1) == 0)
					weight[enemyLog[j][1] + 1][enemyLog[j][0] - 1] += Weight;
			}
			else
				weight[enemyLog[j][1] - 1][enemyLog[j][0] + 1] = -1;

			if (showBoard(enemyLog[j][0], enemyLog[j][1] - 1) == 0)
			{
				weight[enemyLog[j][1] - 1][enemyLog[j][0]] += 10;
			} 
			else if (showBoard(enemyLog[j][0], enemyLog[j][1] - 1) == 2 || showBoard(enemyLog[j][0], enemyLog[j][1] - 1) == 3)
			{
				weight[enemyLog[j][1] - 1][enemyLog[j][0]] = -1;
				Weight = searchTree(0, -1, enemyLog[j][0], enemyLog[j][1] - 1, j);
				if (showBoard(enemyLog[j][0], enemyLog[j][1] + 1) == 0)
					weight[enemyLog[j][1] + 1][enemyLog[j][0]] += Weight;
			}
			else
				weight[enemyLog[j][1] - 1][enemyLog[j][0]] = -1;

			if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1] - 1) == 0)
			{
				weight[enemyLog[j][1] - 1][enemyLog[j][0] - 1] += 10;
			}
			else if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1] - 1) == 2 || showBoard(enemyLog[j][0] - 1, enemyLog[j][1] - 1) == 3)
			{
				weight[enemyLog[j][1] - 1][enemyLog[j][0] - 1] = -1;
				Weight = searchTree(-1, -1, enemyLog[j][0] - 1, enemyLog[j][1] - 1, j);
				if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1] + 1) == 0)
					weight[enemyLog[j][1] + 1][enemyLog[j][0] + 1] += Weight;
			}
			else
				weight[enemyLog[j][1] - 1][enemyLog[j][0] - 1] = -1;

			if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1]) == 0)
			{
				weight[enemyLog[j][1]][enemyLog[j][0] - 1] += 10;
			}
			else if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1]) == 2 || showBoard(enemyLog[j][0] - 1, enemyLog[j][1]) == 3)
			{
				weight[enemyLog[j][1]][enemyLog[j][0] -1] = -1;
				Weight = searchTree(-1, 0, enemyLog[j][0] - 1, enemyLog[j][1], j);
				if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1]) == 0)
					weight[enemyLog[j][1]][enemyLog[j][0] + 1] += Weight;
			}
			else
				weight[enemyLog[j][1]][enemyLog[j][0] - 1] = -1;

			if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1] + 1) == 0)
			{
				weight[enemyLog[j][1] + 1][enemyLog[j][0] - 1] += 10;
			}
			else if (showBoard(enemyLog[j][0] - 1, enemyLog[j][1] + 1) == 2 || showBoard(enemyLog[j][0] - 1, enemyLog[j][1] + 1) == 3)
			{
				weight[enemyLog[j][1] + 1][enemyLog[j][0] - 1] = -1;
				Weight = searchTree(-1, 1, enemyLog[j][0] - 1, enemyLog[j][1] + 1, j);
				if (showBoard(enemyLog[j][0] + 1, enemyLog[j][1] - 1) == 0)
					weight[enemyLog[j][1] - 1][enemyLog[j][0] + 1] += Weight;
			}
			else
				weight[enemyLog[j][1] + 1][enemyLog[j][0] - 1] = -1;

	}
}
void setMyWeight(int cnt)
{
		int Weight = 0;
	for (int j = 0; j < cnt; j++)
	{
		weight[myLog[j][1]][myLog[j][0]] = -1;
		if (showBoard(myLog[j][0] + 1, myLog[j][1]) == 0)
			{
			weight[myLog[j][1]][myLog[j][0] + 1] += 10;
			}
		else if (showBoard(myLog[j][0] + 1, myLog[j][1]) == 1 || showBoard(myLog[j][0] + 1, myLog[j][1]) == 3)
			{	//showBoard�� 1�� 0���� �ٲ����. showBoard������ x,y���̹Ƿ�..
			weight[myLog[j][1]][myLog[j][0] + 1] = -1;
			Weight = searchTree(1, 0, myLog[j][0] + 1, myLog[j][1], j, true);
			if (showBoard(myLog[j][0] - 1, myLog[j][1]) == 0)
				weight[myLog[j][1]][myLog[j][0] - 1] += Weight;
			}
			else
				weight[myLog[j][1]][myLog[j][0] + 1] = -1;

		if (showBoard(myLog[j][0], myLog[j][1] + 1) == 0)
			{
			weight[myLog[j][1] + 1][myLog[j][0]] += 10;
			}
		else if (showBoard(myLog[j][0], myLog[j][1] + 1) == 1 || showBoard(myLog[j][0], myLog[j][1] + 1) == 3)
			{
			weight[myLog[j][1] + 1][myLog[j][0]] = -1;
			Weight = searchTree(0, 1, myLog[j][0], myLog[j][1] + 1, j, true);
			if (showBoard(myLog[j][0], myLog[j][1] - 1) == 0)
				weight[myLog[j][1] - 1][myLog[j][0]] += Weight;
			}
			else
				weight[myLog[j][1] + 1][myLog[j][0]] = -1;

		if (showBoard(myLog[j][0] + 1, myLog[j][1] + 1) == 0)
			{
			weight[myLog[j][1] + 1][myLog[j][0] + 1] += 10;
			}
		else if (showBoard(myLog[j][0] + 1, myLog[j][1] + 1) == 1 || showBoard(myLog[j][0] + 1, myLog[j][1] + 1) == 3)
			{
			weight[myLog[j][1] + 1][myLog[j][0] + 1] = -1;
			Weight = searchTree(1, 1, myLog[j][0] + 1, myLog[j][1] + 1, j, true);
			if (showBoard(myLog[j][0] - 1, myLog[j][1] - 1) == 0)
				weight[myLog[j][1] - 1][myLog[j][0] - 1] += Weight;
			}
			else
				weight[myLog[j][1] + 1][myLog[j][0] + 1] = -1;

		if (showBoard(myLog[j][0] + 1, myLog[j][1] - 1) == 0)
			{
			weight[myLog[j][1] - 1][myLog[j][0] + 1] += 10;
			}
		else if (showBoard(myLog[j][0] + 1, myLog[j][1] - 1) == 1 || showBoard(myLog[j][0] + 1, myLog[j][1] - 1) == 3)
			{
			weight[myLog[j][1] - 1][myLog[j][0] + 1] = -1;
			Weight = searchTree(1, -1, myLog[j][0] + 1, myLog[j][1] - 1, j, true);
			if (showBoard(myLog[j][0] - 1, myLog[j][1] + 1) == 0)
				weight[myLog[j][1] + 1][myLog[j][0] - 1] += Weight;
			}
			else
				weight[myLog[j][1] - 1][myLog[j][0] + 1] = -1;

		if (showBoard(myLog[j][0], myLog[j][1] - 1) == 0)
			{
			weight[myLog[j][1] - 1][myLog[j][0]] += 10;
			} 
		else if (showBoard(myLog[j][0], myLog[j][1] - 1) == 1 || showBoard(myLog[j][0], myLog[j][1] - 1) == 3)
			{
			weight[myLog[j][1] - 1][myLog[j][0]] = -1;
			Weight = searchTree(0, -1, myLog[j][0], myLog[j][1] - 1, j, true);
			if (showBoard(myLog[j][0], myLog[j][1] + 1) == 0)
				weight[myLog[j][1] + 1][myLog[j][0]] += Weight;
			}
			else
				weight[myLog[j][1] - 1][myLog[j][0]] = -1;

		if (showBoard(myLog[j][0] - 1, myLog[j][1] - 1) == 0)
			{
			weight[myLog[j][1] - 1][myLog[j][0] - 1] += 10;
			}
		else if (showBoard(myLog[j][0] - 1, myLog[j][1] - 1) == 1 || showBoard(myLog[j][0] - 1, myLog[j][1] - 1) == 3)
			{
			weight[myLog[j][1] - 1][myLog[j][0] - 1] = -1;
			Weight = searchTree(-1, -1, myLog[j][0] - 1, myLog[j][1] - 1, j, true);
			if (showBoard(myLog[j][0] + 1, myLog[j][1] + 1) == 0)
				weight[myLog[j][1] + 1][myLog[j][0] + 1] += Weight;
			}
			else
				weight[myLog[j][1] - 1][myLog[j][0] - 1] = -1;

		if (showBoard(myLog[j][0] - 1, myLog[j][1]) == 0)
			{
			weight[myLog[j][1]][myLog[j][0] - 1] += 10;
			}
		else if (showBoard(myLog[j][0] - 1, myLog[j][1]) == 1 || showBoard(myLog[j][0] - 1, myLog[j][1]) == 3)
			{
			weight[myLog[j][1]][myLog[j][0] - 1] = -1;
			Weight = searchTree(-1, 0, myLog[j][0] - 1, myLog[j][1], j, true);
			if (showBoard(myLog[j][0] + 1, myLog[j][1]) == 0)
				weight[myLog[j][1]][myLog[j][0] + 1] += Weight;
			}
			else
				weight[myLog[j][1]][myLog[j][0] - 1] = -1;

		if (showBoard(myLog[j][0] - 1, myLog[j][1] + 1) == 0)
			{
			weight[myLog[j][1] + 1][myLog[j][0] - 1] += 10;
			}
		else if (showBoard(myLog[j][0] - 1, myLog[j][1] + 1) == 1 || showBoard(myLog[j][0] - 1, myLog[j][1] + 1) == 3)
			{
			weight[myLog[j][1] + 1][myLog[j][0] - 1] = -1;
			Weight = searchTree(-1, 1, myLog[j][0] - 1, myLog[j][1] + 1, j, true);
			if (showBoard(myLog[j][0] + 1, myLog[j][1] - 1) == 0)
				weight[myLog[j][1] - 1][myLog[j][0] + 1] += Weight;
			}
			else
				weight[myLog[j][1] + 1][myLog[j][0] - 1] = -1;

	}
}

void myturn(int cnt) {

	int maxVal = 1;
	int x[2], y[2];
	FILE *file_pointer;
	file_pointer = fopen("C:\\Users\\�ִ���\\Desktop\\�Ｚ����DS�ι�����SW�˰����ȸ\\01_SamsungGo_AI_Code_����_����\\SamsungGo_AI_Code_C_C++\\Releastestlog.txt", "w");

	srand((unsigned)time(NULL));
	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.
	//���� ���϶�,
	if (cnt == 1)
	{
			do {
				x[0] = rand() % width;
				y[0] = rand() % height;
				if (terminateAI) return;
			} while (!isFree(x[0], y[0]));

		myLog[0][0] = x[0];
		myLog[0][1] = y[0]; 
	}
	else
	{
		if (enemyLog[1][0] == -1  && myLog[1][0] == -1)
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
				fprintf(file_pointer, "%d ", weight[z][q]);
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
					if (maxVal < weight[j][k])
					{
						maxVal = weight[j][k];
						y[i] = j;
						x[i] = k;
					}
				}

			}

			/*
			if (maxVal == 0)
			{
				int z = 9;
				do {
					x[0] = z;
					y[0] = z + 1;
					z++;
					if (terminateAI) return;
				} while (!isFree(x[0], y[0]));
			}
			*/

			weight[y[i]][x[i]] = -1;
			myLog[i][0] = x[i];
			myLog[i][1] = y[i];

			if (terminateAI) return;
		}
	}
	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);
}


#include<bits/stdc++.h> 
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include <iomanip>
using namespace std;

void init(void);
void print(void);
void build(void);
void falling(void);
void click(int x, int y);
int check(int x, int y);
int checking(int x, int y);
int getRandom(int left, int right);
int find(int x, int y, int num, int* bag[]);

int hp = 5;// ���� 5 ����
int score;// �ܳɼ�
int Array[7][7];// 5 * 5 ���� 



int main() {
	init();
	while (hp) {
		print();
		cout << "��������ѡ��Ҫ����ķ�������꣨������ֵ���ֱ���Ϊ�кź��кţ�";
		int x, y;
		//int r = 0;
		//r = scanf("%d %d", &x, &y);
		cin >> x >> y;
		while (!(x >= 1 && y >= 1 && x <= 5 && y <= 5)) {
			cout << "�Ƿ���ʽ!(x �� y ��Ϊ [1,5] ֮�������)" << endl;
			while (getchar() != '\n');
			cin >> x >> y;
			//r = scanf("%d %d", &x, &y);
		}
		click(x, y);
	}
	cout << '\t' << "   GameOver!" << '\n';
}

// ģ�������� 
void click(int x, int y) 
{
	hp--;// ÿ���һ������ֵ��һ 
	Array[x][y] += 1;// ���ʱֵ��һ 
	print();
	Sleep(50);
	int mixNum = checking(x, y);
	if (mixNum < 2) {
	}
	else if (mixNum == 2) {
		cout << "�ã�" << '\n';
	}
	else if (mixNum == 3) {
		cout << "������" << '\n';
	}
	else {
		cout << "�޵��ˣ�" << '\n';
	}
	if (mixNum >= 3) system("pause");
}

// ������������ 
int checking(int x, int y) {
	int mixNum = check(x, y);
	if (mixNum) {
		int num = 0;
		num = check(1, 1);
		mixNum += num;
		while (num) {
			num = 0;
			num = check(1, 1);
			mixNum += num;
		}
	}

	return mixNum;
}

// �� (x, y) ��ʼ�������� 
int check(int x, int y) {
	int mixNum = 0;
	int i = x;
	for (; i <= 5; i++) {
		int j = y;
		for (; j <= 5; j++) {
			int* bag[26];// ʹ���±� 1 ~ 25 �洢�� Array[i][j] ��ֵ��������ڵĸ�ĵ�ַ 
			int num = find(i, j, 0, bag);// num Ϊ�� Array[i][j] ��ֵ��������ڵĸ�ĸ���
			if (num >= 2) {// �ϳ�
				if (hp < 5) hp++;// ��Ѫ������ 5���ϳ�ʱ����������ֵ 
				mixNum++;// ��¼�ϳɴ��� 
				int k = 1;
				for (; k <= num; k++) {// ȫ������ 
					*bag[k] = 0;
				}
				score += Array[i][j] * (num + 1);// ���³ɼ�
				// ���µ���
				int temp = Array[i][j] + 1;
				Array[i][j] = 0;// �Ӿ�Ч�� 
				print();
				Sleep(150);
				Array[i][j] = temp;
				print();
				Sleep(350);

				falling();// ��׹�����

				j--;
			}
		}
	}
	return mixNum;
}

int find(int x, int y, int num, int* bag[]) 
{
	int X[4] = { -1, 0, 1, 0 }, Y[4] = { 0, 1, 0, -1 };// �� �� �� �� 
	static int state[7][7];

	if (num == 0) {// ��ʼ�� 
		memset(state, 0, sizeof(state));
		state[x][y] = 1;
	}

	
	for (int i = 0; i < 4; i++) {
		if (Array[x + X[i]][y + Y[i]] != -1 &&
			state[x + X[i]][y + Y[i]] == 0 &&
			Array[x][y] == Array[x + X[i]][y + Y[i]]) {
			state[x + X[i]][y + Y[i]] = 1;
			num++;
			bag[num] = &Array[x + X[i]][y + Y[i]];
			num = find(x + X[i], y + Y[i], num, bag);
		}
	}

	return num;
}

void falling(void) {
	
	for (int row = 1; row <= 5; row++) {
		bool isFall = false;
		build();// �ڶ��˽�����������ո� 
		int column = 1;
		for (; column <= 5; column++) {
			if (Array[row][column] != 0) {// ��λ���пյĸ� 
				continue;// ��������һ�� 
			}

			// ��ǰλ�����Ϸ��ĸ���������׹һ��  
			int in = row;
			while (Array[in - 1][column] != -1 && Array[in - 1][column] != 0) {
				Array[in][column] = Array[in - 1][column];
				Array[in - 1][column] = 0;
				in--;
				isFall = true;
			}
		}
		if (isFall) {// �����Ϸ��ĸ����Ƿ���׹�� 
			build();// �ڶ��˽�����������ո� 
			// ��׹Ч�� 
			print();
			Sleep(50);
		}
	}
}

// �ڶ������� 1 ~ 6 ֮��������
void build(void) {
	int column = 1;
	for (; column <= 5; column++) {
		if (Array[1][column] == 0) {
			Array[1][column] = getRandom(1, 6);
		}
	}
	print();
	Sleep(50);
}

// ���� left ~ right ��Χ�ڵ������
int getRandom(int left, int right) {
	int random = rand() % (right - left + 1) + left;
	return random;
}

// ��ʼ������ 
void init() 
{
	
	for (int i = 0; i < 7; i++) 
	{// ��ʼ������߽� 
		Array[0][i] = -1;
		Array[6][i] = -1;
		Array[i][0] = -1;
		Array[i][6] = -1;
	}

	srand((unsigned)time(NULL));// ��ʼ����������� 
	int in = 1;
	for (; in <= 5; in++) {// ��ʼ������ 
		int j = 1;
		for (; j <= 5; j++) 
		{
			Array[in][j] = getRandom(1, 5);
			int* bag[26] = { 0 };
			while (find(in, j, 0, bag) >= 2) 
			{
				Array[in][j] = getRandom(1, 5);
			}
		}
	}
}

// ��ӡ����
void print() 
{
	system("cls");
	printf(" HP: %d\t\t   score: %d\n", hp, score);
	printf(" ----- ----- ----- ----- -----\n");
	int i = 1;
	for (; i < 6; i++) {
		putchar('|');
		int j = 1;
		for (; j < 6; j++) {
			if (Array[i][j] != 0)
				cout << setw(5) << Array[i][j] << "|";
			else
				cout << "     |";
		}
		cout << endl;
		cout << " ----- ----- ----- ----- -----" << endl;
	}
}
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

int hp = 5;// 开局 5 条命
int score;// 总成绩
int Array[7][7];// 5 * 5 矩阵 



int main() {
	init();
	while (hp) {
		print();
		cout << "请输入你选择要点击的方格的坐标（键入两值，分别作为行号和列号）";
		int x, y;
		//int r = 0;
		//r = scanf("%d %d", &x, &y);
		cin >> x >> y;
		while (!(x >= 1 && y >= 1 && x <= 5 && y <= 5)) {
			cout << "非法格式!(x 和 y 都为 [1,5] 之间的整数)" << endl;
			while (getchar() != '\n');
			cin >> x >> y;
			//r = scanf("%d %d", &x, &y);
		}
		click(x, y);
	}
	cout << '\t' << "   GameOver!" << '\n';
}

// 模拟点击操作 
void click(int x, int y) 
{
	hp--;// 每点击一次生命值减一 
	Array[x][y] += 1;// 点击时值加一 
	print();
	Sleep(50);
	int mixNum = checking(x, y);
	if (mixNum < 2) {
	}
	else if (mixNum == 2) {
		cout << "好！" << '\n';
	}
	else if (mixNum == 3) {
		cout << "完美！" << '\n';
	}
	else {
		cout << "无敌了！" << '\n';
	}
	if (mixNum >= 3) system("pause");
}

// 持续遍历搜索 
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

// 从 (x, y) 开始遍历搜索 
int check(int x, int y) {
	int mixNum = 0;
	int i = x;
	for (; i <= 5; i++) {
		int j = y;
		for (; j <= 5; j++) {
			int* bag[26];// 使用下标 1 ~ 25 存储与 Array[i][j] 的值相等且相邻的格的地址 
			int num = find(i, j, 0, bag);// num 为与 Array[i][j] 的值相等且相邻的格的个数
			if (num >= 2) {// 合成
				if (hp < 5) hp++;// 若血量少于 5，合成时会增加生命值 
				mixNum++;// 记录合成次数 
				int k = 1;
				for (; k <= num; k++) {// 全部置零 
					*bag[k] = 0;
				}
				score += Array[i][j] * (num + 1);// 更新成绩
				// 更新点数
				int temp = Array[i][j] + 1;
				Array[i][j] = 0;// 视觉效果 
				print();
				Sleep(150);
				Array[i][j] = temp;
				print();
				Sleep(350);

				falling();// 下坠并填格

				j--;
			}
		}
	}
	return mixNum;
}

int find(int x, int y, int num, int* bag[]) 
{
	int X[4] = { -1, 0, 1, 0 }, Y[4] = { 0, 1, 0, -1 };// 上 右 下 左 
	static int state[7][7];

	if (num == 0) {// 初始化 
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
		build();// 在顶端降落随机数填充空格 
		int column = 1;
		for (; column <= 5; column++) {
			if (Array[row][column] != 0) {// 定位到中空的格 
				continue;// 检查该行下一列 
			}

			// 当前位置正上方的格子整体下坠一格  
			int in = row;
			while (Array[in - 1][column] != -1 && Array[in - 1][column] != 0) {
				Array[in][column] = Array[in - 1][column];
				Array[in - 1][column] = 0;
				in--;
				isFall = true;
			}
		}
		if (isFall) {// 该行上方的格子是否下坠过 
			build();// 在顶端降落随机数填充空格 
			// 下坠效果 
			print();
			Sleep(50);
		}
	}
}

// 在顶部生成 1 ~ 6 之间的随机数
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

// 生成 left ~ right 范围内的随机数
int getRandom(int left, int right) {
	int random = rand() % (right - left + 1) + left;
	return random;
}

// 初始化操作 
void init() 
{
	
	for (int i = 0; i < 7; i++) 
	{// 初始化矩阵边界 
		Array[0][i] = -1;
		Array[6][i] = -1;
		Array[i][0] = -1;
		Array[i][6] = -1;
	}

	srand((unsigned)time(NULL));// 初始化随机数种子 
	int in = 1;
	for (; in <= 5; in++) {// 初始化矩阵 
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

// 打印矩阵
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
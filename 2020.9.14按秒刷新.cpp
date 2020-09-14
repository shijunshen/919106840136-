#include<iostream>
#include<stdio.h>
#include<time.h>
#include<string>
#include<stdlib.h>
#include <conio.h>              //getch()的头文件
#include<cstring>
#include<ctime>
#include <fstream>
#define maxn 100001
using namespace std;
ofstream outFile;
ifstream inFile;

int ttemp, tttemp = 0, ttttemp,NUM,p,illPigHome,gailv=0;
long timeBegin, timeFirst;
int order, q = 0, A, B, C, tempp = 0, SS = 0, pricetemp, nodead, kk=1;
int QQQ = 0;
float x;
int last1 = 0, last2 = 0, s1 = 0, s2 = 0, s21 = 0, s22 = 0;
time_t timep;


int getTime() {
	return clock() / CLOCKS_PER_SEC;
}

int sellTime[maxn][4];

struct A {
	bool flag;
	int num;
}pigHome[100][12];

struct bought {
	int num1;
	int num2;
	int num3;
}bought[maxn];

struct Node {
	int variety;
	int home;
	long time;
	float kg;
	int Number;
	int status;
	struct Node* next;
};

struct Node* creatList() {
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next = NULL;
	return headNode;
}

struct Node* creatNode(int home, int variety, float kg, int time, int Number) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->home = home;
	newNode->next = NULL;
	newNode->variety = variety;
	newNode->kg = kg;
	newNode->Number = Number;
	newNode->time = q;
	newNode->status = 0;
	return newNode;
}

struct Node* header = creatList();
struct Node* sellheader = creatList();
struct Node* illPigs = creatList();

void sortInsertNode(struct Node* headNode, int home, int variety, float kg, long time, int Number) {
	struct Node* newNode = creatNode(home, variety, kg, time, Number);
	struct Node* postNode = headNode->next;
	struct Node* postNodeFront = headNode;
	if (postNode == NULL) {
		postNodeFront->next = newNode;
		newNode->next = NULL;
		return;
	}
	else {
		while ((postNode->home) <= home) {
			postNode = postNode->next;
			postNodeFront = postNodeFront->next;
			if (postNode == NULL) {
				postNodeFront->next = newNode;
				newNode->next = NULL;
				return;
			}
		}
		postNodeFront->next = newNode;
		newNode->next = postNode;
	}
}

void insert(struct Node* headNode, int home, int variety, float kg, long time, int Number) {
	struct Node* newNode = creatNode(home, variety, kg, time, Number);
	struct Node* pmove = headNode->next;
	struct Node* pmoveFront = headNode;
	while (pmove != NULL) {
		pmove = pmove->next;
		pmoveFront = pmoveFront->next;
	}
	pmoveFront->next = newNode;
	newNode->next = NULL;
}

void deleteNode(struct Node* headNode, int home, int variety, float kg) {
	struct Node* postNode = headNode->next;
	struct Node* postNodeFront = headNode;
	if (postNode == NULL) {
		cout << "列表为空";
	}
	else {
		while (postNode->home != home || postNode->variety != variety || postNode->kg != kg) {
			postNode = postNode->next;
			postNodeFront = postNodeFront->next;
			if (postNode == NULL) {
				cout << "没有找到相关信息，无法删除";
				return;
			}
		}
		postNodeFront->next = postNode->next;
		free(postNode);
	}
}

void deleteList(struct Node* headNode) {
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		headNode->next = pmove->next;
		free(pmove);
		pmove = headNode->next;
	}
}

void printNode(struct Node* headNode) {
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		cout << "该猪所在猪圈编号为：" << pmove->home << " " << "该猪种类为：" << pmove->variety << " " << "该猪的当前体重为:" << pmove->kg << " " << "该猪的编号为" << pmove->Number << " " << "时间为：" << pmove->time << endl;
		pmove = pmove->next;
	}
}

void printNodeOrder(struct Node* headNode, int home) {
	struct Node* pmove = headNode->next;
	int num = 0, q = 0, q2 = 0, q3 = 0;
	while (pmove != NULL) {
		if (pmove->home == home) {
			num++;
			if (pmove->variety == 1)q = 1;
			else if (pmove->variety == 2)q2++;
			else if (pmove->variety == 3)q3++;
		}
		pmove = pmove->next;
	}
	if (q)cout << endl << "编号为" << home << "的猪圈共有" << num << "只猪，全为黑猪" << endl;
	else {
		cout << endl << "编号为" << home << "的猪圈共有" << num << "只猪，其中有" << q2 << "只小花猪，有" << q3 << "只大花白猪" << endl;
	}
}

void printPig(struct Node* pig) {
	cout << "该猪品种为：" ;
	if (pig->variety == 1)cout << "黑猪";
	else if (pig->variety == 2)cout << "小花猪";
	else if (pig->variety == 3)cout << "大花白猪";
	cout << endl;
	cout << "该猪当前体重为：" << pig->kg << endl;
}

void store(struct Node* headNode, int A, int B, int C, long time, int p) {
	while (A) {
		for (int i = 0; i < p; i++) {
			float temp = float(rand() % 30 + 20);
			for (int j = 1; j < 11; j++) {
				if (pigHome[i][j].num == 0) {
					sortInsertNode(headNode, i, 1, temp, time, j);
					pigHome[i][0].num++;
					pigHome[i][j].num = 1;
					A--;
					break;
				}
			}
			if (!A)break;
		}
	}
	int TT = B + C;
	int j1 = 0, k1 = 0;
	while (TT) {
		int i1 = p;
		for (; j1 < B && i1 < 100; i1++) {
			float temp = float(rand() % 30 + 20);
			for (int j = 1; j < 11; j++) {
				if (pigHome[i1][j].num == 0) {
					sortInsertNode(headNode, i1, 2, temp, time, j);
					pigHome[i1][0].num++;
					pigHome[i1][j].num = 2;
					TT--;
					j1++;
					break;
				}
			}
		}
		if (j1 < B)continue;
		for (; k1 < C && i1 < 100; i1++) {
			float temp = float(rand() % 30 + 20);
			for (int j = 1; j < 11; j++) {
				if (pigHome[i1][j].num == 0) {
					sortInsertNode(headNode, i1, 3, temp, time, j);
					pigHome[i1][0].num++;
					pigHome[i1][j].num = 3;
					k1++;
					TT--;
					break;
				}
			}
		}
	}
}

void grow(struct Node* headNode, int timeBetween) {
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		for (int i = 0; i < timeBetween; i++) {
			float temp = (rand() % 12) * 1.0 / 10;
			pmove->kg += temp;
		}
		pmove = pmove->next;
	}
}

void findPig(struct Node* headNode, int a, int b) {
	struct Node* pmove = headNode->next;
	int flag = 0;
	while (pmove != NULL && pmove->home <= a) {
		if (pmove->home == a && pmove->Number == b) {
			flag = 1; break;
		}
		pmove = pmove->next;
	}
	if (!flag)cout << "该猪圈没有该编号的猪" << endl;
	else printPig(pmove);
}

void sell(struct Node* headNode, struct Node* sellheader, long nowTime) {
	struct Node* pmove = headNode->next;
	struct Node* pmoveFront = headNode;
	while (pmove != NULL) {
		if (pmove->kg > 40 || (nowTime - pmove->time) > 365) {
			sortInsertNode(sellheader, pmove->home, pmove->variety, pmove->kg, pmove->time, pmove->Number);
			pigHome[pmove->home][pmove->Number].num = 0;
			pigHome[pmove->home][0].num--;
			pmoveFront->next = pmove->next;
			struct Node* freetemp = pmove;
			pmove = pmove->next;
			free(freetemp);
		}
		else {
			pmove = pmove->next;
			pmoveFront = pmoveFront->next;
		}
	}
}

float price(struct Node* sellheader) {
	struct Node* pmove = sellheader->next;
	float money = 0;
	while (pmove != NULL) {
		if (pmove->variety == 1) {
			money += pmove->kg * 15;
		}
		else if (pmove->variety == 2) {
			money += pmove->kg * 7;
		}
		else if (pmove->variety == 3) {
			money += pmove->kg * 6;
		}
		pmove = pmove->next;
	}
	return money;
}

int sortheavy(struct Node* headNode, int variety, int a, int b) {
	int num = 0;
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		if (pmove->variety == variety && pmove->kg > a && pmove->kg <= b)num++;
		pmove = pmove->next;
	}
	return num;
}

int sortday(struct Node* headNode, int variety, int a, int b, int timeBegin) {
	int num = 0;
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		if (pmove->variety == variety && timeBegin - pmove->time >= a && timeBegin - pmove->time < b)num++;
		pmove = pmove->next;
	}
	return num;
}

int mark(struct Node* sellhead, int variety) {
	struct Node* pmove = sellhead->next;
	int num = 0;
	while (pmove != NULL) {
		if (pmove->variety == variety) {
			num++;
		}
		pmove = pmove->next;
	}
	return num;
}

void saveList(struct Node* headNode) {
	outFile.open("猪圈信息.txt");
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		outFile << pmove->home << " " << pmove->variety << " " << pmove->kg << " " << pmove->time << " " << pmove->Number << endl;
		pmove = pmove->next;
	}
	outFile << 0 << " " << 0;
	outFile.close();
}

void loadList(struct Node* headNode) {
	inFile.open("猪圈信息.txt");
	int home, variety, Number;
	float kg;
	long time;
	while (inFile >> home >> variety) {
		if (variety == 0)break;
		inFile >> kg >> time >> Number;
		insert(headNode, home, variety, kg, time, Number);
	}
	inFile.close();
}

int illPig(struct Node* headNode,int Num) {
	struct Node* pmove = headNode;
	for (int i = 0; i < Num; i++) {
		pmove = pmove->next;
	}
	pmove->status = 1;
	return pmove->home;
}

void randPig(struct Node* headNode) {
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		if (pmove->status == 0) {
			int temp2 = rand() % 100 + 1;
					if (temp2 <= gailv)pmove->status = 1;				
		}
		pmove = pmove->next;
	}	
}

void separatePig(struct Node* headNode, struct Node* liipigs) {
	struct Node* pmove = headNode->next;
	struct Node* pmoveFront = headNode;
	while (pmove != NULL) {
		if (pmove->status != 0) {
			sortInsertNode(illPigs, pmove->home, pmove->variety, pmove->kg, pmove->time, pmove->Number);
			pigHome[pmove->home][pmove->Number].num = 0;
			pigHome[pmove->home][0].num--;
			struct Node* tempNode = pmove;
			pmove = pmove->next;
			free(tempNode);
			pmoveFront->next = pmove;
		}
		else {
			pmove = pmove->next;
			pmoveFront=pmoveFront->next;
		}
	}
}













int updata() {
	  
	randPig(header);
	separatePig(header,illPigs);
	int gameover = 1;
	long start = clock();
	while (clock() - start <= 1000);
	grow(header, 1);
	if (q)cout << endl;
	q++;
	if (q % 5 == 0) {
		last1 = 0; last2 = 0; s1 = 0; s2 = 0; s21 = 0; s22 = 0;
		for (int i = 0; i < 100; i++) {
			if (pigHome[i][0].flag == 0) {
				s1 += pigHome[i][0].num;
			}
			else {
				for (int PP = 1; PP < 12; PP++) {
					if (pigHome[i][PP].num == 2)s21++;
					else if (pigHome[i][PP].num == 3)s22++;
				}
			}
		}
		s2 = s21 + s22;
		deleteList(sellheader);
		sell(header, sellheader, q);
		pricetemp = price(sellheader);
		sellTime[kk][0] = pricetemp;
		sellTime[kk][1] = mark(sellheader, 1);
		sellTime[kk][2] = mark(sellheader, 2);
		sellTime[kk][3] = mark(sellheader, 3);
		last1 = 10 * p - s1;
		last2 = 10 * (100 - p) - s2;				//last1还能容纳的黑猪量，last2还能容纳的花猪量			 
	again1:
		cout << endl << "请输入加入各猪的数量（黑猪还能容纳" << last1 << "只，花猪还能容纳" << last2 << "只）" << endl;
		cout << "黑猪的数量为：";
		cin >> A;
		cout << "小花猪的数量为：";
		cin >> B;
		cout << "大花白猪的数量为：";
		cin >> C;
		if (A == 0 && B == 0 && C == 0) {
			cout << "\n至少加入一头任意品种的猪，请重新输入:\n";
			goto again1;
		}
		else if (A > last1 || (B + C) > last2) {
			cout << "\n猪圈超载，请根据剩余提示重新输入:\n";
			goto again1;
		}
		bought[kk].num1 = A;
		bought[kk].num2 = B;
		bought[kk].num3 = C;
		kk++;
		store(header, A, B, C, q, p);
		printNode(header);                                             //购进一批猪
		
	}
	return gameover;
}
		
int Order() {

	cout << "-----------------------------------------------------" << endl;
	cout << "                      输入指令                       " << endl;
	cout << "                      停止（0）                      " << endl;
	cout << "           查询当前某一猪圈的猪的数量和种类（1）     " << endl;
	cout << "                计算本次出圈猪的总价（2）            " << endl;
	cout << "             查询某圈某一编号的猪的状态（3）         " << endl;
	cout << "               查询当前猪场的整体情况（4）           " << endl;
	cout << "           查询近五年的销售记录和购入记录（5）       " << endl;
	cout << "-----------------------------------------------------" << endl;
	cin >> order;
	if (order == 0)return 0;
	else if (order == 1) {
		int checkHome;
		cout << endl << "输入你要查询的猪圈编号为：";
		cin >> checkHome;
		printNodeOrder(header, checkHome);
	}
	else if (order == 2) {
		cout << "本次卖出的总收入为：" << pricetemp << endl;
		printNode(sellheader);
		cout << endl;
	}
	else if (order == 3) {
		int check1, check2;
		cout << "请输入您查询的猪圈编号：";
		cin >> check1;
		cout << "请输入您查询的猪的编号：";
		cin >> check2;
		findPig(header, check1, check2);
	}
	else if (order == 4) {
		last1 = 0; last2 = 0; s1 = 0; s2 = 0; s21 = 0; s22 = 0;
		for (int i = 0; i < 100; i++) {
			if (pigHome[i][0].flag == 0) {
				s1 += pigHome[i][0].num;
			}
			else {
				for (int PP = 1; PP < 12; PP++) {
					if (pigHome[i][PP].num == 2)s21++;
					else if (pigHome[i][PP].num == 3)s22++;
				}
			}
		}
		s2 = s21 + s22;
		last1 = 10 * p - s1;
		last2 = 10 * (100 - p) - s2;


		cout << "当前猪场共有黑猪" << s1 << "只，小花猪" << s21 << "只，大花白猪" << s22 << "只" << endl;
		cout << "其中数量分布情况如下：（猪圈编号（数量））" << endl;
		cout << "黑猪:" << endl;
		if (s1 == 0)cout << "无" << endl;
		else {
			for (int i = 0; i < p; i++) {
				if (pigHome[i][0].num == 0)continue;
				if (i < 10)cout << 0;
				cout << i << "(" << pigHome[i][0].num << ")" << " ";
			}
		}
		cout << endl << endl << "小花猪：" << endl;
		if (s21 == 0)cout << "无" << endl;
		else {
			for (int i = p; i < 100; i++) {
				int UU = 0;
				for (int j = 1; j < 11; j++) {
					if (pigHome[i][j].num == 2)UU++;
				}
				if (UU == 0)continue;
				else cout << i << "(" << UU << ")" << " ";
			}
		}
		cout << endl << endl << "大花白猪：" << endl;
		if (s22 == 0)cout << "无" << endl;
		else {
			for (int i = p; i < 100; i++) {
				int UU = 0;
				for (int j = 1; j < 11; j++) {
					if (pigHome[i][j].num == 3)UU++;
				}
				if (UU == 0)continue;
				else cout << i << "(" << UU << ")" << " ";
			}
		}
		cout << endl << "体重分布情况如下：（区间：数量）" << endl;
		cout << "黑猪：" << endl;
		cout << "20-30(kg):" << sortheavy(header, 1, 20, 30) << "只" << endl;
		cout << "30-50(kg):" << sortheavy(header, 1, 30, 50) << "只" << endl;
		cout << "50-75(kg):" << sortheavy(header, 1, 50, 75) << "只" << endl;
		cout << "75-100(kg):" << sortheavy(header, 1, 75, 100) << "只" << endl;
		cout << "100-160(kg):" << sortheavy(header, 1, 100, 160) << "只" << endl;
		cout << endl;
		cout << "小花猪：" << endl;
		cout << "20-30(kg):" << sortheavy(header, 2, 20, 30) << "只" << endl;
		cout << "30-50(kg):" << sortheavy(header, 2, 30, 50) << "只" << endl;
		cout << "50-75(kg):" << sortheavy(header, 2, 50, 75) << "只" << endl;
		cout << "75-100(kg):" << sortheavy(header, 2, 75, 100) << "只" << endl;
		cout << "100-160(kg):" << sortheavy(header, 2, 100, 160) << "只" << endl;
		cout << endl;
		cout << "大花白猪：" << endl;
		cout << "20-30(kg):" << sortheavy(header, 3, 20, 30) << "只" << endl;
		cout << "30-50(kg):" << sortheavy(header, 3, 30, 50) << "只" << endl;
		cout << "50-75(kg):" << sortheavy(header, 3, 50, 75) << "只" << endl;
		cout << "75-100(kg):" << sortheavy(header, 3, 75, 100) << "只" << endl;
		cout << "100-160(kg):" << sortheavy(header, 3, 100, 160) << "只" << endl;
		cout << endl << "饲养时间分布情况如下：（区间：数量）" << endl;
		cout << "黑猪：" << endl;
		cout << "0-60(天):" << sortday(header, 1, 0, 60, q) << "只" << endl;
		cout << "60-120(天):" << sortday(header, 1, 60, 120, q) << "只" << endl;
		cout << "120-180(天):" << sortday(header, 1, 120, 180, q) << "只" << endl;
		cout << "180-240(天):" << sortday(header, 1, 180, 240, q) << "只" << endl;
		cout << "240-300(天):" << sortday(header, 1, 240, 300, q) << "只" << endl;
		cout << "300-365(天):" << sortday(header, 1, 300, 365, q) << "只" << endl;
		cout << endl;
		cout << "小花猪：" << endl;
		cout << "0-60(天):" << sortday(header, 2, 0, 60, q) << "只" << endl;
		cout << "60-120(天):" << sortday(header, 2, 60, 120, q) << "只" << endl;
		cout << "120-180(天):" << sortday(header, 2, 120, 180, q) << "只" << endl;
		cout << "180-240(天):" << sortday(header, 2, 180, 240, q) << "只" << endl;
		cout << "240-300(天):" << sortday(header, 2, 240, 300, q) << "只" << endl;
		cout << "300-365(天):" << sortday(header, 2, 300, 365, q) << "只" << endl;
		cout << endl;
		cout << "大花白猪：" << endl;
		cout << "0-60(天):" << sortday(header, 3, 0, 60, q) << "只" << endl;
		cout << "60-120(天):" << sortday(header, 3, 60, 120, q) << "只" << endl;
		cout << "120-180(天):" << sortday(header, 3, 120, 180, q) << "只" << endl;
		cout << "180-240(天):" << sortday(header, 3, 180, 240, q) << "只" << endl;
		cout << "240-300(天):" << sortday(header, 3, 240, 300, q) << "只" << endl;
		cout << "300-365(天):" << sortday(header, 3, 300, 365, q) << "只" << endl;
		cout << endl;
	}


	else if (order == 6) {
	printNode(illPigs);
	deleteList(illPigs);
	}

	else if (order == 5) {
		outFile.open("购入和销售记录.txt");
		outFile << "近五年的购入情况：" << endl;
		if (kk < 19) {
			for (int i = 0; i < kk; i++) {
				outFile << "第" << i + 1 << "次购入：黑猪(" << bought[i].num1 << ")，小花猪(" << bought[i].num2 << ")，大花白猪(" << bought[i].num3 << ")" << endl;
			}
		}
		else {
			int j = kk - 19;
			for (int i = 1; i <= 20; i++, j++) {
				outFile << "第" << i << "次购入：黑猪(" << bought[j].num1 << ")，小花猪(" << bought[j].num2 << ")，大花白猪(" << bought[j].num3 << ")" << endl;
			}
		}
		outFile << endl;
		outFile << "近五年的销售记录：" << endl;
		if (kk < 19) {
			for (int i = 1; i < kk; i++) {
				outFile << "第" << i << "次出售：黑猪(" << sellTime[i][1] << ")，小花猪(" << sellTime[i][2] << ")，大花白猪(" << sellTime[i][3] << ")" << endl;
			}
		}
		else {
			int j = kk - 19;
			for (int i = 1; i <= 20; i++, j++) {
				outFile << "第" << i << "次购入：黑猪(" << sellTime[j][1] << ")，小花猪(" << sellTime[j][2] << ")，大花白猪(" << sellTime[j][3] << ")" << endl;
			}
		}
		outFile.close();																														////存档




		


		if (kk < 19) {
			for (int i = 0; i < kk; i++) {
				cout << "第" << i + 1 << "次购入：黑猪(" << bought[i].num1 << ")，小花猪(" << bought[i].num2 << ")，大花白猪(" << bought[i].num3 << ")" << endl;
			}
		}
		else {
			int j = kk - 19;
			for (int i = 1; i <= 20; i++, j++) {
				cout << "第" << i << "次购入：黑猪(" << bought[j].num1 << ")，小花猪(" << bought[j].num2 << ")，大花白猪(" << bought[j].num3 << ")" << endl;
			}
		}
		outFile << endl;
		outFile << "近五年的销售记录：" << endl;
		if (kk < 19) {
			for (int i = 1; i < kk; i++) {
				cout << "第" << i << "次出售：黑猪(" << sellTime[i][1] << ")，小花猪(" << sellTime[i][2] << ")，大花白猪(" << sellTime[i][3] << ")" << endl;
			}
		}
		else {
			int j = kk - 19;
			for (int i = 1; i <= 20; i++, j++) {
				cout << "第" << i << "次购入：黑猪(" << sellTime[j][1] << ")，小花猪(" << sellTime[j][2] << ")，大花白猪(" << sellTime[j][3] << ")" << endl;
			}
		}

	}
	else if (order == 10)printNode(header);
}


int main(){
	loadList(header);
	printNode(header);
	deleteList(header);
	cout << endl;
	cout << "以上为上次程序结束时的猪圈信息" << endl << endl << "下面开始本次程序：" << endl;
	cout << "-----------------------------------------------------------------------------------------"<<endl;


	cout << "是否模拟猪瘟：输入1模拟，0不模拟：";
	cin >> ttemp;
	cout << endl;
	if (ttemp == 1) {
		cout << "请输入模拟的猪瘟多少天后会导致猪死亡：";
		cin >> tttemp;
		cout << endl;
	}
	srand((unsigned)time(NULL));
	memset(pigHome, 0, sizeof(pigHome));
	memset(bought, 0, sizeof(bought));
	memset(sellTime, 0, sizeof(sellTime));
	for (int i = 0; i < 100; i++) {
		if (pigHome[i][0].num != 0)QQQ = 1;
	}
	cout << "初始录入：" << endl;
again:
	cout << "黑猪的数量为：";
	cin >> A;
	cout << "小花猪的数量为：";
	cin >> B;
	cout << "大花白猪的数量为：";
	cin >> C;
	if (A == 0 && B == 0 && C == 0) {
		cout << "\n至少加入一头任意品种的猪，请重新输入:\n";
		goto again;
	}
	else if (A + B + C > 1000) {
		cout << "初始猪场只能容纳1000只猪，请重新输入：\n";
		goto again;
	}
	bought[0].num1 = A;
	bought[0].num2 = B;
	bought[0].num3 = C;
	float D = (float)A;
	NUM = A + B + C;
	x = D / (A + B + C);
	p = int(x * 100);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < 12; j++)
			pigHome[i][j].flag = 0;
	}
	for (int i = p; i < 100; i++) {
		for (int j = 0; j < 12; j++)
			pigHome[i][j].flag = 1;
	}

	int temp = rand() % NUM+1;

	store(header, A, B, C, q, p);

	printNode(header);

	if (ttemp == 1) {
		illPigHome = illPig(header, temp);				//随机一只猪生病，并得到病猪的猪圈编号
		cout << "是否采取隔离措施，输入1是，0否：";
		pigHome[illPigHome][11].num = 1;
		cin >> ttttemp;
		if (ttttemp == 0)goto end;
		else {
			cout << "请输入每只猪有百分之多少的概率自然得病：";
			cin >> gailv;		
		}
	}
	
	
	



	do
	{
		nodead = updata();
		system("cls");
		cout << "第" << q << "天"<<endl<<endl<<"按任意键暂停进行查询"<<endl;
		if (_kbhit()) {
		Again:
			int ng = Order();
			if (ng == 0)break;
			cout << "继续查询输入1，停止查询输入其他键" << endl;
			cin >> ng;
			if (ng == 1)goto Again;
		}
	} while (nodead);																	///每天更新（每秒更新）

	





end:
	if (ttttemp == 0 && ttemp ==1 ) {
		int deadDay = 0,temp1;
		for (deadDay;; deadDay++) {
			struct Node* pmove = header->next;
			struct Node* pmoveFront = header;
			while (pmove != NULL) {
				temp1 = rand() % 100 + 1;
				if (pmove->status != 0) {
					if (pmove->status > tttemp) {
						pigHome[pmove->home][11].num--;
						pmove = pmove->next;
						free(pmoveFront->next);
						pmoveFront->next=pmove;		
						NUM--;
					}
					else {
						pmove->status++;
						pmove = pmove->next;
						pmoveFront = pmoveFront->next;
					}
				}
				else {
					if (pigHome[pmove->home][11].num !=0) {
						if (temp1 <= 50) {
							pmove->status = 1;
							pigHome[pmove->home][11].num++;
						}
					}
					else if (pigHome[pmove->home][11].num == 0 || pigHome[pmove->home + 1][11].num !=0 || pigHome[pmove->home - 1][11].num !=0) {
						if (temp1 <= 15) {
							pmove->status = 1;
							pigHome[pmove->home][11].num = 1;
						}
					}
					pmove = pmove->next;
					pmoveFront = pmoveFront->next;
				}
			}
			if (NUM == 0) {
				cout << "第" << deadDay << "天猪全死光";
				break;
			}
			int k=0;
			for (int i = 0; i < 100; i++) {
				if (pigHome[i][11].num == 1) {
					k = 1; break;
				}
			}
			if (k == 0) {
				cout << "猪瘟传染不充分，猪不会死光";
				break;
			}
		}
	}


	saveList(header);
	cout << endl << "程序结束";
}

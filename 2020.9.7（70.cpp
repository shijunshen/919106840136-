#include<stdio.h>
#include<time.h>
#include<iostream>
#include<string>
#include<stdlib.h> 
#include<cstring>
#include<ctime>
using namespace std;

int getTime() {
	return clock() / CLOCKS_PER_SEC;
}

struct A {
	bool flag;
	int num;
}pigHome[100][11];

struct Node {
	int variety;
	int home;
	long time;
	float kg;
	int Number;
	struct Node* next;
};

struct Node* creatList() {
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next = NULL;
	return headNode;
}

struct Node* creatNode(int home, int variety,float kg,long time,int Number) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->home = home;
	newNode->next = NULL;
	newNode->variety = variety;
	newNode->kg = kg;
	newNode->Number = Number;
	newNode->time = time;
	return newNode;
}

void sortInsertNode(struct Node* headNode, int home, int variety, float kg,long time,int Number) {
	struct Node* newNode=creatNode(home,variety,kg,time,Number);
	struct Node* postNode = headNode->next;
	struct Node* postNodeFront = headNode;
	if (postNode == NULL) {
		postNodeFront->next = newNode;
		newNode->next = NULL;
		return;
	}
	else {
		while ((postNode->home) <=home) {
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

void deleteNode(struct Node* headNode, int home, int variety, float kg) {
	struct Node* postNode = headNode->next;
	struct Node* postNodeFront = headNode;
	if (postNode == NULL) {
		cout << "列表为空";
	}
	else {
		while (postNode->home != home || postNode->variety != variety||postNode->kg!=kg) {
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
		cout << "该猪所在猪圈编号为："<<pmove->home << " "<<"该猪种类为：" << pmove->variety <<" "<<"该猪的当前体重为:"<<pmove->kg<<" "<<"该猪的编号为"<<pmove->Number<<endl;
		pmove = pmove->next;
	}
}

void printNodeOrder(struct Node* headNode,int home) {
	struct Node* pmove = headNode->next;
	int num=0,q=0,q2=0,q3=0;
	while (pmove != NULL) {
		if (pmove->home == home) {
			num++;
			if (pmove->variety == 1)q = 1;
			else if (pmove->variety == 2)q2++;
			else if (pmove->variety == 3)q3++;
		}	
		pmove = pmove->next;
	}
	if (q)cout << endl<< "编号为" << home << "的猪圈共有" << num << "只猪，全为黑猪"<<endl;
	else {
		cout <<endl<< "编号为" << home << "的猪圈共有" << num << "只猪，其中有" << q2 << "只小花猪，有" << q3 << "只大花白猪"<<endl;
	}
}

void printPig(struct Node* pig) {
	cout << "该猪品种为：" << pig->variety << endl;
	cout << "该猪当前体重为：" << pig->kg << endl;
}

void store(struct Node* headNode, int A, int B, int C,long time,int p) {	
	int Number=0;
	while (A) {
		for (int i = 0; i < p; i++) {
			float temp = float(rand() % 30 + 20);
			for (int j = 1; j < 11; j++) {
				if (pigHome[i][j].num == 0) {
					Number = j; break;
				}
			}
			sortInsertNode(headNode, i, 1, temp, time,Number);
			pigHome[i][0].num++;
			pigHome[i][Number].num = 1;
			A--;
			if (!A)break;
		}
	}
	int TT = B + C;
	int j1 = 0, k1 = 0;
	while (TT) {
		int i1 = p;
		for (; j1 < B && i1 < 100; j1++, i1++) {
			float temp = float(rand() % 30 + 20);
			for (int j = 1; j < 11; j++) {
				if (pigHome[i1][j].num == 0) {
					Number = j; break;
				}
			}
			sortInsertNode(headNode, i1, 2, temp,time,Number);
			pigHome[i1][0].num++;
			pigHome[i1][Number].num = 1;
			TT--;
		}
		if (j1 < B)continue;
		for (; k1 < C && i1 < 100; i1++, k1++) {
			float temp = float(rand() % 30 + 20);
			for (int j = 1; j < 11; j++) {
				if (pigHome[i1][j].num == 0) {
					Number = j; break;
				}
			}
			sortInsertNode(headNode, i1, 3, temp,time,Number);
			pigHome[i1][0].num++;
			pigHome[i1][Number].num = 2;
			TT--;
		}
	}
}

void grow(struct Node* headNode,int timeBetween) {
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		for (int i = 0; i < timeBetween; i++) {
			float temp = (rand() % 12)*1.0/10;
			pmove->kg += temp;
		}
		pmove = pmove->next;
	}
}

void findPig(struct Node* headNode,int a, int b) {
	struct Node* pmove = headNode->next;
	int flag = 0;
	while (pmove != NULL&&pmove->home<=a) {
		if (pmove->home == a && pmove->Number == b) {
			flag = 1; break;
		}
	}
	if (!flag)cout << "该猪圈没有该编号的猪" << endl;
	else printPig(pmove);
}

void sell(struct Node* headNode,struct Node* sellheader,long nowTime) {
	struct Node* pmove = headNode->next;
	struct Node* pmoveFront = headNode;
	while (pmove != NULL) {
		if (pmove->kg > 75||(nowTime-pmove->time)>365) {
			sortInsertNode(sellheader, pmove->home, pmove->variety, pmove->kg,pmove->time,pmove->Number);
			pigHome[pmove->home][pmove->Number].num=0;
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

int sortheavy(struct Node* headNode, int variety,int a, int b) {
	int num=0;
	struct Node* pmove = headNode->next;
	while (pmove!=NULL) {
		if (pmove->variety == variety && pmove->kg > a && pmove->kg <= b)num++;
		pmove = pmove->next;
	}
	return num;
}

int sortday(struct Node* headNode,int variety, int a, int b, int timeBegin) {
	int num = 0;
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		if (pmove->variety == variety && timeBegin-pmove->time > a && timeBegin - pmove->time <= b)num++;
		pmove = pmove->next;
	}
	return num;
}

int main() {
	srand((unsigned)time(NULL));
	time_t timep;
	int order, q = 0, A, B, C,tempp=0,SS=0;
	char variety[10];
	struct Node* header = creatList(); 
	struct Node* sellheader = creatList();
	memset(pigHome, 0, sizeof(pigHome));
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
	float D = (float)A;
	int NUM = A + B + C;
	float x = D / (A + B + C);
	int p = int(x * 100);
	for (int i = 0; i < p; i++) {
		for(int j=0;j<10;j++)
		pigHome[i][j].flag = 0;
	}
	for (int i = p; i < 100; i++) {
		for (int j = 0; j < 10; j++)
		pigHome[i][j].flag = 1;
	}
	time(&timep);			
	long timeBegin = timep;              //timeBegin为初始时间
	long timeFirst = timep;				 //timeFirst为第一批猪进入的初始时间
	store(header,A, B, C, timeBegin,p);
	printNode(header);
	while (1) {
		if (q)cout << endl;
		q++;
		cout << "-----------------------------------------------------" << endl;
		cout << "                      输入指令                       " << endl;
		cout << "                      停止（0）                      " << endl;
		cout << "                     加入猪（1）                     " << endl;
		cout << "           查询当前某一猪圈的猪的数量和种类（2）     " << endl;
		cout << "                计算本次出圈猪的总价（3）            " << endl;
		cout << "             查询某圈某一编号的猪的状态（4）         " << endl;
		cout << "               查询当前猪场的整体情况（5）           " << endl;
		cout << "-----------------------------------------------------" << endl;
		cin >> order;
		time(&timep);
		long timeNow = timep;
		int timeBetween = timeNow - timeBegin;	 //timeBetween为两次指令的间隔时间
		int timeBetweenFirst = timeNow - timeFirst;	 //timeBetweenFirst为程序开始到本次指令的间隔时间
		timeBegin = timeNow;
		timeNow = 0;
		tempp = SS;
		SS = timeBetweenFirst / 90;					//为了方便调试
		if (SS > tempp) {
			deleteList(sellheader);
			sell(header, sellheader, timeBegin);
		}
		grow(header, timeBetween);
		int s1 = 0, s2 = 0, s21=0, s22=0, last1, last2;					//s1黑猪和s2花猪目前存放的数量
		for (int i = 0; i < 100; i++) {
			if (pigHome[i][0].flag == 0) {
				s1 += pigHome[i][0].num;
			}
			else {
				for (int PP = 1; PP < 11; PP++) {
					if (pigHome[i][PP].num == 1)s21++;
					else if (pigHome[i][PP].num == 2)s22++;
				}
			}		
		}
		s2 = s21 + s22;
		if (order == 0)break;
		else if (order == 1) {			
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
			store(header, A, B, C, timeBegin, p);
			printNode(header);
		}
		else if (order == 2) {
			int checkHome;
			cout << endl << "输入你要查询的猪圈编号为：";
			cin >> checkHome;
			printNodeOrder(header, checkHome);
		}
		else if (order == 3) {
			if (SS == 0)cout << "尚未开始出售";
			else {
				cout << "第" << SS << "次:\n";
				printNode(sellheader);
				cout << endl;
				cout << price(sellheader) << endl;
			}
		}
		else if (order == 4) {
			int check1,check2;
			cout << "请输入您查询的猪圈编号：";
			cin >> check1;
			cout << "请输入您查询的猪的编号：";
			cin >> check2;
			findPig(header,check1, check2);
		}
		else if (order == 5) {
			cout << "当前猪场共有黑猪" << s1 << "只，小花猪" << s21 << "只，大花白猪" << s22 << "只" << endl;
			cout << "其中数量分布情况如下：（猪圈编号（数量））"<<endl;
			cout << "黑猪:"<<endl;
			for (int i = 0; i < p; i++) {
				if (pigHome[i][0].num == 0)continue;
				if (i < 10)cout << 0;
				cout << i << "（"<< pigHome[i][0].num << "）"<<" ";
			}
			cout << endl<<endl << "小花猪："<<endl;
			for (int i = p; i < 100; i++) {
				int UU = 0;
				for (int j = 1; j < 11; j++) {
					if (pigHome[i][j].num == 1)UU++;
				}
				if (UU == 0)continue;
				else cout << i << "（" << UU << "）" << " ";
			}
			cout << endl <<endl<< "大花白猪："<< endl;
			for (int i = p; i < 100; i++) {
				int UU = 0;
				for (int j = 1; j < 11; j++) {
					if (pigHome[i][j].num == 2)UU++;
				}
				if (UU == 0)continue;
				else cout << i << "（" << UU << "）" << " ";
			}
			cout << endl << "体重分布情况如下：（区间：数量）" << endl;
			cout << "黑猪：" << endl;
			cout << "20-30(kg):" << sortheavy(header, 1, 20, 30) << "只"<<endl;
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
			cout << "0-60(天):" << sortday(header, 1, 0, 60, timeBegin) << "只" << endl;
			cout << "60-120(天):" << sortday(header, 1, 60, 120, timeBegin) << "只" << endl;
			cout << "120-180(天):" << sortday(header, 1, 120, 180, timeBegin) << "只" << endl;
			cout << "180-240(天):" << sortday(header, 1, 180, 240, timeBegin) << "只" << endl;
			cout << "240-300(天):" << sortday(header, 1, 240, 300, timeBegin) << "只" << endl;
			cout << "300-365(天):" << sortday(header, 1, 300, 365, timeBegin) << "只" << endl;
			cout << endl;
			cout << "小花猪：" << endl;
			cout << "0-60(天):" << sortday(header, 2, 0, 60, timeBegin) << "只" << endl;
			cout << "60-120(天):" << sortday(header, 2, 60, 120, timeBegin) << "只" << endl;
			cout << "120-180(天):" << sortday(header, 2, 120, 180, timeBegin) << "只" << endl;
			cout << "180-240(天):" << sortday(header, 2, 180, 240, timeBegin) << "只" << endl;
			cout << "240-300(天):" << sortday(header, 2, 240, 300, timeBegin) << "只" << endl;
			cout << "300-365(天):" << sortday(header, 2, 300, 365, timeBegin) << "只" << endl;
			cout << endl;
			cout << "大花白猪：" << endl;
			cout << "0-60(天):" << sortday(header, 3, 0, 60, timeBegin) << "只" << endl;
			cout << "60-120(天):" << sortday(header, 3, 60, 120, timeBegin) << "只" << endl;
			cout << "120-180(天):" << sortday(header, 3, 120, 180, timeBegin) << "只" << endl;
			cout << "180-240(天):" << sortday(header, 3, 180, 240, timeBegin) << "只" << endl;
			cout << "240-300(天):" << sortday(header, 3, 240, 300, timeBegin) << "只" << endl;
			cout << "300-365(天):" << sortday(header, 3, 300, 365, timeBegin) << "只" << endl;
			cout << endl;
		}
		else if (order == 10) {
			printNode(header);        //方便调试
			cout << endl << timeBetweenFirst << endl;			//方便调试
		}
	}
	printNode(header);
	cout << endl << "程序结束";
}

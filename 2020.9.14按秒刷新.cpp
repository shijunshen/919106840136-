#include<iostream>
#include<stdio.h>
#include<time.h>
#include<string>
#include<stdlib.h>
#include <conio.h>              //getch()��ͷ�ļ�
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
		cout << "�б�Ϊ��";
	}
	else {
		while (postNode->home != home || postNode->variety != variety || postNode->kg != kg) {
			postNode = postNode->next;
			postNodeFront = postNodeFront->next;
			if (postNode == NULL) {
				cout << "û���ҵ������Ϣ���޷�ɾ��";
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
		cout << "����������Ȧ���Ϊ��" << pmove->home << " " << "��������Ϊ��" << pmove->variety << " " << "����ĵ�ǰ����Ϊ:" << pmove->kg << " " << "����ı��Ϊ" << pmove->Number << " " << "ʱ��Ϊ��" << pmove->time << endl;
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
	if (q)cout << endl << "���Ϊ" << home << "����Ȧ����" << num << "ֻ��ȫΪ����" << endl;
	else {
		cout << endl << "���Ϊ" << home << "����Ȧ����" << num << "ֻ��������" << q2 << "ֻС������" << q3 << "ֻ�󻨰���" << endl;
	}
}

void printPig(struct Node* pig) {
	cout << "����Ʒ��Ϊ��" ;
	if (pig->variety == 1)cout << "����";
	else if (pig->variety == 2)cout << "С����";
	else if (pig->variety == 3)cout << "�󻨰���";
	cout << endl;
	cout << "����ǰ����Ϊ��" << pig->kg << endl;
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
	if (!flag)cout << "����Ȧû�иñ�ŵ���" << endl;
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
	outFile.open("��Ȧ��Ϣ.txt");
	struct Node* pmove = headNode->next;
	while (pmove != NULL) {
		outFile << pmove->home << " " << pmove->variety << " " << pmove->kg << " " << pmove->time << " " << pmove->Number << endl;
		pmove = pmove->next;
	}
	outFile << 0 << " " << 0;
	outFile.close();
}

void loadList(struct Node* headNode) {
	inFile.open("��Ȧ��Ϣ.txt");
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
		last2 = 10 * (100 - p) - s2;				//last1�������ɵĺ�������last2�������ɵĻ�����			 
	again1:
		cout << endl << "�����������������������������" << last1 << "ֻ������������" << last2 << "ֻ��" << endl;
		cout << "���������Ϊ��";
		cin >> A;
		cout << "С���������Ϊ��";
		cin >> B;
		cout << "�󻨰��������Ϊ��";
		cin >> C;
		if (A == 0 && B == 0 && C == 0) {
			cout << "\n���ټ���һͷ����Ʒ�ֵ�������������:\n";
			goto again1;
		}
		else if (A > last1 || (B + C) > last2) {
			cout << "\n��Ȧ���أ������ʣ����ʾ��������:\n";
			goto again1;
		}
		bought[kk].num1 = A;
		bought[kk].num2 = B;
		bought[kk].num3 = C;
		kk++;
		store(header, A, B, C, q, p);
		printNode(header);                                             //����һ����
		
	}
	return gameover;
}
		
int Order() {

	cout << "-----------------------------------------------------" << endl;
	cout << "                      ����ָ��                       " << endl;
	cout << "                      ֹͣ��0��                      " << endl;
	cout << "           ��ѯ��ǰĳһ��Ȧ��������������ࣨ1��     " << endl;
	cout << "                ���㱾�γ�Ȧ����ܼۣ�2��            " << endl;
	cout << "             ��ѯĳȦĳһ��ŵ����״̬��3��         " << endl;
	cout << "               ��ѯ��ǰ�������������4��           " << endl;
	cout << "           ��ѯ����������ۼ�¼�͹����¼��5��       " << endl;
	cout << "-----------------------------------------------------" << endl;
	cin >> order;
	if (order == 0)return 0;
	else if (order == 1) {
		int checkHome;
		cout << endl << "������Ҫ��ѯ����Ȧ���Ϊ��";
		cin >> checkHome;
		printNodeOrder(header, checkHome);
	}
	else if (order == 2) {
		cout << "����������������Ϊ��" << pricetemp << endl;
		printNode(sellheader);
		cout << endl;
	}
	else if (order == 3) {
		int check1, check2;
		cout << "����������ѯ����Ȧ��ţ�";
		cin >> check1;
		cout << "����������ѯ����ı�ţ�";
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


		cout << "��ǰ�����к���" << s1 << "ֻ��С����" << s21 << "ֻ���󻨰���" << s22 << "ֻ" << endl;
		cout << "���������ֲ�������£�����Ȧ��ţ���������" << endl;
		cout << "����:" << endl;
		if (s1 == 0)cout << "��" << endl;
		else {
			for (int i = 0; i < p; i++) {
				if (pigHome[i][0].num == 0)continue;
				if (i < 10)cout << 0;
				cout << i << "(" << pigHome[i][0].num << ")" << " ";
			}
		}
		cout << endl << endl << "С����" << endl;
		if (s21 == 0)cout << "��" << endl;
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
		cout << endl << endl << "�󻨰���" << endl;
		if (s22 == 0)cout << "��" << endl;
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
		cout << endl << "���طֲ�������£������䣺������" << endl;
		cout << "����" << endl;
		cout << "20-30(kg):" << sortheavy(header, 1, 20, 30) << "ֻ" << endl;
		cout << "30-50(kg):" << sortheavy(header, 1, 30, 50) << "ֻ" << endl;
		cout << "50-75(kg):" << sortheavy(header, 1, 50, 75) << "ֻ" << endl;
		cout << "75-100(kg):" << sortheavy(header, 1, 75, 100) << "ֻ" << endl;
		cout << "100-160(kg):" << sortheavy(header, 1, 100, 160) << "ֻ" << endl;
		cout << endl;
		cout << "С����" << endl;
		cout << "20-30(kg):" << sortheavy(header, 2, 20, 30) << "ֻ" << endl;
		cout << "30-50(kg):" << sortheavy(header, 2, 30, 50) << "ֻ" << endl;
		cout << "50-75(kg):" << sortheavy(header, 2, 50, 75) << "ֻ" << endl;
		cout << "75-100(kg):" << sortheavy(header, 2, 75, 100) << "ֻ" << endl;
		cout << "100-160(kg):" << sortheavy(header, 2, 100, 160) << "ֻ" << endl;
		cout << endl;
		cout << "�󻨰���" << endl;
		cout << "20-30(kg):" << sortheavy(header, 3, 20, 30) << "ֻ" << endl;
		cout << "30-50(kg):" << sortheavy(header, 3, 30, 50) << "ֻ" << endl;
		cout << "50-75(kg):" << sortheavy(header, 3, 50, 75) << "ֻ" << endl;
		cout << "75-100(kg):" << sortheavy(header, 3, 75, 100) << "ֻ" << endl;
		cout << "100-160(kg):" << sortheavy(header, 3, 100, 160) << "ֻ" << endl;
		cout << endl << "����ʱ��ֲ�������£������䣺������" << endl;
		cout << "����" << endl;
		cout << "0-60(��):" << sortday(header, 1, 0, 60, q) << "ֻ" << endl;
		cout << "60-120(��):" << sortday(header, 1, 60, 120, q) << "ֻ" << endl;
		cout << "120-180(��):" << sortday(header, 1, 120, 180, q) << "ֻ" << endl;
		cout << "180-240(��):" << sortday(header, 1, 180, 240, q) << "ֻ" << endl;
		cout << "240-300(��):" << sortday(header, 1, 240, 300, q) << "ֻ" << endl;
		cout << "300-365(��):" << sortday(header, 1, 300, 365, q) << "ֻ" << endl;
		cout << endl;
		cout << "С����" << endl;
		cout << "0-60(��):" << sortday(header, 2, 0, 60, q) << "ֻ" << endl;
		cout << "60-120(��):" << sortday(header, 2, 60, 120, q) << "ֻ" << endl;
		cout << "120-180(��):" << sortday(header, 2, 120, 180, q) << "ֻ" << endl;
		cout << "180-240(��):" << sortday(header, 2, 180, 240, q) << "ֻ" << endl;
		cout << "240-300(��):" << sortday(header, 2, 240, 300, q) << "ֻ" << endl;
		cout << "300-365(��):" << sortday(header, 2, 300, 365, q) << "ֻ" << endl;
		cout << endl;
		cout << "�󻨰���" << endl;
		cout << "0-60(��):" << sortday(header, 3, 0, 60, q) << "ֻ" << endl;
		cout << "60-120(��):" << sortday(header, 3, 60, 120, q) << "ֻ" << endl;
		cout << "120-180(��):" << sortday(header, 3, 120, 180, q) << "ֻ" << endl;
		cout << "180-240(��):" << sortday(header, 3, 180, 240, q) << "ֻ" << endl;
		cout << "240-300(��):" << sortday(header, 3, 240, 300, q) << "ֻ" << endl;
		cout << "300-365(��):" << sortday(header, 3, 300, 365, q) << "ֻ" << endl;
		cout << endl;
	}


	else if (order == 6) {
	printNode(illPigs);
	deleteList(illPigs);
	}

	else if (order == 5) {
		outFile.open("��������ۼ�¼.txt");
		outFile << "������Ĺ��������" << endl;
		if (kk < 19) {
			for (int i = 0; i < kk; i++) {
				outFile << "��" << i + 1 << "�ι��룺����(" << bought[i].num1 << ")��С����(" << bought[i].num2 << ")���󻨰���(" << bought[i].num3 << ")" << endl;
			}
		}
		else {
			int j = kk - 19;
			for (int i = 1; i <= 20; i++, j++) {
				outFile << "��" << i << "�ι��룺����(" << bought[j].num1 << ")��С����(" << bought[j].num2 << ")���󻨰���(" << bought[j].num3 << ")" << endl;
			}
		}
		outFile << endl;
		outFile << "����������ۼ�¼��" << endl;
		if (kk < 19) {
			for (int i = 1; i < kk; i++) {
				outFile << "��" << i << "�γ��ۣ�����(" << sellTime[i][1] << ")��С����(" << sellTime[i][2] << ")���󻨰���(" << sellTime[i][3] << ")" << endl;
			}
		}
		else {
			int j = kk - 19;
			for (int i = 1; i <= 20; i++, j++) {
				outFile << "��" << i << "�ι��룺����(" << sellTime[j][1] << ")��С����(" << sellTime[j][2] << ")���󻨰���(" << sellTime[j][3] << ")" << endl;
			}
		}
		outFile.close();																														////�浵




		


		if (kk < 19) {
			for (int i = 0; i < kk; i++) {
				cout << "��" << i + 1 << "�ι��룺����(" << bought[i].num1 << ")��С����(" << bought[i].num2 << ")���󻨰���(" << bought[i].num3 << ")" << endl;
			}
		}
		else {
			int j = kk - 19;
			for (int i = 1; i <= 20; i++, j++) {
				cout << "��" << i << "�ι��룺����(" << bought[j].num1 << ")��С����(" << bought[j].num2 << ")���󻨰���(" << bought[j].num3 << ")" << endl;
			}
		}
		outFile << endl;
		outFile << "����������ۼ�¼��" << endl;
		if (kk < 19) {
			for (int i = 1; i < kk; i++) {
				cout << "��" << i << "�γ��ۣ�����(" << sellTime[i][1] << ")��С����(" << sellTime[i][2] << ")���󻨰���(" << sellTime[i][3] << ")" << endl;
			}
		}
		else {
			int j = kk - 19;
			for (int i = 1; i <= 20; i++, j++) {
				cout << "��" << i << "�ι��룺����(" << sellTime[j][1] << ")��С����(" << sellTime[j][2] << ")���󻨰���(" << sellTime[j][3] << ")" << endl;
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
	cout << "����Ϊ�ϴγ������ʱ����Ȧ��Ϣ" << endl << endl << "���濪ʼ���γ���" << endl;
	cout << "-----------------------------------------------------------------------------------------"<<endl;


	cout << "�Ƿ�ģ������������1ģ�⣬0��ģ�⣺";
	cin >> ttemp;
	cout << endl;
	if (ttemp == 1) {
		cout << "������ģ��������������ᵼ����������";
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
	cout << "��ʼ¼�룺" << endl;
again:
	cout << "���������Ϊ��";
	cin >> A;
	cout << "С���������Ϊ��";
	cin >> B;
	cout << "�󻨰��������Ϊ��";
	cin >> C;
	if (A == 0 && B == 0 && C == 0) {
		cout << "\n���ټ���һͷ����Ʒ�ֵ�������������:\n";
		goto again;
	}
	else if (A + B + C > 1000) {
		cout << "��ʼ��ֻ������1000ֻ�����������룺\n";
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
		illPigHome = illPig(header, temp);				//���һֻ�����������õ��������Ȧ���
		cout << "�Ƿ��ȡ�����ʩ������1�ǣ�0��";
		pigHome[illPigHome][11].num = 1;
		cin >> ttttemp;
		if (ttttemp == 0)goto end;
		else {
			cout << "������ÿֻ���аٷ�֮���ٵĸ�����Ȼ�ò���";
			cin >> gailv;		
		}
	}
	
	
	



	do
	{
		nodead = updata();
		system("cls");
		cout << "��" << q << "��"<<endl<<endl<<"���������ͣ���в�ѯ"<<endl;
		if (_kbhit()) {
		Again:
			int ng = Order();
			if (ng == 0)break;
			cout << "������ѯ����1��ֹͣ��ѯ����������" << endl;
			cin >> ng;
			if (ng == 1)goto Again;
		}
	} while (nodead);																	///ÿ����£�ÿ����£�

	





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
				cout << "��" << deadDay << "����ȫ����";
				break;
			}
			int k=0;
			for (int i = 0; i < 100; i++) {
				if (pigHome[i][11].num == 1) {
					k = 1; break;
				}
			}
			if (k == 0) {
				cout << "������Ⱦ����֣���������";
				break;
			}
		}
	}


	saveList(header);
	cout << endl << "�������";
}

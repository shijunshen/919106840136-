#include<iostream>
#include<stdio.h>
#include<time.h>
#include<string>
#include<stdlib.h> 
#include<cstring>
#include<ctime>
#include <fstream>
#define maxn 100001
using namespace std;
ofstream outFile;
ifstream inFile;
int getTime() {
	return clock() / CLOCKS_PER_SEC;
}

int sellTime[maxn][4];

struct A {
	bool flag;
	int num;
}pigHome[100][11];

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
	struct Node* next;
};

struct Node* creatList() {
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next = NULL;
	return headNode;
}

struct Node* creatNode(int home, int variety, float kg, long time, int Number) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->home = home;
	newNode->next = NULL;
	newNode->variety = variety;
	newNode->kg = kg;
	newNode->Number = Number;
	newNode->time = time;
	return newNode;
}

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
	cout << "����Ʒ��Ϊ��" << pig->variety << endl;
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
		if (pmove->variety == variety && timeBegin - pmove->time > a && timeBegin - pmove->time <= b)num++;
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

int main() {
	cout << "�Ƿ�ģ������������1ģ�⣬0��ģ��";
	int ttemp;
	cin >> ttemp;
	srand((unsigned)time(NULL));
	time_t timep;
	int order, q = 0, A, B, C, tempp = 0, SS = 0, pricetemp, threeMonth = 0;
	struct Node* header = creatList();
	struct Node* sellheader = creatList();
	loadList(header);
	printNode(header);
	deleteList(header);
	memset(pigHome, 0, sizeof(pigHome));
	memset(bought, 0, sizeof(bought));
	memset(sellTime, 0, sizeof(sellTime));
	int QQQ = 0;
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
	int NUM = A + B + C;
	float x = D / (A + B + C);
	int p = int(x * 100);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < 11; j++)
			pigHome[i][j].flag = 0;
	}
	for (int i = p; i < 100; i++) {
		for (int j = 0; j < 11; j++)
			pigHome[i][j].flag = 1;
	}
	time(&timep);
	long timeBegin = timep;              //timeBeginΪ��ʼʱ��
	long timeFirst = timep;				 //timeFirstΪ��һ�������ĳ�ʼʱ��
	store(header, A, B, C, timeBegin, p);		printNode(header);
	while (1) {
		if (q)cout << endl;
		q++;
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
		time(&timep);
		long timeNow = timep;
		int timeBetween = timeNow - timeBegin;	 //timeBetweenΪ����ָ��ļ��ʱ��
		int timeBetweenFirst = timeNow - timeFirst;	 //timeBetweenFirstΪ����ʼ������ָ��ļ��ʱ��
		timeBegin = timeNow;
		timeNow = 0;
		grow(header, timeBetween);
		tempp = SS;
		SS = timeBetweenFirst / 10;					//Ϊ�˷������
		threeMonth = SS - tempp;
		int s1 = 0, s2 = 0, s21 = 0, s22 = 0, last1, last2;					//s1�����s2����Ŀǰ��ŵ�����
		for (int i = 0; i < 100; i++) {
			if (pigHome[i][0].flag == 0) {
				s1 += pigHome[i][0].num;
			}
			else {
				for (int PP = 1; PP < 11; PP++) {
					if (pigHome[i][PP].num == 2)s21++;
					else if (pigHome[i][PP].num == 3)s22++;
				}
			}
		}
		s2 = s21 + s22;
		if (SS > tempp) {
			for (int kk = 0; kk < threeMonth; kk++) {
				deleteList(sellheader);
				sell(header, sellheader, timeFirst + 10 * (kk + tempp + 1));
				pricetemp = price(sellheader);
				sellTime[tempp + kk + 1][0] = pricetemp;
				sellTime[tempp + kk + 1][1] = mark(sellheader, 1);
				sellTime[tempp + kk + 1][2] = mark(sellheader, 2);
				sellTime[tempp + kk + 1][3] = mark(sellheader, 3);
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
				bought[tempp + kk + 1].num1 = A;
				bought[tempp + kk + 1].num2 = B;
				bought[tempp + kk + 1].num3 = C;
				store(header, A, B, C, timeFirst + 10 * (kk + tempp + 1), p);
				printNode(header);
			}
		}
		if (order == 0)break;
		else if (order == 1) {
			int checkHome;
			cout << endl << "������Ҫ��ѯ����Ȧ���Ϊ��";
			cin >> checkHome;
			printNodeOrder(header, checkHome);
		}
		else if (order == 2) {
			if (SS == 0)cout << "��δ��ʼ����";
			else {
				cout << "��" << SS << "��������������Ϊ��" << pricetemp << endl;
				printNode(sellheader);
				cout << endl;
			}
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
			cout << "0-60(��):" << sortday(header, 1, 0, 60, timeBegin) << "ֻ" << endl;
			cout << "60-120(��):" << sortday(header, 1, 60, 120, timeBegin) << "ֻ" << endl;
			cout << "120-180(��):" << sortday(header, 1, 120, 180, timeBegin) << "ֻ" << endl;
			cout << "180-240(��):" << sortday(header, 1, 180, 240, timeBegin) << "ֻ" << endl;
			cout << "240-300(��):" << sortday(header, 1, 240, 300, timeBegin) << "ֻ" << endl;
			cout << "300-365(��):" << sortday(header, 1, 300, 365, timeBegin) << "ֻ" << endl;
			cout << endl;
			cout << "С����" << endl;
			cout << "0-60(��):" << sortday(header, 2, 0, 60, timeBegin) << "ֻ" << endl;
			cout << "60-120(��):" << sortday(header, 2, 60, 120, timeBegin) << "ֻ" << endl;
			cout << "120-180(��):" << sortday(header, 2, 120, 180, timeBegin) << "ֻ" << endl;
			cout << "180-240(��):" << sortday(header, 2, 180, 240, timeBegin) << "ֻ" << endl;
			cout << "240-300(��):" << sortday(header, 2, 240, 300, timeBegin) << "ֻ" << endl;
			cout << "300-365(��):" << sortday(header, 2, 300, 365, timeBegin) << "ֻ" << endl;
			cout << endl;
			cout << "�󻨰���" << endl;
			cout << "0-60(��):" << sortday(header, 3, 0, 60, timeBegin) << "ֻ" << endl;
			cout << "60-120(��):" << sortday(header, 3, 60, 120, timeBegin) << "ֻ" << endl;
			cout << "120-180(��):" << sortday(header, 3, 120, 180, timeBegin) << "ֻ" << endl;
			cout << "180-240(��):" << sortday(header, 3, 180, 240, timeBegin) << "ֻ" << endl;
			cout << "240-300(��):" << sortday(header, 3, 240, 300, timeBegin) << "ֻ" << endl;
			cout << "300-365(��):" << sortday(header, 3, 300, 365, timeBegin) << "ֻ" << endl;
			cout << endl;
		}
		else if (order == 5) {
			outFile.open("��������ۼ�¼.txt");
			outFile << "������Ĺ��������" << endl;
			if (SS < 20) {
				for (int i = 0; i <= SS; i++) {
					outFile << "��" << i + 1 << "�ι��룺����(" << bought[i].num1 << ")��С����(" << bought[i].num2 << ")���󻨰���(" << bought[i].num3 << ")" << endl;
				}
			}
			else {
				int j = SS - 19;
				for (int i = 1; i <= 20; i++, j++) {
					outFile << "��" << i << "�ι��룺����(" << bought[j].num1 << ")��С����(" << bought[j].num2 << ")���󻨰���(" << bought[j].num3 << ")" << endl;
				}
			}
			outFile << endl;
			outFile << "����������ۼ�¼��" << endl;
			if (SS < 20) {
				for (int i = 1; i <= SS; i++) {
					outFile << "��" << i << "�γ��ۣ�����(" << sellTime[i][1] << ")��С����(" << sellTime[i][2] << ")���󻨰���(" << sellTime[i][3] << ")" << endl;
				}
			}
			else {
				int j = SS - 19;
				for (int i = 1; i <= 20; i++, j++) {
					outFile << "��" << i << "�ι��룺����(" << sellTime[j][1] << ")��С����(" << sellTime[j][2] << ")���󻨰���(" << sellTime[j][3] << ")" << endl;
				}
			}
			cout << "������Ĺ��������" << endl;
			if (SS < 20) {
				for (int i = 0; i <= SS; i++) {
					cout << "��" << i + 1 << "�ι��룺����(" << bought[i].num1 << ")��С����(" << bought[i].num2 << ")���󻨰���(" << bought[i].num3 << ")" << endl;
				}
			}
			else {
				int j = SS - 19;
				for (int i = 1; i <= 20; i++, j++) {
					cout << "��" << i << "�ι��룺����(" << bought[j].num1 << ")��С����(" << bought[j].num2 << ")���󻨰���(" << bought[j].num3 << ")" << endl;
				}
			}
			cout << endl;
			cout << "����������ۼ�¼��" << endl;
			if (SS < 20) {
				for (int i = 1; i <= SS; i++) {
					cout << "��" << i << "�γ��ۣ�����(" << sellTime[i][1] << ")��С����(" << sellTime[i][2] << ")���󻨰���(" << sellTime[i][3] << ")" << endl;
				}
			}
			else {
				int j = SS - 19;
				for (int i = 1; i <= 20; i++, j++) {
					cout << "��" << i << "�ι��룺����(" << sellTime[j][1] << ")��С����(" << sellTime[j][2] << ")���󻨰���(" << sellTime[j][3] << ")" << endl;
				}
			}
			outFile.close();
		}
		else if (order == 10) {
			cout << endl;
			printNode(header);
			cout << endl;
			printNode(sellheader);
			//�������
		}
		cout << endl << timeBetweenFirst << endl;
	}
	saveList(header);
	cout << endl << "�������";
}

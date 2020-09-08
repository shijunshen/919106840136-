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
		cout << "�б�Ϊ��";
	}
	else {
		while (postNode->home != home || postNode->variety != variety||postNode->kg!=kg) {
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
		cout << "����������Ȧ���Ϊ��"<<pmove->home << " "<<"��������Ϊ��" << pmove->variety <<" "<<"����ĵ�ǰ����Ϊ:"<<pmove->kg<<" "<<"����ı��Ϊ"<<pmove->Number<<endl;
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
	if (q)cout << endl<< "���Ϊ" << home << "����Ȧ����" << num << "ֻ��ȫΪ����"<<endl;
	else {
		cout <<endl<< "���Ϊ" << home << "����Ȧ����" << num << "ֻ��������" << q2 << "ֻС������" << q3 << "ֻ�󻨰���"<<endl;
	}
}

void printPig(struct Node* pig) {
	cout << "����Ʒ��Ϊ��" << pig->variety << endl;
	cout << "����ǰ����Ϊ��" << pig->kg << endl;
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
	if (!flag)cout << "����Ȧû�иñ�ŵ���" << endl;
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
	long timeBegin = timep;              //timeBeginΪ��ʼʱ��
	long timeFirst = timep;				 //timeFirstΪ��һ�������ĳ�ʼʱ��
	store(header,A, B, C, timeBegin,p);
	printNode(header);
	while (1) {
		if (q)cout << endl;
		q++;
		cout << "-----------------------------------------------------" << endl;
		cout << "                      ����ָ��                       " << endl;
		cout << "                      ֹͣ��0��                      " << endl;
		cout << "                     ������1��                     " << endl;
		cout << "           ��ѯ��ǰĳһ��Ȧ��������������ࣨ2��     " << endl;
		cout << "                ���㱾�γ�Ȧ����ܼۣ�3��            " << endl;
		cout << "             ��ѯĳȦĳһ��ŵ����״̬��4��         " << endl;
		cout << "               ��ѯ��ǰ�������������5��           " << endl;
		cout << "-----------------------------------------------------" << endl;
		cin >> order;
		time(&timep);
		long timeNow = timep;
		int timeBetween = timeNow - timeBegin;	 //timeBetweenΪ����ָ��ļ��ʱ��
		int timeBetweenFirst = timeNow - timeFirst;	 //timeBetweenFirstΪ����ʼ������ָ��ļ��ʱ��
		timeBegin = timeNow;
		timeNow = 0;
		tempp = SS;
		SS = timeBetweenFirst / 90;					//Ϊ�˷������
		if (SS > tempp) {
			deleteList(sellheader);
			sell(header, sellheader, timeBegin);
		}
		grow(header, timeBetween);
		int s1 = 0, s2 = 0, s21=0, s22=0, last1, last2;					//s1�����s2����Ŀǰ��ŵ�����
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
			store(header, A, B, C, timeBegin, p);
			printNode(header);
		}
		else if (order == 2) {
			int checkHome;
			cout << endl << "������Ҫ��ѯ����Ȧ���Ϊ��";
			cin >> checkHome;
			printNodeOrder(header, checkHome);
		}
		else if (order == 3) {
			if (SS == 0)cout << "��δ��ʼ����";
			else {
				cout << "��" << SS << "��:\n";
				printNode(sellheader);
				cout << endl;
				cout << price(sellheader) << endl;
			}
		}
		else if (order == 4) {
			int check1,check2;
			cout << "����������ѯ����Ȧ��ţ�";
			cin >> check1;
			cout << "����������ѯ����ı�ţ�";
			cin >> check2;
			findPig(header,check1, check2);
		}
		else if (order == 5) {
			cout << "��ǰ�����к���" << s1 << "ֻ��С����" << s21 << "ֻ���󻨰���" << s22 << "ֻ" << endl;
			cout << "���������ֲ�������£�����Ȧ��ţ���������"<<endl;
			cout << "����:"<<endl;
			for (int i = 0; i < p; i++) {
				if (pigHome[i][0].num == 0)continue;
				if (i < 10)cout << 0;
				cout << i << "��"<< pigHome[i][0].num << "��"<<" ";
			}
			cout << endl<<endl << "С����"<<endl;
			for (int i = p; i < 100; i++) {
				int UU = 0;
				for (int j = 1; j < 11; j++) {
					if (pigHome[i][j].num == 1)UU++;
				}
				if (UU == 0)continue;
				else cout << i << "��" << UU << "��" << " ";
			}
			cout << endl <<endl<< "�󻨰���"<< endl;
			for (int i = p; i < 100; i++) {
				int UU = 0;
				for (int j = 1; j < 11; j++) {
					if (pigHome[i][j].num == 2)UU++;
				}
				if (UU == 0)continue;
				else cout << i << "��" << UU << "��" << " ";
			}
			cout << endl << "���طֲ�������£������䣺������" << endl;
			cout << "����" << endl;
			cout << "20-30(kg):" << sortheavy(header, 1, 20, 30) << "ֻ"<<endl;
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
		else if (order == 10) {
			printNode(header);        //�������
			cout << endl << timeBetweenFirst << endl;			//�������
		}
	}
	printNode(header);
	cout << endl << "�������";
}

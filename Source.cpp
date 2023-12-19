#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string>
struct TienTrinh
{
	char tenTienTrinh[11];
	int AT;
	int BT;
	int WT;
};
typedef TienTrinh ItemType;
struct QueueNode
{
	ItemType Info;
	QueueNode *Next;
};
struct Queue
{
	QueueNode *Head, *Tail;
};
void initQueue(Queue &q)
{
	q.Head = q.Tail = NULL;
}
QueueNode *createQueueNode(ItemType x)
{
	QueueNode *p = new QueueNode;
	if (p == NULL)
		return NULL;
	p->Info = x;
	p->Next = NULL;
	return p;
}
int insertTail(Queue &q, QueueNode *p)
{
	if (p == NULL)
		return 0;
	if (q.Head == NULL)
		q.Head = p;
	else
		q.Tail->Next = p;
	q.Tail = p;
	return 1;
}
void nhap1TT(FILE *file, ItemType &x)
{
	fscanf(file, "%s%d%d", &x.tenTienTrinh, &x.AT, &x.BT);
}

void createQueue(Queue &q)
{
	initQueue(q);
	FILE *fi = fopen("process.txt", "rt");
	if (fi == NULL) {
		printf("Khong the mo file.\n");
		return;
	}

	int n;
	fscanf(fi, "%d\n", &n);
	ItemType x;
	for (int i = 0; i < n; i++)
	{
		nhap1TT(fi, x);
		insertTail(q, createQueueNode(x));
	}

	fclose(fi);
}

void xuat1TT(ItemType x)
{
	printf("\t%s\t\t%d\t\t%d\n", x.tenTienTrinh, x.AT, x.BT);
}
void showQueue(Queue q)
{
	printf("\n\tTen tien trinh\tThoi gian den\tThoi gian xu ly\n");
	for (QueueNode *p = q.Head; p != NULL; p = p->Next)
		xuat1TT(p->Info);
}
float tinhThoiGianHTTB(Queue gantt, Queue ganttam);
float tinhThoiGianChoTB(Queue gantt, Queue gantam);
void swap(ItemType &x, ItemType &y)
{
	ItemType t = x;
	x = y; y = t;
}
void selectionSort(Queue &q)
{
	for (QueueNode *p = q.Head; p != q.Tail; p = p->Next)
	{
		QueueNode *min = p;
		for (QueueNode *t = p->Next; t != NULL; t = t->Next)
			if (min->Info.AT>t->Info.AT)
				min = t;
		swap(min->Info, p->Info);
	}
}
QueueNode *gan(char *ten, int WT, int AT, int BT)
{
	QueueNode *p = new QueueNode;
	p->Info.AT = AT;
	p->Info.WT = WT;
	p->Info.BT = BT;
	strcpy(p->Info.tenTienTrinh, ten);
	p->Next = NULL;
	return p;
}
int deleteHead(Queue &q, ItemType &x)
{
	if (q.Head == NULL)
		return 0;
	QueueNode *p = q.Head;
	q.Head = q.Head->Next;
	if (q.Head == NULL)
		q.Tail = NULL;
	x = p->Info;
	delete  p;
	return 1;
}

void xuLy(Queue &q, Queue &gantt, int quantum)
{
	initQueue(gantt);//khoi tao rong
	Queue tmp;
	initQueue(tmp);//khoi tao rong
	int flag = 0;
	if (quantum >= q.Head->Info.BT)
		insertTail(gantt, gan(q.Head->Info.tenTienTrinh, q.Head->Info.AT, q.Head->Info.AT, q.Head->Info.BT + q.Head->Info.AT));
	else
	{
		insertTail(gantt, gan(q.Head->Info.tenTienTrinh, q.Head->Info.AT, q.Head->Info.AT, quantum + q.Head->Info.AT));
		flag = 1;
	}
	ItemType x;
	deleteHead(q, x);
	while (q.Head != NULL&&q.Head->Info.AT<gantt.Tail->Info.BT)
	{
		ItemType y;
		deleteHead(q, y);
		insertTail(tmp, createQueueNode(y));
	}
	if (flag == 1)
		insertTail(tmp, gan(x.tenTienTrinh, quantum, x.AT, x.BT - quantum));
	while (tmp.Head != NULL)
	{
		flag = 0;
		if (quantum >= tmp.Head->Info.BT)
			insertTail(gantt, gan(tmp.Head->Info.tenTienTrinh, gantt.Tail->Info.BT, tmp.Head->Info.AT, tmp.Head->Info.BT + gantt.Tail->Info.BT));
		else
		{
			insertTail(gantt, gan(tmp.Head->Info.tenTienTrinh, gantt.Tail->Info.BT, tmp.Head->Info.AT, quantum + gantt.Tail->Info.BT));
			flag = 1;
		}
		while (q.Head != NULL&&q.Head->Info.AT<gantt.Tail->Info.BT)
		{
			ItemType y;
			deleteHead(q, y);
			insertTail(tmp, createQueueNode(y));
		}
		ItemType t;
		deleteHead(tmp, t);
		if (flag == 1)
			insertTail(tmp, gan(t.tenTienTrinh, quantum, t.AT, t.BT - quantum));
	}
}
void xuat1TTgantt(ItemType x)
{
	printf("\t%s\t\t%d\t\t%d\n", x.tenTienTrinh, x.WT, x.BT - x.AT);
}
void showQueuegantt(Queue q)
{
	printf("\n\n\t\t  THOI GIAN CHO THOI GIAN HOAN THANH\n");
	printf("\tTen tien trinh\tThoi gian cho\tThoi gian hoan thanh\n");
	for (QueueNode *p = q.Head; p != NULL; p = p->Next)
		xuat1TTgantt(p->Info);
}
int tinhThoiGianCho(Queue gantt, ItemType x)
{
	QueueNode *q;
	for (QueueNode *p = gantt.Head; p != NULL; p = p->Next)
		if (strcmp(x.tenTienTrinh, p->Info.tenTienTrinh) == 0)
		{
			q = p;
			break;
		}
	int tongCho = q->Info.WT - q->Info.AT;
	for (QueueNode *p = q; p->Next != NULL; p = p->Next)
		if (strcmp(x.tenTienTrinh, p->Info.tenTienTrinh) == 0)
			for (QueueNode *t = p->Next; t != NULL; t = t->Next)
				if (strcmp(x.tenTienTrinh, t->Info.tenTienTrinh) == 0)
				{
					tongCho += t->Info.WT - p->Info.BT;
					break;
				}
	return tongCho;
}

QueueNode *tinhThoiGianHT(Queue gantt, ItemType x)
{
	QueueNode *max;
	for (QueueNode *p = gantt.Head; p != NULL; p = p->Next)
		if (strcmp(p->Info.tenTienTrinh, x.tenTienTrinh) == 0)
			max = p;
	return max;
}

void bieuDoGantt(Queue q)
{
	printf("\n\t\t\t  BIEU DO GANTT\n");
	printf("|");
	for (QueueNode *p = q.Head; p != NULL; p = p->Next)
		printf("  %s  |", p->Info.tenTienTrinh);
	printf("\n");
	printf("%d", q.Head->Info.WT);
	for (QueueNode *p = q.Head; p != NULL; p = p->Next)
		printf("%7d", p->Info.BT);
}
float tinhThoiGianChoTB(Queue gantt, Queue gantam)
{
	int dem = 0;
	int tong = 0;
	for (QueueNode *p = gantam.Head; p != NULL; p = p->Next)
	{
		dem++;
		p->Info.WT = tinhThoiGianCho(gantt, p->Info);
		tong += tinhThoiGianCho(gantt, p->Info);
	}
	return tong / (float)dem;
}
float tinhThoiGianHTTB(Queue gantt, Queue ganttam)
{
	int dem = 0;
	int tong = 0;
	for (QueueNode *p = ganttam.Head; p != NULL; p = p->Next)
	{
		dem++;
		p->Info.BT = tinhThoiGianHT(gantt, p->Info)->Info.BT;
		tong += tinhThoiGianHT(gantt, p->Info)->Info.BT - tinhThoiGianHT(gantt, p->Info)->Info.AT;
	}
	return tong / (float)dem;
}
void main()
{
	Queue q, gantt, gantam;
	createQueue(q);
	showQueue(q);
	initQueue(gantam);
	for (QueueNode *p = q.Head; p != NULL; p = p->Next)
		insertTail(gantam, createQueueNode(p->Info));
	selectionSort(q);
	int quantum;
	printf("Nhap quantum:");
	scanf("%d", &quantum);
	xuLy(q, gantt, quantum);
	bieuDoGantt(gantt);
	tinhThoiGianHTTB(gantt, gantam);
	tinhThoiGianChoTB(gantt, gantam);
	showQueuegantt(gantam);
	getch();
}




=======线性表=======
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include<string>
#include<stdlib.h>
/*----------链表----------*/
typedef struct LNode
{
	struct LNode* next;
}LinkNode;

typedef struct LinkList
{
	LinkNode head;
	int size;
}LinkList;

//两个回调函数：由程序员根据自己的数据节点，自己改写
typedef void(*PRINTNODE)(LinkNode*);
typedef int(*COMPARE)(LinkNode*, LinkNode*);

LinkList* Init_LinkList()
{
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	list->head.next = NULL;
	list->size = 0;
	return list;
}
void Free_LinkList(LinkList* list)
{
	if (list == NULL)
		return;
	free(list);  
	list = NULL;
	list->size = 0;
}
void Insert_elem(LinkList* list, int pos, LinkNode* data) {
	if (list == NULL || data == NULL)
		return;
	if (pos<0 || pos>list->size)
		pos = list->size;
	LinkNode* pCur = &(list->head); //先指向头节点
	for (int i = 0; i < pos; i++){
		pCur = pCur->next;
	}
	data->next = pCur->next;
	pCur->next = data;
	list->size++;
}
void Remove_elem(LinkList* list, int pos){
	if (list == NULL)
		return;
	if (pos<0 || pos>list->size)
		pos = list->size;
	LinkNode* pCur = &(list->head);
	for (int i = 0; i < pos; i++){
		pCur = pCur->next;
	}
	
	pCur->next = pCur->next->next;
	list->size--;
}
int Find_elem(LinkList* list, LinkNode* data, COMPARE compare){
	if (list == NULL || data == NULL)
		return -1;
	LinkNode* pCur = &(list->head);
	int pos = -1;
	for (int i = 0; i < list->size; i++, pCur = pCur->next){
		if (compare(data, pCur) == 0){//相等
			pos = i;
			break;
		}	
	}
	return pos;
}
//大小
int Size_LinkList(LinkList* list){
	if (list == NULL)
		return -1;
	return list->size;
}

void Print_LinkList(LinkList* list, PRINTNODE print){
	if (list == NULL)
		return;
	LinkNode* pCur = (list->head.next); //指向第一个有效值
	while (pCur){
		print(pCur);
		pCur = pCur->next;
	}
}

/*----------用户----------*/
typedef struct Person{//数据节点
	LinkNode node; //数据节点中第一个元素是LinkNode
	char name[64];
	int age;
}Person;

//打印
void printPerson(LinkNode* data){
	Person* p = (Person*)data;
	printf("%s,%d\n", p->name, p->age);
}
int compare(LinkNode* a, LinkNode* b){
	if (((Person*)a)->age == ((Person*)b)->age && 
		strcmp(((Person*)a)->name, ((Person*)b)->name) == 0)
		return 0;
	return -1;
}
int main(){
	LinkList* list = Init_LinkList();
	//创建数据
	Person p1, p2, p3, p4, p5;
	strcpy(p1.name, "aaaa"); p1.age = 10;
	strcpy(p2.name, "bbbb"); p2.age = 10;
	strcpy(p3.name, "cccc"); p3.age = 10;
	strcpy(p4.name, "dddd"); p4.age = 10;
	strcpy(p5.name, "eeee"); p5.age = 10;
	//插入节点
	Insert_elem(list, 0, (LinkNode*)(&p1));
	Insert_elem(list, 1, (LinkNode*)(&p2));
	Insert_elem(list, 2, (LinkNode*)(&p3));
	Insert_elem(list, 3, (LinkNode*)(&p4));
	Insert_elem(list, 4, (LinkNode*)(&p5));
	//Print_LinkList(list, printPerson);//打印
	//删除节点
	Remove_elem(list, 2);
	Print_LinkList(list, printPerson);
	//查找节点
	Person pp; strcpy(pp.name, "bbbb"); pp.age = 10;
	int ret = Find_elem(list, (LinkNode*)(&pp), compare);
	if (ret == -1)
		printf("查找失败\n");
	//释放链表内存
	Free_LinkList(list);
	system("pause");
}

 


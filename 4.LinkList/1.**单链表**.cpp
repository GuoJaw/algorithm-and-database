

#include<assert.h>
#include<iostream>
#include<stack>
#include<unordered_set> //哈希表
using namespace std;

/*
1.创建节点
2.获取中间节点
3.判环；第一个入环节点
4.两个有序链表的合并
5.链表反转
	链表局部反转
6.链表排序***
7.查找值为key的节点
8.打印两个链表的公共部分:相等，c1/c2一起后移
9.1查找倒数第K个节点
9.2删除倒数第K个节点:
	先查找倒数第K个节点的前驱，即查找倒数第K+1个节点
	删除
10.判断一个链表是否是回文***
11.复制rand指针的单链表
12.删除无序单链表中重复的节点
13.一种怪异的节点删除方式
    不给定链表的head节点指针，只给node节点指针，要求在O(1)时间复杂度内，删除node节点
 答案:
	[1]将swap(node->data,node->next->data)交换
	[2]删除node节点的后继
 存在问题:node如果是最后一个节点,无法删除
*/
typedef struct LinkNode{
	struct LinkNode* next;
	struct LinkNode* rand;
	int data;
}LinkNode;
//1.创建节点
LinkNode* createLink(){
	LinkNode* head = (LinkNode*)malloc(sizeof(LinkNode));
	head->next = NULL;
	LinkNode* ptr = head;
	int data;
	while (1){
		cout << "请输入data=";
		cin >> data;
		if (data == -1)
			break;
		//创建新节点
		LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode));
		newNode->data = data;
		newNode->next = NULL;
		//在尾部插入新节点newNode
		ptr->next = newNode;
		//ptr指针指向新的尾部节点
		ptr = newNode;
	}
	return head;
}
//2.获取中间节点
LinkNode* getMidNode(LinkNode* head){
	assert(head != NULL);
	if (head->next == NULL) //链表没有有效节点,返回NULL
		return NULL;
	//【初始化】
	LinkNode* slow = head->next;  //slow指向第一个有效节点
	LinkNode* fast = head->next->next; //fast指向第二个有效节点
	while (fast&&fast->next){
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

/*3.
判断单链表是否有环：
如果有，返回入环的第一个点
如果没有，返回NULL
*/
LinkNode* isLoop(LinkNode* head){
	assert(head != NULL);
	//【初始化】
	LinkNode* slow = head;
	LinkNode* fast = head;
	while (fast&&fast->next){
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			break;
	}
	if (slow != fast)//不相等，说明无环
		return NULL;
	//在相遇位置，使快指针指向head，之后快慢指针都一次走一步，下一次相交点就是第一个入环点
	fast = head;
	while (fast != slow){
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}
//4.有序链表的合并:将L2中的节点插入到L1中
LinkNode* mergeL1L2(LinkNode* L1, LinkNode* L2){
	assert((L1 != NULL) && (L2 != NULL));
	//初始化L1和L2的前驱节点/当前节点的指针
	LinkNode* p1 = L1; LinkNode* c1 = L1->next;
	LinkNode* p2 = L2; LinkNode* c2 = L2->next;
	while (c1 && c2){
		if (c1->data <= c2->data){
			p1 = c1; c1 = c1->next;
		}
		else{//在L1中插入L2中的c2
			//1.保存删除节点的后继
			LinkNode* tmp = c2->next;
			//2.c2插入L1
			c2->next = c1; p1->next = c2;
			//3.更新p1/c1和p2/c2
			p1 = p1->next; p2->next = tmp; c2 = tmp;
		}
	}
	if (p2 != NULL)
		p1->next = c2;
	free(L2);
	return L1;
}
//5.单链表的倒置
LinkNode* reverse(LinkNode* head){
	if (head->next == NULL) //如果没有有效节点
		return head;
	if (head->next->next == NULL)
		return head;  //只有一个有效节点
	//【初始化】
	LinkNode* pre = head->next;
	LinkNode* cur = head->next->next; //cur指向第二个有效节点
	while (cur != NULL){
		LinkNode* last = cur->next;//1.保存cur的后继，防止断链
		cur->next = pre;//2.cur反指向pre
		pre = cur; cur = last; //3.后移cur和pre: 更新pre和cur
	}
	head->next->next = NULL;
	head->next = pre;
	return head;
}
//扩展：链表的局部反转——[from,to]
LinkNode* searchPre(LinkNode* head, LinkNode* node){ //查找node的前驱
	if (head == NULL || node == NULL)
		return NULL;
	LinkNode* cur = head->next;
	LinkNode* pre = head;
	while (cur != NULL){
		if (cur != node){
			pre = cur;
			cur = cur->next;
		}
		else
			return pre;
	}
	return NULL;
}
void reversePart(LinkNode*& head, LinkNode* from, LinkNode* to){
	if (head == NULL || from == NULL || to == NULL || from >= to)
		return;
	LinkNode* pre_from = searchPre(head, from);//1.查找from的前驱
	if (pre_from == NULL) //如果没找到from，则直接返回，不做任何处理
		return;
	LinkNode* last_to = to->next; //2.查找to的后继
	//3.反转局部链表[from,to]
	LinkNode* pre = from;
	LinkNode* cur = from->next;
	while (cur != last_to){
		LinkNode* last = cur->next;
		cur->next = pre;//反指
		pre = cur; cur = last;
	}
	//4.重新连接
	pre_from->next->next = last_to; //pre_from->next指向last_to
	pre_from->next = to;//pre_from指向to
}
//6.单链表排序
//LinkNode* sortLinkNode(LinkNode* head){
//	assert(head != NULL);
//	//排序
//
//}
//7.查找
LinkNode* searchData(LinkNode* head, int key){
	assert(head != NULL);
	LinkNode* cur = head->next; //指向第一个节点
	while (cur){
		if (cur->data == key){
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//8.打印两个链表的公共部分
void printCommonPart(LinkNode* L1, LinkNode* L2){
	assert((L1 != NULL) && (L2 != NULL));
	LinkNode* c1 = L1; LinkNode* c2 = L2;
	while (c1 != NULL&&c2 != NULL){ //如果相等，c1/c2都后移
		if (c1->data == c2->data){
			c1 = c1->next; c2 = c2->next;
			cout << c1->data << "  ";
		}
		else if (c1->data < c2->data) //如果不等，小的后移
			c1 = c1->next;
		else
			c2 = c2->next;
	}
}
//9.1查找倒数第K个节点
LinkNode* GetLastKthNode(LinkNode* head, int lastKth){
	if (head == NULL || head->next == NULL || lastKth <= 0)
		return NULL;
	LinkNode* p = head;
	LinkNode* q = head;
	while (p && lastKth > 0){
		p = p->next;
		lastKth--;
	}
	if (lastKth > 0)
		return NULL;
	while (p){
		p = p->next;
		q = q->next;
	}
	return q;
}
//9.2删除倒数第K个节点
void RemoveLastKthNode(LinkNode* head, int lastKth){
	//查找倒数第K+1个节点的位置(即倒数第K个节点的前驱)
	LinkNode* pre = GetLastKthNode(head, lastKth + 1);
	if (!pre) //如果没找到
		return;
	LinkNode* deleteNode = pre->next;
	//删除deleteNode
	pre->next = deleteNode->next; delete(deleteNode); deleteNode = NULL;
}
//10.判断链表是否为回文:O(N)  O(N/2)  O(1)
//方法1：空间复杂度O(N)
bool isPlalindrome1(LinkNode* head){
	assert(head != NULL);
	if (head->next == NULL)
		return true;

	stack<LinkNode*> S;
	LinkNode* cur = head->next;
	while (cur != NULL){ //1.将链表的有效节点依次入栈
		S.push(cur);
		cur = cur->next;
	}
	cur = head->next;//重置cur
	while (!S.empty()){ //如果栈不空
		LinkNode* topNode = S.top();
		//2.判断（获取栈顶元素==cur）
		if (topNode->data != cur->data) //如果有一个不同，就不是回文
			return false;
		S.pop(); cur = cur->next;
	}
	return true;
}
//方法2：空间复杂度O(N/2)
bool isPlalindrome2(LinkNode* head){
	assert(head != NULL);
	if (head->next == NULL)
		return true;
	LinkNode* slow = head->next;
	LinkNode* fast = head->next->next;
	//1.寻找第中间节点slow
	while (fast&&fast->next){
		fast = fast->next->next;
		slow = slow->next->next;
	}
	stack<int> S; //2.将链表的右半部分入栈
	while (slow){
		S.push(slow->data);
		slow = slow->next;
	}
	fast = head->next; //fast指向head->next
	//3.（将栈中元素）依次与（链表左半部分元素）比对
	while (!S.empty()){
		if (S.top() != fast->data)
			return false;
		S.pop(); fast = fast->next;//比对下一个元素
	}
	return true;
}
/*
方法3：
1-->2-->3-->2-->1    1-->2-->2-->1
1-->2-->3<--2<--1    1-->2<--2<--1
*/

//11.复制rand指针的单链表
// head-->1-->2-->3-->4-->null
// head-->1-->1'-->2-->2'-->3-->3'-->4-->4'-->null
// [return] 1'-->2'-->3'-->4'-->null
LinkNode* CopyRandLink(LinkNode* head){
	if (head == NULL || head->next == NULL)
		return head;
	//1.第一次遍历：拷贝每个节点
	LinkNode* cur = head->next;
	while (cur != NULL){
		//(1)创建新节点
		LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode));
		newNode->data = cur->data; newNode->rand = NULL;
		//(2)插入新节点
		newNode->next = cur->next; cur->next = newNode;
		//(3)后移
		cur = cur->next->next;
	}
	//2.第二次遍历：复制rand指针域
	cur = head->next;
	while (cur != NULL){
		//拷贝rand指针域的指向：注意rand是NULL的情况
		cur->next->rand = (cur->rand == NULL) ? (NULL) : cur->rand->next;
		cur = cur->next->next;//向后遍历
	}
	//3.第三次遍历：拆分
	cur = head->next;    LinkNode* ret = cur->next;
	while (cur != NULL){
		LinkNode* tmp = cur->next; //保存
		cur = cur->next->next;
		tmp->next = (cur == NULL) ? NULL : cur->next;//注意cur==NULL的情况
	}
	return ret;
}
//12.删除无序链表中重复的值1-->2-->3-->3-->4-->2-->1-->null
/*方法1：类似于插入排序——时间复杂度O(N*N)，空间复杂度O(1)
首先检查第一个有效节点1；然后向后依次遍历值为1的节点，删除
检查第二个有效节点2；然后向后依次遍历值为2的节点，删除
...
*/
//方法2：哈希表——时间复杂度O(N),空间复杂度O(N)
void RemoveRep(LinkNode*& head){
	if (head == NULL || head->next == NULL)
		return;
	unordered_set<int> set;
	set.insert(head->next->data);  //将第一个值放入哈希表

	LinkNode* pre = head->next;
	LinkNode* cur = head->next->next;
	while (cur != NULL){
		unordered_set<int>::iterator iter = set.find(cur->data);
		if (iter == set.end()) {//哈希表中没有,不删除（直接后移）
			set.insert(cur->data); //cur->data插入哈希表
			pre = cur; cur = cur->next;
		}
		else{ //哈希表中有,删除cur
			LinkNode* tmp = cur;
			pre->next = pre->next->next; free(tmp);
			cur = pre->next;
		}
	}
}
void RemoveValue(LinkNode*& head, int num){
	if (head == NULL || head->next == NULL)
		return;
	LinkNode* pre = head;
	LinkNode* cur = head->next;
	while (cur != NULL){
		if (cur->data == num){
			LinkNode* tmp = cur;
			pre->next = pre->next->next; free(tmp);
			cur = pre->next;
		}
		else{
			pre = cur; cur = cur->next;
		}
	}
}
//遍历
void travel(LinkNode* head){
	LinkNode* cur = head->next;//cur指向第一个有效节点
	while (cur){
		cout << cur->data << "  ";
		cur = cur->next;
	}
	system("pause");
}

void test01(){//查找中间节点
	LinkNode* head = createLink();
	LinkNode* mid = getMidNode(head);
	head = reverse(head);
	travel(head);
	system("pause");
}
void test02(){  //环形单链表
	LinkNode* head = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* node1 = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* node2 = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* node3 = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* node4 = (LinkNode*)malloc(sizeof(LinkNode));
	head->next = node1;
	node1->next = node2; node1->data = 1;
	node2->next = node3; node2->data = 2;
	node3->next = node4; node3->data = 3;
	node4->next = node3; node4->data = 4;

	LinkNode* ret = isLoop(head);
	if (ret != NULL)
		printf("%d\n", ret->data);

	system("pause");
}
void test03(){ //有序表的合并
	LinkNode* L1 = createLink();
	LinkNode* L2 = createLink();
	LinkNode* L3 = mergeL1L2(L1, L2);
	travel(L3);
}
void test04(){ //删除节点
	LinkNode* L1 = createLink();
	RemoveLastKthNode(L1, 3);
	travel(L1);
}
void test05(){  //查找
	LinkNode* head = createLink();
	LinkNode* ret = searchData(head, 10);
	if (ret == NULL)
		cout << "没查找到" << endl;
	else
		cout << ret->data << endl;
	system("pause");
}
void test06(){ //链表局部反转
	LinkNode* head = createLink();
	LinkNode* from = head->next->next;
	LinkNode* to = from->next->next->next;
	reversePart(head, from, to);
	travel(head);
}
void test07(){
	LinkNode* head = createLink();
	bool ret1 = isPlalindrome1(head);
	bool ret2 = isPlalindrome2(head);
}
void test08(){  //复制带有rand指针的链表
	LinkNode* head = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* node1 = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* node2 = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* node3 = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* node4 = (LinkNode*)malloc(sizeof(LinkNode));
	head->next = node1;
	node1->next = node2; node1->rand = node3; node1->data = 1;
	node2->next = node3; node2->rand = node1; node2->data = 2;
	node3->next = node4; node3->rand = node1; node3->data = 3;
	node4->next = NULL; node4->rand = NULL; node4->data = 4;

	LinkNode* ret = CopyRandLink(head);
	system("pause");
}
void test09(){ //无序单链表的去重
	LinkNode* head = createLink();
	RemoveRep(head);
	travel(head);
}
void test10(){
	LinkNode* head = createLink();
	RemoveValue(head, 10);
	travel(head);
}

int main(){
	test04();
}

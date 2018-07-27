#include<assert.h>
#include<iostream>
#include<string>
using namespace std;
/*
1.字符串倒置
2.I am from shanghai-->shanghai from am I
3.strstr
4.atoi:存在前后为空格（两头堵）
5.字符串拷贝：strcpy和memcpy
6.循环后移:考察API的使用
*/
void swap(char& a, char& b){
	a ^= b;
	b ^= a;
	a ^= b;
}
//1.字符串倒置
void myReverse1(char* str){
	char* r = str + strlen(str) - 1;
	char* l = str;
	while (l < r){
		swap(*l++, *r--);
	}
}
void myReverse2(char* start, char* end){
	while (start < end){
		swap(*start++, *end--);
	}
}
//2.I am from shanghai-->shanghai from am I
void myReverse3(char* src){
	assert(src != NULL);
	//字符串整个反转
	myReverse1(src);

	char* start = src;//记录start
	while (*src++ != '\0'){ 
		if (*src == ' ' || *src == '\0'){//查找到end的后继
			char* end = src - 1;
			myReverse2(start, end);
			start = src + 1; //更新start
		}
	}
}
//3.strstr
char* mystrstr(char* str, char* sub){
	assert((str != NULL) && (sub != NULL));
	while (*str++ != '\0'){
		char* ptr_str = str; //每查一个节点
		char* ptr_sub = sub;
		//就要进行比较是否相等
		do{
			if (*ptr_sub == '\0')
				return str; //返回第一次查到的首节点
		} while (*ptr_str++ == *ptr_sub++);
	}
	return NULL; //没有查到
}
//4.atoi:存在前后为空格（两头堵）
/*
(1)去除两段的' '
(2)判断左面第一个元素是否为符号:+和-
(3)从左到右，一次取出每个值，再计算:num = num * 10 + (*ch - '0');
*/
int myatoi(char* src){  
	assert(src != NULL);
	char* start = src;
	char* end = src + strlen(src) - 1;
	//去除两端的空格
	while (*start++ == ' '); start--; //查找左边起第一个不为' '的元素位置:需要回退一个start--
	while (*end-- == ' '); end++;
	//判断第一个字符是否有符号
	bool flag; //flag=true表示正数
	switch (*start){
	case '-':
		flag = false; start++; break;
	case '+':
		flag = true; start++; break;
	default:
		flag = true;
	}
	const char* ch = start;
	int num = 0;
	while (ch != end + 1){
		num = num * 10 + (*ch - '0');
		ch++;
	}
	if (flag != true)
		return -num;
	return num;
}
//5.字符串拷贝：strcpy和memcpy
char* mystrcpy(char* dst, const char* src){
	assert((dst != NULL) && (src != NULL));
	char* tmp = dst; //备份dst
	while ((*dst++ = *src++) != '\0');
	return tmp; //链式调用
}
void* mymemcpy(void* dst, const void* src, size_t size){
	assert((dst != NULL) && (src != NULL));
	//先保存起始指针
	char* tmp_dst = (char*)dst;
	char* tmp_src = (char*)src;
	while (size--){
		*tmp_dst++ = *tmp_src++;
	}
	return dst;
}
//6.循环后移:考察API的使用
void loopstep(char* src,int steps){
	assert(src);
	int len = strlen(src) - steps;
	char buf[1024] = { '\0' };
	memcpy(buf, src + len, steps);
	memcpy(src + steps, src, len);
	memcpy(src, buf, steps);
}

void test01(){
	char A[] = "I am from shanghai   ";
	myReverse3(A);
	cout << A << endl;
	system("pause");
}
void test02(){
	char A[] = "I am from shanghai";
	loopstep(A, 5);
	cout << A << endl;
	system("pause");
}
void test03(){
	char* ret = mystrstr("I am from shanghai", "hai");
	if (ret != NULL)
		cout << ret << endl;
	else
		cout << "查找substr失败" << endl;
	system("pause");
}
void test04(){
	char A[] = "   -123456   ";
	int num = myatoi(A);
}
int main(){
	test04();
}

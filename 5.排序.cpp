//排序

#include<iostream>
using namespace std;
#define STRLEN(A) (sizeof((A))/sizeof((A[0])))
//二分查找
int binarySearch(int A[], int n, int key){
	int left = 0, right = n - 1;
	while (left <= right){ // <=
		int mid = (left + right) / 2;
		if (A[mid] == key)
			return mid;
		else if (A[mid]>key)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}
void swap(int& a, int& b){
	a ^= b; b ^= a; a ^= b;
}
//冒泡排序
void bubbleSort(int A[], int n){
	for (int i = 0; i < n - 1; i++){ //进行n-1趟排序
		bool flag = false;//记录该趟是否发生了交换
		for (int j = 0; j < n - 1 - i; j++){
			if (A[j] > A[j + 1]){ //前一个数>后一个数，就交换
				swap(A[j], A[j + 1]);
				flag = true;
			}
		}
		if (flag == false)//如果没有发生交换，说明已经有序，直接退出
			break;
	}
}
//选择排序
void selectSort(int A[], int n){
	for (int i = 0; i < n - 1; i++){ //进行n-1趟
		int min = i;//先将i设为最小值
		for (int j = i + 1; j < n; j++){//从A[i,n)选出最小值
			if (A[min]>A[j])
				min = j;
		}
		if (min != i) 
			swap(A[min], A[i]);
	}
}
/*直接插入排序
(1)确定待插入元素位置:[1,n-1]
(2)将A[i]插入到A[0]~A[i-1]位置
	[1]tmp保存待插入元素
	[2]寻找插入位置&&越界判断，后移
	[3]插入
*/
void insertSort(int A[], int n){
	int j;
	for (int i = 1; i < n; i++){//将A[i]插入有序序列A[1]，A[2]，...，A[N-1]中
		if (A[i - 1]>A[i]){ //如果逆序
			int tmp = A[i];//[1]保存待插元素A[i]
			for (j = i - 1; j >= 0 && A[j] > tmp; j--)//[2]后移
				A[j + 1] = A[j];
			A[j+1] = tmp;//[3]插入
		}
	}
}
//折半插入排序
void binary_insert_sort(int A[], int n){
	for (int i = 1; i < n; i++){//待插入元素A[1]~A[n-1]
		//寻找插入位置：left或right+1
		int left = 0, right = i - 1;
		while (left <= right){
			int mid = (left + right) / 2;
			if (A[mid] < A[i])
				left = mid + 1;
			else
				right = mid - 1;
		}
		//保存待插入元素
		int tmp = A[i];
		//后移
		for (int j = i - 1; j>=left; j--)
			A[j + 1] = A[j];
		//插入
		A[left] = tmp;
	}
}

/*
快速排序：分治策略
（1）至少有两个数，才进行（quick_sort快速排序，partition划分操作）因此，
		条件分别是：if( l < r ) ， while( l < r )
（2）partition划分操作：先从右到左，寻找第一个小于pivot的值A[r] ----> 执行A[l] = A[r]
（3）partition划分操作的返回值是： A[l] = pivot;     return l ;
*/
int partition(int A[], int l, int r){
	int pivot = A[l]; //基准
	while (l < r){
		while (l < r && pivot <= A[r])//从右到左
			r--;
		A[l] = A[r];
		while (l < r && A[l] <= pivot)//从左到右
			l++;
		A[r] = A[l];
	}
	A[l] = pivot;
	return l;
}
void quick_sort(int A[], int l, int r){
	if (l < r){//至少两个数，才进行快排
		int pivot = partition(A, l, r);
		quick_sort(A, l, pivot - 1);
		quick_sort(A, pivot + 1, r);
	}
}

void printA(int A[], int n){
	for (int i = 0; i < n; i++)
		cout << A[i] << "   ";
	cout << endl;
}
void test01(){
	int A[] = { 1, 2, 4, 3, 1, 7, 9, 8 };
	int len = STRLEN(A);
	binary_insert_sort(A, len);
	printA(A, len);
}
void test02(){
	int A[] = { 1, 2, 4, 3, 1, 7, 9, 8 };
	int len = STRLEN(A);
	quick_sort(A, 0, len-1);/*这里原文第三个参数要减1否则内存越界*/
	printA(A, len);
}
int main()
{
	test02();
	system("pause");
}

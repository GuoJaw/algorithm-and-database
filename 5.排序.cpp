//排序

#include<iostream>
using namespace std;
#define STRLEN(A) (sizeof((A))/sizeof((A[0])))

void swap(int& a, int& b){
	a ^= b; b ^= a; a ^= b;
}
void bubble_sort(int A[], int n){
	for (int i = 0; i < n - 1; i++){//进行n-1趟
		bool flag = false;//标记该趟是否发生了交换
		for (int j = 0; j < n - 1 - i; j++){//每趟确定一个最大值末尾(终端)
			if (A[j]>A[j + 1]){
				swap(A[j], A[j + 1]);
				flag = true;
			}
		}
		if (flag == false)
			break;
	}
}
void select_sort(int A[], int n){
	for (int i = 0; i < n - 1; i++){//进行n-1趟
		int min = i;
		for (int j = i + 1; j < n; j++){
			if (A[min]>A[j])
				min = j;
		}
		if (min != i)//当min不等于初始的i，说明min发生变化-->交换
			swap(A[min], A[i]);
	}
}
int binary_search(int A[], int n, int key){//二分查找
	int l = 0, r = n - 1;
	while (l <= r){
		int mid = (l + r) / 2;
		if (A[mid] = key)
			return mid;
		else if (A[mid] > key)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return -1; //没查找到
}
void insert_sort(int A[], int n){
	int j;
	for (int i = 1; i < n; i++){//待插元素[1,n-1]
		if (A[i] < A[i - 1]){ //将A[i]插入到(有序的[0,i-1]中)
			int tmp = A[i]; //记录A[i]
			for (j = i - 1; j >= 0 && A[j]>tmp; j--)//寻找插入位置，并后移
				A[j + 1] = A[j];
			//查找到插入位置为j+1
			A[j + 1] = tmp;
		}
	}
}
void binary_insert_sort(int A[], int n){
	for (int i = 1; i < n; i++){//待插元素[1,n-1]
		//查找插入位置:l
		int l = 0, r = i - 1;
		while (l <= r){
			int mid = (l + r) / 2;
			if (A[mid]<A[i])
				l = mid + 1;
			else
				r = mid - 1;
		}
		//保存带插入元素
		int tmp = A[i];
		for (int j = i - 1; j >= l; j--)//后移
			A[j + 1] = A[j];
		A[l] = tmp;
	}
}
//快速排序
int partition(int A[], int l, int r){
	int pivot = A[l]; //将第一个元素设为基准
	while (l < r){
		while (l < r&&pivot <= A[r])
			r--;
		A[l] = A[r];

		while (l < r&&pivot >= A[l])
			l++;
		A[r] = A[l];
	}
	A[l] = pivot;
	return l;
}
void quick_sort(int A[], int l, int r){
	if (l < r){
		int pivot = partition(A, l, r);
		quick_sort(A, l, pivot - 1);
		quick_sort(A, pivot + 1, r);
	}
}
//归并排序
void merge(int Arr[], int L, int mid, int R){
	int* help = new int[R - L + 1]; //辅助数组
	int i = L;
	int p1 = L, p2 = mid + 1;
	while (p1 <= mid && p2 <= R){ //谁小填谁
		help[i++] = Arr[p1] < Arr[p2] ? Arr[p1++] : Arr[p2++];
	}
	//两个必然有且只有一个越界
	while (p1 <= mid){
		help[i++] = Arr[p1++];
	}
	while (p2 <= R){
		help[i++] = Arr[p2++];
	}
	//将help数组，拷贝会Arr
	for (int i = L; i <= R; i++)
		Arr[i] = help[i];

}
void merge_sort(int Arr[], int L, int R){ //思想:分而治之
	if (L < R){
		int mid = (L + R) / 2; //int mid = L+(R-L)/2=L+((R-L)>>1);
		merge_sort(Arr, L, mid);//先左边排好序:T(n/2)
		merge_sort(Arr, mid + 1, R);//再右边排好序:T(n/2)
		merge(Arr, L, mid, R);//将两个有序数组[L,mid][mid+1,R]合并:T(n)
	}
}

void printA(int A[], int n){
	for (int i = 0; i < n; i++)
		cout << A[i] << "   ";
	cout << endl;
}

void test02(){//归并排序
	int A[] = { -10, -2, 40, 3, 1, 17, 19, 81 };
	int len = STRLEN(A);
	merge_sort(A, 0, len-1);
	printA(A, len);
}
void test03(){//快速排序
	int A[] = { 1, 2, 4, 3, 1, 7, 9, 8 };
	int len = STRLEN(A);
	quick_sort(A, 0, len-1); 
	printA(A, len);
}
int main()
{
	test02();
	system("pause");
}

//排序

#include<iostream>
#include<time.h>
using namespace std;
void printA(int A[], int n){
	for (int i = 0; i < n; i++)
		cout << A[i] << "   ";
	cout << endl;
}
void swap(int* data, int i, int j){ //交换数组中的两个元素
	if (i == j) 
		return;
	data[i] ^= data[j];
	data[j] ^= data[i];
	data[i] ^= data[j];
}

void bubble_sort(int A[], int n){
	for (int i = 0; i < n - 1; i++){//进行n-1趟
		bool flag = false;//标记该趟是否发生了交换
		for (int j = 0; j < n - 1 - i; j++){//每趟确定一个最大值末尾(终端)
			if (A[j]>A[j + 1]){
				swap(A, j, j + 1);
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
			swap(A, min, i);
	}
}
int binary_search(int A[], int n, int key){//二分查找
	int l = 0, r = n - 1;
	while (l <= r){
		int mid = (l + r) / 2;
		if (A[mid] == key)
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
//快速排序：长期期望
/*时间复杂度分析：
	最差情况O(N*N)：有序
	最好情况O(N*logN)：每次patition，基准都划分在中间
空间复杂度：
	最差情况O(N)：有序
	最好情况O(logN)
*/

快速排序：
	设立基准pivot=A[l]
	用A[r]和A[l]与基准pivot进行比较
	A[l]=pivot; return l;

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
void quick_sort(int A[], int l, int r){ //快速排序
	if (l < r){
		int pivot = partition(A, l, r);
		quick_sort(A, l, pivot - 1);
		quick_sort(A, pivot + 1, r);
	}
}
void rand_quick_sort(int A[], int l, int r){ //随机快速排序
	if (l < r){
		//随机获取基准下标
		srand(time(NULL)); //1.获取[l,r]中的随机数k
		int k = rand() % (r - l + 1) + l; 
		swap(A, l, k); //2.将A[k]与A[l]交换

		//快速排序
		int pivot = partition(A, l, r);
		quick_sort(A, l, pivot - 1);
		quick_sort(A, pivot + 1, r);
	}
}
//归并排序
/*时间复杂度分析：T[n]  =  2T[n/2] + O(n)；
	最好情况O(N*logN)
空间复杂度：临时的数组
	最差情况O(N)：有序
*/
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

void test01(){//归并排序
	int A[] = { -10, -2, 40, 3, 1, 17, 19, 81 };
	int len = sizeof(A) / sizeof(A[0]);
	merge_sort(A, 0, len - 1);
	printA(A, len);
}
void test02(){//随机快速排序
	int A[] = { 1,3,5,6,2,4,9,10 };
	int len = sizeof(A) / sizeof(A[0]);
	rand_quick_sort(A, 0, len - 1);
	printA(A, len);
}
int main()
{
	test02();
	system("pause");
}

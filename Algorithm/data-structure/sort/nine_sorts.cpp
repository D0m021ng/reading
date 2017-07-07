#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;

#define MAXN 10000005
int a[MAXN], b[MAXN];

/***********************************************************
 *  插入排序：内部排序、稳定排序
 *  分析：平均时间复杂度：O(n^2)，最坏时间复杂度：O(n^2)
 *  @param a[] 未排序数组
 *	@param n   数组长度
 ************************************************************
 */
void Insertion_Sort(int a[], int n){
	int i, j;	
	for(i = 1; i < n; ++i){
		j = i - 1;
		int key = a[i];
		while(j >= 0 && a[j] > key){
			a[j+1] = a[j];
			--j;
		}
		a[j+1] = key;	
	}
}

/***********************************************************
 *  希尔排序：插入排序的更高效改进版本，也叫递减增量排序
 *            内部排序、不稳定排序
 *  分析：平均时间复杂度：O(n*logn*logn)，最坏时间复杂度：
 *        O(n^2)
 *  @param a[] 未排序数组
 *  @param n   数组长度
 ************************************************************
 */
void Shell_Sort(int a[], int n){

    for(int step = n >> 1; step > 0; step >>= 1){
        for(int i = step; i < n; ++i){
            int key = a[i];
            int j = i -step;
            for(; j >= 0 && a[j] > key; j -= step)
                a[j + step] = a[j];
            a[j + step] = key;
        }
    }
}

/*************************************************************
 *  冒泡排序：内部排序、稳定排序
 *  分析：平均时间复杂度：O(n^2)，最坏时间复杂度：O(n^2)
 *  @param a[] 未排序数组
 *	@param n   数组长度
 *************************************************************
 */
void Bubble_Sort(int a[], int n){
	int i, j, t;
	// i表示冒泡的轮数
	for(i = 0; i < n; ++i){
		// 每一轮有n-i个数比较
		for(j = n - 1 ; j > i; --j){
			if(a[j-1] > a[j]){
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}
}

/*************************************************************
 *  双向冒泡排序：内部排序、稳定排序
 *  分析：平均时间复杂度：O(n^2)，最坏时间复杂度：O(n^2)
 *  @param a[] 未排序数组
 *  @param n   数组长度
 *************************************************************
 */
void Bidirectional_Bubble_Sort(int a[], int n){
    int left = 0, right = n-1;
    int lastSwapLeft = left, lastSwapRight = right;

    while(left < right){
        // 从左到右
        lastSwapRight = 0;
        for(int i = left; i < right; ++i)
            if(a[i] > a[i+1]){
                swap(a[i], a[i+1]);
                lastSwapRight = i;
            }
        right = lastSwapRight;

        // 从右到左
        lastSwapLeft = n - 1;
        for(int j = right; j > left; j--)
            if(a[j] < a[j-1]){
                swap(a[j], a[j-1]);
                lastSwapLeft = j;
            }
        left = lastSwapLeft;
    }
}

/*************************************************************
 *  选择排序：内部排序、不稳定排序
 *  分析：平均时间复杂度：O(n^2)，最坏时间复杂度：O(n^2)
 *  @param a[] 未排序数组
 *	@param n   数组长度
 *************************************************************
 */
void Selection_Sort(int a[], int n){

    for(int i = 0; i < n; ++i){
        int min = i;
        for(int j = i+1; j < n; ++j){
            if(a[min] > a[j])
                min = j;
        }
        int t = a[min];
        a[min] = a[i];
        a[i] = t;
    }
}

/************************************************************
 *  快速排序：内部排序、不稳定排序
 *  分析：平均时间复杂度：O(n*logn)，最坏时间复杂度：O(n^2)
 *  @param a[] 未排序数组
 *	@param n   数组长度
 ************************************************************
 */
void Quick_Sort(int a[], int left, int right){
    
    if(left < right){
        int low = left, high = right, key = a[low];

        while(low < high){
            while(low < high && a[high] >= key)
                --high;
            a[low] = a[high];
            while(low < high && a[low] < key)
                ++low;
            a[high] = a[low];
        }
        a[low] = key;
        Quick_Sort(a, left, low-1);
        Quick_Sort(a, low+1, right);
    }
}

/************************************************************
 *  堆排序之最大堆调整： 堆元素修改之后，保持最大堆特性
 *  思路： 用数组存储堆；找到该堆节点的左，右子节点；若子节
 *        点比堆节点大，则交换子节点和堆节点数值，然后调整；
 *        依次下去。
 *  @param a[]       最大堆数组
 *	@param n         堆元素
 *	@param heapsize  堆的大小
 ************************************************************
 */
void MaxHeap_Adjust(int a[], int idx, int heapsize){
    
	int lchild = 2*idx+1, rchild = 2*(idx+1);
	int max = idx;
		
	if(lchild < heapsize && a[lchild] > a[max]){
		max = lchild;
	}
	if(rchild < heapsize && a[rchild] > a[max]){
		max = rchild;
	}
			
	if(max != idx){
		swap(a[idx], a[max]);
		MaxHeap_Adjust(a, max, heapsize);	
	}	
}

/**********************************************************************
 *  堆排序之创建最大堆： 在未排序的数组上创建最大堆
 *  思路： 在未排序的数组上，从堆低向上调用最大堆调整函数，进行调整；
 *         由于数组是从0开始计数，所以最大堆最后一层父节点为n/2-1）；
 *         对于父节点为i，左子节点为2*i+1，右子节点为2*(i+1)。
 *  @param a[]    未排序数组
 *	@param n      数组大小
 **********************************************************************	
 */
void Build_MaxHeap(int a[], int n){
	int iparent = n / 2 - 1;
	for(; iparent >= 0; --iparent){
		MaxHeap_Adjust(a, iparent, n);
	}
}

/**********************************************************************
 *  堆排序：内部排序、不稳定排序
 *  思路： 先用未排序数组创建最大堆，然后将最大堆首元素取出（最大元素
 *         和堆最后一个元素交换），并调整最大堆。
 *  分析：平均时间复杂度：O(n*logn)，最坏时间复杂度：O(n*logn)
 *  @param a[] 未排序数组
 *	@param n   数组长度
 **********************************************************************
 */
void Heap_Sort(int a[], int n){
    Build_MaxHeap(a, n);

    for(int i = n-1; i > 0; --i){
    	swap(a[0], a[i]);
    	MaxHeap_Adjust(a, 0, i);
    }
}

/**********************************************************************
 *  归并排序之合并操作： 将两个有序序列合并成一个有序序列
 *  @param a[]    未排序数组
 *	@param left   第一个有序序列，最小值下标
 *	@param mid    第一个有序序列，最大值下标
 *	@param right  第二个有序序列，最大值下标
 **********************************************************************
 */
int tmp[MAXN];
void Merge(int a[], int left, int mid, int right){

    int i = left, j = mid+1, k = 0;

    while(i <= mid && j <= right){
        if(a[i] <= a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }

    while(i <= mid)
        tmp[k++] = a[i++];

    while(j <= right)
        tmp[k++] = a[j++];

    for(i = 0; i < k; i++)
        a[left+i] = tmp[i];
}

/**********************************************************************
 *  归并排序： 二路内部排序、稳定排序
 *  思路： 使用分治的思想，将n个数看成n个长度为1的有序序列，然后两两
 *         合并有序序列；依次类推，直到2个长度为n/2的有序序列合并
 *  分析：平均时间复杂度：O(n*logn)，最坏时间复杂度：O(n*logn)
 *  @param a[]    未排序数组
 *	@param left   最左边元素下标
 *	@param right  最右边元素下标
 **********************************************************************
 */
void Merge_Sort(int a[], int left, int right){
    if(left < right){
        int mid = (left + right) / 2;
        Merge_Sort(a, left, mid);
        Merge_Sort(a, mid+1, right);

        Merge(a, left, mid, right);
    }
}

/**********************************************************************
 *  计数排序： 外部排序、稳定排序
 *  思路： 初始化一个计数数组，大小是待排序数组中最大的数k，统计待
 *         排序数组中数出现的次数；遍历计数数组，对于每个数x，确定
 *         小于等于x的数个数；根据这一信息，将x放在输出数组中
 *  分析： 平均时间复杂度：O(n+k)，最坏时间复杂度：O(n+k)       
 *  @param a[]  未排序数组 
 *  @param n    数组元素个数 
 *  @param K    最大元素限制
 **********************************************************************
 */
// int B[MAXN];
void Counting_Sort(int a[], int n){
	int K = a[0];
 	for(int i = 1; i < n; ++i)
 		if(K < a[i])
 			K = a[i];

    int *Count = new int[K+1];
    // int *B = new int[n];

    memset(Count, 0, (K+1)*sizeof(int));
    // 数组a的副本
    memcpy(tmp, a, n*sizeof(int));
    for(int i = 0; i < n; ++i)
        ++Count[a[i]];
    for(int i = 1; i <= K; ++i)
        Count[i] += Count[i-1];

    for(int i = n-1; i >= 0; --i){
        // 数组中a[i]排序后在a中第C[tmp[i]]位，由于数组从零开始，故需减1
        a[Count[tmp[i]]-1] = tmp[i];
        Count[tmp[i]]--;
    }
}

/***********************************************************************
 *  基数排序： 外部排序、稳定排序
 *  思路： 先找到未排序数组中最大的数，计算最大的数位数k；
 *         将未排序数组中的数按照个位上数字放入编号为0-9的桶中，然后
 *         将按照桶编号0-9依次取出桶中元素；以此类推，十位、百位...，
 *         直到最大的数位数。
 *  分析： 平均时间复杂度：O(n*k)，最坏时间复杂度：O(n*k)       
 *  @param a[]  未排序数组 
 *  @param n    数组元素个数 
 *********************************************************************** 
 */
void Radix_Sort(int a[], int n){
    vector<int> bucket[10];
    
    int PosCount = 0;
    int max = a[0];
    for(int i = 1; i < n; ++i)
        if(max < a[i]){
            max = a[i];
        }
    while(max){
        max /= 10;
        ++PosCount;
    }

    int log = 1;
    for(int j = 0; j < PosCount; ++j){
        for(int i = 0; i < n; ++i){
            int tk = (a[i]/log) % 10;
            bucket[tk].push_back(a[i]);
        }
        
        int k = 0;
        for(int i = 0; i < 10; ++i){
            for(auto &t : bucket[i]){
              a[k++] = t;    
            }
            bucket[i].clear();
        }
        log *= 10;            
    }
}

/***********************************************************************
 *  桶排序： 外部排序、稳定排序
 *  分析： 平均时间复杂度：O(n)，最坏时间复杂度：O(n*logn)       
 *  @param a[]  未排序数组 
 *  @param n    数组元素个数 
 *********************************************************************** 
 */
 void Bucket_Sort(int a[], int n){
 	int max = a[0];
 	for(int i = 1; i < n; ++i)
 		if(max < a[i])
 			max = a[i];

 	int *Bucket = new int[max+1];
 	memset(Bucket, 0, (max+1)*sizeof(int));
 	for(int i = 0; i < n; ++i)
 		++Bucket[a[i]];
 	
 	int k = 0;
 	for(int i = 0; i <= max; ++i)
 		for(int j = 1; j <= Bucket[i]; ++j)
 			a[k++] = i;
 }

void print_a(int a[], int n){
	
	for(int i = 0; i < n; ++i){
		cout << a[i] << " ";
	}
	cout << endl;
}

void verify_a(int a[], int n){

	bool flag = true;
	for(int i = 1; i < n; ++i)
		if(a[i] < a[i-1]){
			flag = false;
			break;
		}

	if(flag)
		cout << "Sort Correct!\n";
	else
		cout << "ERROR!\n";				
}

int main(){
	
	int n;
	clock_t tbegin, tend;
	cout << "CLOCKS_PER_SEC = " << CLOCKS_PER_SEC << endl;
    fstream fin("input");
	while(fin >> n){
		int i;
		for(i = 0; i < n; ++i)
			fin >> a[i];
        cout << "待排序数个数: " << i;
        // print_a(a, n);
        cout << "\n内部排序时间：" << endl;
        
		// 1. 插入排序
        memcpy(b, a, sizeof(a));
        tbegin = clock();
		Insertion_Sort(b, n);
		tend = clock();
		cout << "1. 插入排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
		// verify_a(b, n);

        // 1. 希尔排序
        memcpy(b, a, sizeof(a));
        tbegin = clock();
        Shell_Sort(b, n);
        tend = clock();
        cout << "1. 希尔排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
        // verify_a(b, n);
        // print_a(b, n);

		// 2. 冒泡排序
        memcpy(b, a, sizeof(a));
        tbegin = clock();
		Bubble_Sort(b, n);
		tend = clock();
		cout << "2. 冒泡排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
		// verify_a(b, n);
		// print_a(b, n);

        // 2. 双向冒泡排序
        // memcpy(b, a, sizeof(a));
        // tbegin = clock();
        // Bidirectional_Bubble_Sort(b, n);
        // tend = clock();
        // cout << "2. 双向冒泡: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
        // verify_a(b, n);
        // print_a(b, n);

        // 3. 选择排序
        memcpy(b, a, sizeof(a));
        tbegin = clock();
        Selection_Sort(b, n);
        tend = clock();
        cout << "3. 选择排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
        // verify_a(b, n);
        // print_a(b, n);

        // 4. 快速排序
        memcpy(b, a, sizeof(a));
	    tbegin = clock();	
		Quick_Sort(b, 0, n-1);
		tend = clock();
		cout << "4. 快速排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
		// verify_a(b, n);
        // print_a(b, n);

		// 5. 堆排序
        memcpy(b, a, sizeof(a));
  		tbegin = clock();		
		Heap_Sort(b, n);
		tend = clock();
		cout << "5.   堆排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
		// verify_a(b, n);
		// print_a(b, n);
    
        cout << "\n外部排序时间：" << endl;
        // 6. 归并排序
        memcpy(b, a, sizeof(a));
        tbegin = clock();
        Merge_Sort(b, 0, n-1);
        tend = clock();
        cout << "6. 归并排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
        // verify_a(b, n);
        // print_a(b, n);

        // 7. 计数排序
        memcpy(b, a, sizeof(a));
        tbegin = clock();
		Counting_Sort(b, n);
		tend = clock(); 
		cout << "7. 计数排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
		// verify_a(b, n);  
        // print_a(b, n);

		// 8. 基数排序
        memcpy(b, a, sizeof(a));
        tbegin = clock();
		Radix_Sort(b, n);
		tend = clock();
		cout << "8. 基数排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s." << endl;
		// verify_a(b, n);  
		// print_a(b, n);

        // 9. 桶排序
        memcpy(b, a, sizeof(a));
        tbegin = clock();
        Bucket_Sort(b, n);
        tend = clock(); 
        cout << "9.   桶排序: " << (double)(tend-tbegin)/CLOCKS_PER_SEC << " s."<< endl;  
        // verify_a(b, n);
        // print_a(b, n);
        cout << "END!\n\n\n";
                
        
	}

	return 0;
}

/**
CLOCKS_PER_SEC = 1000000
待排序数个数: 10000
内部排序时间：
1. 插入排序: 0.062881 s.
1. 希尔排序: 0.001844 s.
2. 冒泡排序: 0.231324 s.
2. 双向冒泡: 0.3005 s.
3. 选择排序: 0.107489 s.
4. 快速排序: 0.001177 s.
5.   堆排序: 0.002618 s.

外部排序时间：
6. 归并排序: 0.001331 s.
7. 计数排序: 0.000348 s.
8. 基数排序: 0.001293 s.
9.   桶排序: 0.000406 s.
END!


待排序数个数: 100000
内部排序时间：
1. 插入排序: 5.96642 s.
1. 希尔排序: 0.02941 s.
2. 冒泡排序: 27.0253 s.
2. 双向冒泡: 29.9797 s.
3. 选择排序: 10.655 s.
4. 快速排序: 0.014149 s.
5.   堆排序: 0.036905 s.

外部排序时间：
6. 归并排序: 0.017924 s.
7. 计数排序: 0.001329 s.
8. 基数排序: 0.013806 s.
9.   桶排序: 0.001496 s.
END!

*/


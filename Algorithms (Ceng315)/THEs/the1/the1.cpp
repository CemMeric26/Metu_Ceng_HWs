#include "the1.h"
#include <climits>


//You can add your own helper functions

void insertionSort(int* arr, long &comparison, long & swap, int size) 
{
    

    int key,j;

    
    for(int i=1;i<size;i++)
    {
        key = arr[i];
        j = i-1;
        
        while(j>=0 && arr[j]>key)
        {
        
            arr[j+1] = arr[j];
            j--;
            swap++;
        }
        
        arr[j+1]= key;
     
    }
    comparison = size + swap -1;
    
    
    
}

//swap function
void swap(int & a, int & b)
{
    int temp = a;
    a = b;
    b = temp;
}

//heapifying child-parent nodes
void heapify(int* arr, int n, int i, long& comparison,long& s1)
{
	int s = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	if (l < n && arr[l] < arr[s])
	{
		s = l;comparison++;
	}
		


	//right is smallest
	if (r < n && arr[r] < arr[s])
		{s = r;comparison++;}

	//not root
	if (s != i) 
	{
		swap(arr[i], arr[s]);
		s1++;

		heapify(arr, n, s,comparison,s1);
	}
}

//creating the heapified array
void createHeap(int* arr, int n,long& comparison,long& s1)
{

    int start = (n/ 2) - 1;

    for (int i = start; i >= 0; i--) {
        heapify(arr, n, i,comparison,s1);
    }
}

int PartitionHelper(int* arr,int K,int size,long& comparison,long& swap,int& calls,int start)
{
    if(size<K)
    {
        insertionSort(arr,comparison,swap,size);
        
    }
    else
    {
        int sub_size = size /K; //subsize of the partition
        
        for(int j=0;j<K;j++)
        {
            PartitionHelper(arr+start,K,sub_size,comparison,swap,++calls,start); // the part that will be sorted determined by arr+start and size f the partitiın
            start += sub_size; //sliding the pointer
        }
    }
    
    return calls;
}




void MergeHelper(int* arr,int K,int size, long& comparison, long& swap)
{
    
    int start_index=0;
    int sub_size = size/K;
    int heap_arr[sub_size];
    int* index_arr[K];
	int* end_parts[K];
    int sorted_Arr[size];
    //int* flag=nullptr;
	
    //int par_arr[K];
    
    //creating the heap array
    for(int i=0;i<K;i++)
    {
        heap_arr[i]=arr[start_index]; //taking the partitions first index to the heap array
        
        start_index +=sub_size;
        //index_arr[i]= sub_size*i;  //indexes of the partitions beginning
        
        index_arr[i] = &arr[start_index];  //pointers pointing to the partitions
		end_parts[i] = &arr[start_index+sub_size-1];
    }
    
    
    
    for(int j=0;j<size;j++)
    {
        createHeap(heap_arr,K,comparison,swap);  //heapifying the heap array 
         
        sorted_Arr[j]=heap_arr[0]; //recording smallest element in the heap array
        

		//inserting new element to heap
        for(int k=0;k<K;k++)
        {
			//if condition checks the partion group of the root eleement
            if(heap_arr[0] == *(index_arr[k]))
            {
				//if partition goup pointer is not in the end of the partition insert the foloowing partition element to the heap array
				if(index_arr[k] != end_parts[k])
				{
					(index_arr[k])++;
					heap_arr[0] = *(index_arr[k]);
					break;
				}
				//if pointer points to the end of the partition insert INT_mAx to the heap_array
				else if(index_arr[k]==end_parts[k])
				{
					heap_arr[0]=INT_MAX;
					break;
				}
				else
				{
					;
				}
	
			}
			
        }
     
    }
    
	for(int w=0;w<size;w++)
	{
		arr[w]=sorted_Arr[w];
	}
    
}



int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap){
  
  int number_of_calls = 1;
	
	//Your code here
	
	//int* sorted_Arr;
	int calls=0;
	comparison=0;swap=0;
	
	//If the size of the array is less than K, then sort the array by using insertion sort
	calls = PartitionHelper(arr,K,size,comparison,swap,calls,0);
	MergeHelper(arr,K,size,comparison,swap);
	number_of_calls += calls;
	
	
	
	return number_of_calls;
}


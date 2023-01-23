#include "the2.h"
#include <cmath>
// You may write your own helper functions here

//helper function for getting the max element of the array
int getMax(int* arr, int n) 
{
  int max = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > max)
      max = arr[i];
  return max;
}

void countSortAsc(int* arr, int Arrsize, int groupSize,int place,int maxDigit,long& iterations)
{
    int out[Arrsize];
    int count_size=pow(10,groupSize);
    //int place = pow(10,groupSize); // number of digits
    int counts[count_size] = {0} ;
    
    //count of the elements putting them to the count array
    for(int i=0;i<Arrsize;i++)
    {
        counts[(arr[i]/place)%count_size]++; 
        iterations++;
    }
    
    //collecting the numbers in count array
    for(int i=1;i<count_size;i++)
    {
        counts[i] += counts[i-1];
        iterations++;
    }
    
    //sorting the elements into actual array
    for(int i = Arrsize-1;i >= 0;i--)
    {
        out[ --counts[(arr[i]/place)%count_size] ] = arr[i];
        iterations++;
    }
    
    for(int i =0;i<Arrsize;i++)
    {
        arr[i] = out[i];
        iterations++;
        
    }
}

void countSortDesc(int* arr, int Arrsize, int groupSize,int maxDigit)
{
    
    ;
}



long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength){
    long numberOfIterations = 0;
    
    int max = getMax(arr, arraySize); //max number in the array
    int check=-1,start=0,end=arraySize-1;
    
    for (int place = 1; max / place > 0; place *= pow(10,groupSize))
        {
            check++;
            if(maxDigitLength-check*groupSize<groupSize)
            {
                groupSize = maxDigitLength-check*groupSize;
               
                countSortAsc(arr,arraySize,groupSize,place,maxDigitLength,numberOfIterations);
                break;
                
            }
            else
            {
                countSortAsc(arr,arraySize,groupSize,place,maxDigitLength,numberOfIterations);
            }
        }
        
    if(!ascending)
    {
        while (start < end)
        {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }  
    }
    
    
    
    
    
    return numberOfIterations;
}
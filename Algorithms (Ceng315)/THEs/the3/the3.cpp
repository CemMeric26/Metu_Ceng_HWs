#include "the3.h"



int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) { //direct recursive
    number_of_calls+=1;

    //your code here
    int res;
    
    if(i==0)
    {
        return len[0];
        
    }
    
    else
    {
        
        
        
        if(number_of_calls==1)//N == size-1
        { 
            
            int val1=0,val2=0;
            for(int k=i-1;k>=0;k--)
            {
                
                if((arr[i][0]=='S' && arr[k][1]=='S') || (arr[i][0]=='I' && arr[k][1]=='O') || (arr[i][0]=='O' && arr[k][1]=='I')) //start(N) end(i) check
                {
                   
                    //val1=fmax(recursive_sln(k,arr,len,number_of_calls),recursive_sln(k,arr,len,number_of_calls)+len[i]);
                    val1=recursive_sln(k,arr,len,number_of_calls)+len[i];
                    
                    break;
                    
                } 
                
                
            }
            
            //val2=fmax(val1,recursive_sln(i-1,arr,len,number_of_calls));
            
            for(int j=i-1;j>=0;j--)
            {
                val1=fmax(val1,recursive_sln(j,arr,len,number_of_calls));
                
                
            }
            
            res=val1;
            
            
            return res;
            
            
            
            
        }
        
        else   // N != size-1
        {
            int val1=0,val2=len[i];
            int i_1,i_2;
            
            for(int j=i-1;j>=0;j--)
            {
                
                
                if((arr[i][0]=='S' && arr[j][1]=='S') || (arr[i][0]=='I' && arr[j][1]=='O') || (arr[i][0]=='O' && arr[j][1]=='I')) 
                {
                    //i_1=j;
                    val1 = recursive_sln(j,arr,len,number_of_calls)+len[i];
                    break;
                    
                } 
                
                
            }
            
            //val1 = recursive_sln(i_1,arr,len,number_of_calls)+len[i];
            
            for(int j=i-1;j>=0;j--)
            {
                if(arr[i][1]==arr[j][1])  //equals to end(j)
                {
                    //i_2=j;
                    val2=recursive_sln(j,arr,len,number_of_calls);
                    break;
                }
            }
            //val2=recursive_sln(i_2,arr,len,number_of_calls);
            
            res=fmax(val1,val2);
            
            return res;
            
        }
        
    }
    
    
    
    
    
    
    return 0; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int memoization_sln(int i, char**& arr, int*& len, int**& mem) { //memoization

    //your code here
    
    
    
    
    
    
    
    
    
    

    return 0; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int dp_sln(int size, char**& arr, int*& len, int**& mem) { //dynamic programming

    //your code here
    
    for(int i=0;i<size;i++)
    {
        mem[i][0] = 0;
        mem[i][1] = 0;
        mem[i][2] = 0;
    }
    
    switch(arr[0][1]) {
      case 'I':
        mem[0][0]=len[0];
        break;
      case 'O':
        mem[0][1]=len[0];
        break;
      default:
        mem[0][2]=len[0];
    }
    
    for(int i=1;i<size;i++)
    {
        if(arr[i][0]=='I') //starts with I
        {
            // I-I STICK
            if(arr[i][1]=='I') //ends with I
            { 
                 if(mem[i-1][0]<mem[i-1][1]+len[i]) //one before ends with O  arr[i-1][1]=='O'
                 {
                     
                     mem[i][0] = mem[i-1][1]+len[i]; //len[i]+mem[i-1][1]; //length of current stick and previous addition
                     mem[i][1] = mem[i-1][1];
                     mem[i][2] = mem[i-1][2];
                 }
                 else
                 {
                     if(len[i]>mem[i-1][0])  //if cuurent sticks I length is bigger update it
                     {
                         mem[i][0]=len[i];
                         mem[i][1] = mem[i-1][1];
                        mem[i][2] = mem[i-1][2];
                     }
                     else
                     {
                         mem[i][0]=mem[i-1][0];
                         mem[i][1] = mem[i-1][1];
                        mem[i][2] = mem[i-1][2];
                     }
                 }
            }
            
            //I-O STICK
            else if(arr[i][1]=='O') //ends with O
            {
                if(mem[i-1][1]<len[i]+mem[i-1][1]) //arr[i-1][1]=='O'
                 {
                     mem[i][1] = len[i]+mem[i-1][1];
                     mem[i][0] = mem[i-1][0];
                     mem[i][2] = mem[i-1][2];
                 }
                 else
                 {
                     if(len[i]>mem[i-1][1])  
                     {
                         mem[i][1]=len[i];
                         mem[i][0] = mem[i-1][0];
                        mem[i][2] = mem[i-1][2];
                     }
                     else
                     {
                         mem[i][1]=mem[i-1][1];
                         mem[i][0] = mem[i-1][0];
                        mem[i][2] = mem[i-1][2];
                     }
                 }
                
                
            }
            
            //I-S STICK
            else // ends with S
            {
                if(mem[i-1][2]<len[i]+mem[i-1][1]) //arr[i-1][1]=='O'
                 {
                     mem[i][2] =  len[i]+mem[i-1][1];//len[i]+mem[i-1][1];
                     mem[i][1] = mem[i-1][1];
                     mem[i][0] = mem[i-1][0];
                 }
                 
                 else
                 
                 {
                     if(len[i]>mem[i-1][2])
                     {
                         mem[i][2]=len[i];
                         mem[i][1] = mem[i-1][1];
                     mem[i][0] = mem[i-1][0];
                     }
                     else
                     {
                         mem[i][2]=mem[i-1][2];
                         mem[i][1] = mem[i-1][1];
                     mem[i][0] = mem[i-1][0];
                     }
                 }
                 
            }
            
        }
        
        else if(arr[i][0]=='O') //stick starts with O
        {
             if(arr[i][1]=='I')  //stick ends with I
             {
                 if(mem[i-1][0]<len[i]+mem[i-1][0]) //arr[i-1][1]=='I'
                 {
                     mem[i][0] = len[i]+mem[i-1][0];
                     mem[i][1] = mem[i-1][1];
                     mem[i][2]=mem[i-1][2];
                 }
                 
                 else
                 {
                     if(len[i]>mem[i-1][0])
                     {
                         mem[i][0]=len[i];
                         mem[i][1] = mem[i-1][1];
                     mem[i][2]=mem[i-1][2];
                     }
                     else
                     {
                         mem[i][0]=mem[i-1][0];
                         mem[i][1] = mem[i-1][1];
                     mem[i][2]=mem[i-1][2];
                     }
                 }
             }
             
             else if(arr[i][1]=='O') //stick ends with O
            {
                 if(mem[i-1][1]<len[i]+mem[i-1][0]) //arr[i-1][1]=='I'
                 {
                     mem[i][1] = len[i]+mem[i-1][0];
                     mem[i][0]=mem[i-1][0];
                     mem[i][2] = mem[i-1][2];
                 }
                 
                 else
                 
                 {
                     if(len[i]>mem[i-1][1])
                     {
                         mem[i][1]=len[i];
                         mem[i][0]=mem[i-1][0];
                     mem[i][2] = mem[i-1][2];
                     }
                     else
                     {
                          mem[i][1]=mem[i-1][1];
                          mem[i][0]=mem[i-1][0];
                     mem[i][2] = mem[i-1][2];
                     }
                 }   
            }
                
            else //ends with s the stick
            {
                if(mem[i-1][2]<mem[i-1][0]+len[i]) //arr[i-1][1]=='I'   //original
                 {
                     mem[i][2] = mem[i-1][0]+len[i];//len[i]+mem[i-1][0];
                     mem[i][0]=mem[i-1][0];
                     mem[i][1]=mem[i-1][1];
                 }
                 
                 else
                 {
                     if(len[i]>mem[i-1][2])
                     {
                         mem[i][2]=len[i];
                         mem[i][0]=mem[i-1][0];
                     mem[i][1]=mem[i-1][1];
                     }
                     else
                     {
                         mem[i][2]=mem[i-1][2];
                         mem[i][0]=mem[i-1][0];
                     mem[i][1]=mem[i-1][1];
                     }
                 }
            }
        }
        
        else //starts with 'S'
        {
            if(arr[i][1]=='I') // ends with I
            {
                if(mem[i-1][0]<len[i]+mem[i-1][2]) //one before ends with S arr[i-1][1]=='S' so I have to check that if the previous memory value could be greater than the new value I should change it
                {
                    mem[i][0] = len[i]+mem[i-1][2];
                    mem[i][1] = mem[i-1][1];
                    mem[i][2]=mem[i-1][2];
                }
                else
                {
                    if(len[i]>mem[i-1][0])
                    {
                        mem[i][0] = len[i];
                        mem[i][1] = mem[i-1][1];
                    mem[i][2]=mem[i-1][2];
                    }
                    else
                    {
                        mem[i][0] = mem[i-1][0];
                        mem[i][1] = mem[i-1][1];
                    mem[i][2]=mem[i-1][2];
                    }
                }
            }
            
            
            else if(arr[i][1]=='O') //ends with O
            {
                if(mem[i-1][1]<len[i]+mem[i-1][2]) //one before ends with S arr[i-1][1]=='S'
                {
                    mem[i][1] = len[i]+mem[i-1][2];
                    mem[i][0] = mem[i-1][0];
                    mem[i][2]=mem[i-1][2];
                }
                else
                {
                    if(len[i]>mem[i-1][1])
                    {
                        mem[i][1]=len[i];
                        mem[i][0] = mem[i-1][0];
                    mem[i][2]=mem[i-1][2];
                    }
                    else
                    {
                        mem[i][1]=mem[i-1][1];
                        mem[i][0] = mem[i-1][0];
                    mem[i][2]=mem[i-1][2];
                    }
                }
            }
            
            
            else //ends with S
            {
                if(mem[i-1][2]<len[i]+mem[i-1][2]) //one before ends with S arr[i-1][1]=='S'
                {
                    mem[i][2]=len[i]+mem[i-1][2];
                    mem[i][0] = mem[i-1][0];
                    mem[i][1] = mem[i-1][1];
                }
                else
                {
                    if(len[i]>mem[i][2])
                    {
                        mem[i][2]=len[i];
                        mem[i][0] = mem[i-1][0];
                    mem[i][1] = mem[i-1][1];
                    }
                    else
                    {
                        mem[i][2]=mem[i][2]; 
                        mem[i][0] = mem[i-1][0];
                    mem[i][1] = mem[i-1][1];
                    }
                    
                }
            }
            
        }
        
    }
    
    int res;
    int val1=mem[size-1][0];
    int val2=mem[size-1][1];
    int val3=mem[size-1][2];
    
    res = fmax(val1,val3);
    res = fmax(res,val2);
    
    
    
    
    

    return res; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}


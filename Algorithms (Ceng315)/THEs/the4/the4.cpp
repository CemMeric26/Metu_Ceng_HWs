#include "the4.h"



int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem){ //dynamic programming

    //your code here
    
    mem[0][0]=0;
    int cost2=0;
    for(int j=1;j<ncol2+1;j++) //filling the i=0 j row -- Conversion of no columns of box1 to first J column of box2
    {
        
        for(int k=0;k<nrow;k++) //checking box2 elements
        {
            if(arr2[k][j-1]!='-')
                cost2++;
        }
        mem[0][j]=cost2;
    }
    
    int cost1=0;
    for(int i=1;i<ncol1+1;i++) //conversion of no columns of box2 to no columns of box1
    {
        for(int k=0;k<nrow;k++) //checking box1 elements
        {
            if(arr1[k][i-1]!='-')
                cost1++;
        }
        mem[i][0]=cost1;
    }
    
    
    //filling memoziation table according to rules
    for(int i=1;i<ncol1+1;i++)
    {
        for(int j=1;j<ncol2+1;j++)
        {
            int cost_u=0,cost_l=0,cost_d=0,cost_r=INT_MAX;
            
            //checking upper mem_cell of the current cell (2,3) -> (3,3)
            //should check arr2's j'th column
            cost_u = mem[i][0]-mem[i-1][0];
            
            
            //checking left mem_cell of the current cell
            cost_l=mem[0][j]-mem[0][j-1];
            
            cost_u += mem[i-1][j];
            cost_l += mem[i][j-1];
            
            
            //checking the diagonal of the current cell
            
            char arr1_ith[nrow];
            char arr1_ith_ordered[nrow];
            char arr2_jth[nrow];
            char arr2_jth_ordered[nrow];
            
             //construct box1's col_i
            for(int k=0;k<nrow;k++)
            {
                arr1_ith[k]=arr1[k][i-1];
                arr1_ith_ordered[k]=arr1[k][i-1]; //will be used in ordering op
                
            }
            
            
            
            //construct box2's col_j
            for(int k=0;k<nrow;k++)
            {
                arr2_jth[k]=arr2[k][j-1];
                arr2_jth_ordered[k] = arr2[k][j-1]; //will be used in order op
                
            }
            
            
            
            //replacement option checking by columns box1 and box2
            for(int k=0;k<nrow;k++)
            {
                if(arr1_ith[k]==arr2_jth[k])
                {
                    ;
                }
                else if(arr1_ith[k]=='-' || arr2_jth[k] == '-')
                {
                    cost_d+=2;
                    
                }
                else
                {
                    cost_d++;
                }
            }
            
            
            
            //REORDERING OPERATION
            
            //first ordering two box columns to check if the columns have same elements
            
            int a,key,b,key2;
            
            //ordering the column of box1
            for(a=1;a<nrow;a++)
            {
                key=arr1_ith_ordered[a];
                b=a-1;
                
                while(b>=0 && arr1_ith_ordered[b]>key)
                {
                    arr1_ith_ordered[b+1] = arr1_ith_ordered[b];
                    b=b-1;
                }
                arr1_ith_ordered[b+1] = key;
            }
            
            
            //ordering the column of the box2
             for(a=1;a<nrow;a++)
            {
                key2=arr2_jth_ordered[a];
                b=a-1;
                
                while(b>=0 && arr2_jth_ordered[b]>key2)
                {
                    arr2_jth_ordered[b+1] = arr2_jth_ordered[b];
                    b=b-1;
                }
                arr2_jth_ordered[b+1] = key2;
            }
            
            //checking two ordered box columns 
            int flag=1;
            for(int x=0;x<nrow;x++)
            {
                if(arr2_jth_ordered[x]!=arr1_ith_ordered[x])
                {
                    flag=0;break;
                }

            }
            
            
            //this means columns have to be reordered because they have the same elements
            if(flag!=0)
            {
                
                cost_r=0;
                for(int q=0;q<nrow;q++)
                {
                    if(arr1_ith[q]!=arr2_jth[q])
                    {
                        cost_r++;
                    }
                }
                
                cost_r += mem[i-1][j-1] ; //adding diagonal mem_cell cost to the reordering operation cost
            }
            
            
            
            
            
            cost_d += mem[i-1][j-1] ; //adding diagonal mem_cell cost to the replcae operation cost
            
            
            //checking min of the replcae and reorder operation
            int cost_dig;
            cost_dig = cost_d<cost_r ? cost_d: cost_r;
            
            //putting cost of the converting first i'th column of box1 
            //to first j'th column of the box2
            int cost_s; 
            
            
            // check value between left and upper
            cost_s=cost_u  <cost_l ? cost_u : cost_l; 
            
            //should check cost_d with cost_s Don't forget;
            
            
            mem[i][j]= cost_dig < cost_s ? cost_dig : cost_s ; //comparing the three operation costs and taking the minimum of them
        }
    }
    
        

    return mem[ncol1][ncol2]; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}


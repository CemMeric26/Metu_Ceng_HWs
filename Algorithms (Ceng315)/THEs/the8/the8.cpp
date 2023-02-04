#include "the8.h"

//DO NOT ADD OTHER LIBRARIES
#define CHAR_NO 256
using namespace std;






void comp_finite_auto(const std::string& pattern, int m, int finite_table[][CHAR_NO])
{
    int y=0;
    
    
    //filling first row
    for(int j =0;j<CHAR_NO;j++)
    {
        finite_table[0][j] = 0;
    }
    
    int x = pattern[0];
    
    finite_table[0][x] = 1;
    
    //filling the rest of the rows
    for(int i = 1; i<=m; i++ )
    {
        //copying values from yth row
        for(int j=0;j<CHAR_NO;j++)
        {
            finite_table[i][j] = finite_table[y][j];
        }
        
        //updating the entry in pattern i
        x = pattern[i];
        finite_table[i][x] = i+1;
        
        //updating y value for the next yth row
        if(i<m)
        {
            x = pattern[i];
            y = finite_table[y][x];
        }
    }
    
}


/*
void pattern_search(const std::string& sequence, const std::string& pattern)
{
    int m = pattern.length();
    int n = sequence.length();
    
    int finite_table[m+1][CHAR_NO];
    
    comp_finite_auto(pattern,m,finite_table);
    
    int x,j = 0;
    vector<int> result;
    int res;
    for(int i=0; i < n; i++ )
    {
        x=sequence[i];
        j = finite_table[j][x];
        if(j==m)
        {
            //std::cout << i - m + 1 << " ";
            res = i-m+1;
            result.push_back(res);
        }
    }
    
    int size=result.size();
    
    if(size==0)
    {
        cout<<"NONE";
    }
    else
    {
        for(int i=0;i<size-1;i++)
        {
            cout<<result[i]<<" ";
        }
        cout<<result[size-1];
    }
    
    
    
}
*/

//***********************************************

void pattern_search2(const std::string& sequence, const std::string& pattern, std::pair<std::string,std::string> mapping)
{
    string mapped_pattern;
    
    for(char c : pattern)
    {
        
        if(c == mapping.first[0])
        {
            mapped_pattern += mapping.second[0];
        }
        else
        {
            mapped_pattern += c;
            
        }
    }
    
    string mapped_sequence;
    for(char c : sequence)
    {
        
        if(c == mapping.first[0])
        {
            mapped_sequence += mapping.second[0];
        }
        else
        {
            mapped_sequence += c;
            
        }
    }
    
    int m = mapped_pattern.length();
    int n = mapped_sequence.length();
    
    //cout<<mapped_sequence<<"\n";
    //cout<<mapped_pattern<<"\n";
    
    int finite_table[m+1][CHAR_NO];
    
    comp_finite_auto(mapped_pattern,m,finite_table);
    
    int x,j = 0;
    vector<int> result;
    int res;
    for(int i=0; i < n; i++ )
    {
        x=mapped_sequence[i];
        j = finite_table[j][x];
        if(j==m)
        {
            //std::cout << i - m + 1 << " ";
            res = i-m+1;
            result.push_back(res);
        }
    }
    
    int size=result.size();
    
    if(size==0)
    {
        cout<<"NONE";
    }
    else
    {
        for(int i=0;i<size-1;i++)
        {
            cout<<result[i]<<" ";
        }
        cout<<result[size-1];
    }
    
}



void matchPattern(const std::string& sequence, const std::pair<std::string,std::string> mapping, const std::string& pattern){


    /*******
     *
     * 
     * YOU SHOULD PRINT THE STARTING INDEX OF EACH MATCH 
     * IN THE SAME LINE, SEPARATED BY A SINGLE SPACE
     * 
     * IF THERE IS NO MATCH, YOU SHOULD PRINT "NONE"
     *
     * *****/
     pattern_search2(sequence,pattern,mapping);


     
     
}



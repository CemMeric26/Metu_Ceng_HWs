#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    // TODO
    int i;
    int hash=0;
    for(i=0;i<key.length();i++)
    {
        hash += key[i]*PRIME_LIST[i];
        
    }
    
    hash = hash % tableSize;
    
    return hash;
}

void KeyedHashTable::ReHash()
{
    // TODO
    int old_size=tableSize;
    int occup=occupiedElementCount;
    
    HashData *old = new HashData[occup];
    
    int ind=0;
    for(int i=0;i<old_size;i++)
    {
        if(table[i].key != "")
        {
            old[ind].key= table[i].key;
            old[ind].intArray=table[i].intArray;
            ind++;
        }
        
    }
 
    
    
    delete [] table;
    table=NULL; 
    
    
    occupiedElementCount=0;
    
   
    tableSize = FindNearestLargerPrime(2*tableSize);
    
    table = new HashData[tableSize];
    
    for(int k=0;k<occup;k++)
    {
        
        Insert(old[k].key,old[k].intArray);
        
    }
    
    delete [] old; old=NULL;

}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    // TODO
    int i;
    
    for(i=0;i<PRIME_TABLE_COUNT;i++)
    {
        if(PRIME_LIST[i]>requestedCapacity )
        {
            return PRIME_LIST[i];
        }
    }
}

KeyedHashTable::KeyedHashTable()
{
    // TODO
    this->table = new HashData[2];
    
    
    tableSize=2;

    occupiedElementCount=0;
    
    
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    // TODO
    int i= FindNearestLargerPrime(requestedCapacity);
    
    this->table = new HashData[i];
    tableSize=i;
    occupiedElementCount=0;
    
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    // TODO
    
    if(other.table==NULL)
    {
        table=NULL;
        occupiedElementCount=0;
        tableSize=0;
    }

    else
    {
        
 
            table = new HashData[other.tableSize];
            tableSize=other.tableSize;
            
            for(int j=0;j<other.tableSize;j++)
            {
                table[j].key = (other.table[j]).key;
                table[j].intArray= other.table[j].intArray;
            }
            occupiedElementCount=other.occupiedElementCount;
    
      
    }
    
   
    
    
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    // TODO
    if(other.table==NULL)
    {
        table=NULL;
    }
    else
    {
        if(this != &other)
        {
            this-> ~KeyedHashTable(); 
            
            table = new HashData[other.tableSize];
            tableSize=other.tableSize;
            
            for(int j=0;j<other.tableSize;j++)
            {
                table[j].key = (other.table[j]).key;
                table[j].intArray= other.table[j].intArray;
            }
            occupiedElementCount=other.occupiedElementCount;
        }
       
            
        
    }
    
}

KeyedHashTable::~KeyedHashTable()
{
    // TODO

    delete [] table;
    table=NULL;
    
    
    tableSize=0;

    occupiedElementCount=0;
    
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    // TODO
    
    
    
    
    int h=Hash(key);int old_h=h;
    int i=0;
    while(table[h].key != "" && table[h].key != key &&table[h].key!= "__DELETED__" )
    {
        h=old_h;
        h = (h + (i*i)) % tableSize;
        i++;
        
    }
    
    if(table[h].key== key)
    {
        return false;
    }
    
    if(table[h].key != key)
    {
        table[h].key=key;
        table[h].intArray=intArray;
        occupiedElementCount++;
        if(occupiedElementCount * EXPAND_THRESHOLD >= tableSize)
        {
            ReHash();
        
        }
        return true;
    }
    
    return false;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    // TODO
    //use _DELETED_ don't forget it
    
    int h=Hash(key);int old_h=h;
    int i=0;
    while(table[h].key != "" && table[h].key != key)
    {
        h=old_h;
        h = (h + (i*i)) % tableSize;
        i++;
        
    }
    
    if(table[h].key== key)
    {
        table[h].key="__DELETED__" ;
        table[h].intArray.clear();
    }

    
    
    
}

void KeyedHashTable::ClearTable()
{
   // TODO
   for(int i=0;i<tableSize;i++)
   {
       table[i].key="";
       table[i].intArray.clear();
   }
   occupiedElementCount=0;
   
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    // TODO
    
    int h=Hash(key);int old_h=h;
    int i=0;
    while(table[h].key != "" && table[h].key != key && table[h].key != "__DELETED__" )
    {
        h=old_h;
        h = (h + (i*i)) % tableSize;
        i++;
        
    }
    
    if(table[h].key== key)
    {
        valueOut=table[h].intArray;
        return true;
    }
    
    return false;
    
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}
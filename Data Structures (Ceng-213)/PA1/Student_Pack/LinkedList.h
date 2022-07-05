#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() 
{
    /* TODO */
    head = NULL;
    size=0;
  
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) 
{
    /* TODO */ 
    
  
  if(obj.getFirstNode() == NULL)
  {
    head =NULL;
  }
  else
  {
    head = new Node<T>(obj.getFirstNode()->data);
    Node<T> *curr = head;
    Node<T> *tmp = head;
    Node<T> *obj_curr = obj.getFirstNode();
    
    
    while(obj_curr->next != obj.getFirstNode())
    {
      curr->next = new Node<T>(obj_curr->next->data);
      obj_curr = obj_curr->next;
      curr = curr->next;
      curr->prev = tmp;
      tmp = tmp->next;
    }
    
        curr->next=head;
        head->prev=curr;
    
    }

    size=obj.getSize();
    


}

template<class T>
LinkedList<T>::~LinkedList() 
{
    
   int i=0;
  Node<T> *tmp = NULL;
  if(head)
  {
 
      while(i<size)
      {
        tmp = head;
        head = head->next;
        delete tmp;i++;
        }
  } 
    size=0;tmp=NULL;
    head=NULL;
    
}

template<class T>
int LinkedList<T>::getSize() const 
{
    
    return size;
    
}

template<class T>
bool LinkedList<T>::isEmpty() const 
{
    
    if(head==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const 
{
    /* TODO */
    Node <T> *p=getFirstNode();int i=0;
    
    if(p==NULL)
        {
            return false;
        }
    while(i<size)
    {
        
        
            if(p==node&& (node->next)==p->next && node->prev == p->prev)
            {
                return true;
                
            }
            p=p->next; 
        i++;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const 
{
    /* TODO */
    if(isEmpty())
    {
        return NULL;
    }
    
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const 
{
    /* TODO */
   
    
    if(isEmpty())
    {
        return NULL;
    }
    
    
    return head->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const 
{
    /* TODO */
    
    Node<T> *curr=head;int i=0;
   if(head==NULL)
   {
       return NULL;
   }
   
   if(size==1)
   {
       if(head->data==data)
       {
           return head;
       }
       else
       {
           return NULL;
       }
   }
    
    while(i<size)
    {
        
        if(curr->data==data)
        {
            return curr;
        }
        else
        {
            curr=curr->next;
        }i++;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const 
{
    /* TODO */
    
    int i;
    Node<T> *curr=head;
    if(head==NULL)
    {
        return NULL;
    }
    if(index<0||index>=size)
    {
        return NULL;
    }
    if(index==0)
    {
        return head;
    }
    for(i=0;i<index;i++)
    {
        curr=curr->next;
    }
    return curr;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) 
{
    /* TODO */
    if(head==NULL)
    {
        head=new Node<T>(data);
        
        head->next=head;head->prev=head;
    }
    
    else if(size==1)
    {
        Node<T> *first=new Node<T>(data);
        
        first->next=head;head->prev=first;
        head->next=first;first->prev=head;
        head=first;
        
    }
    
    else
    {
        Node<T> *first=new Node<T>(data);
        Node<T> *curr=head;
        Node<T> *last=getLastNode();
    
        head=first;
        first->prev=last;last->next=first;
        first->next=curr;
        curr->prev=first;
    }
    size++;
 
    
    

}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO*/ 
    
    if(head==NULL)
    {
        Node<T> *last=new Node<T>(data);
        head=last;
        last->next=last;last->prev=last;


    }
    else if(size==1)
    {
        Node<T> *last=new Node<T>(data);
        
        
        head->next=last;last->prev=head;
        head->prev=last;last->next=head;
    }
    
    else
    {
        Node<T> *last=new Node<T>(data);
        Node<T> *end=getLastNode();Node<T> *first=getFirstNode();
      
        last->prev=end;end->next=last;last->next=first;first->prev=last;
    }

    this->size++;
    
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
    
    if(node==NULL)
    {
        return ;
    }
    if(head==NULL)
    {
            return ;
    }
    
    if(!contains(node))
    {
        return ;
    }
    else
    {   Node<T> *middle=new Node<T>(data); 
        
        if(size==1&&head==node)
        {
            head->next=middle;middle->prev=head;
            middle->next=head;head->prev=middle;
            size++;
        }
        
        else if(node==head)
        {
            Node<T> *aft=head->next;
            head->next=middle; middle->prev=head;
            middle->next=aft;aft->prev=middle;
            size++;
            
        }
        else if(node==head->prev)
        {
            Node<T> *brr=head->prev;
            brr->next=middle;middle->prev=brr;
            middle->next=head;head->prev=middle;
            size++;
        }
        
        
        else
        {
            Node<T> *tmp=node->next;
            middle->prev=node; middle->next=tmp;node->next=middle;tmp->prev=middle;
            this->size++;
        }
    }
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) 
{
    /* TODO */
    int art=k;
    
    if(k<2||k>size+1)
    {
        return ;
    }
    
    if(k==size+1)
    {
        insertAtTheEnd(data);
    }
    
    else
    {
        
        Node <T> *ins;
        k=k-2;
        while(k<size)
        {
            ins=getNodeAtIndex(k);
            insertAfterNode(data,ins);
            k=k+art;
        }
     
    }
    
    
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) 
{
    /* TODO */
    if(!contains(node))
    {
       return ;
    }
    else if(head==NULL)
    {
       return ;
    }
    else if(size==1&&node==head)
    {
        delete head;
        head=NULL;
        size=0;
    }
    else
    {
        if(node==head)
        {
            head=node->next;
            head->prev=node->prev;
            (node->prev)->next=head;
            delete node;
            
        }
        else if(node==head->prev)
        {
            Node<T> *last=getLastNode()->prev;
            last->next=head;head->prev=last;
            delete node;
            
        }
        
        else
        {
            Node<T> *bef,*aft;
            bef=node->prev;aft=node->next;
            bef->next=aft;aft->prev=bef;
            delete node;
        }
        this->size--;
    }
    

}

template<class T>
void LinkedList<T>::removeNode(const T &data) 
{
    /* TODO */
    
   
    int i=0;int length=size;
    Node<T> *ptr=head;
    while(i<length)
    {
        if(ptr->data==data)
        {
            Node<T> *git=ptr;ptr=ptr->next;
            removeNode(git);
        }
        else
        {
            ptr=ptr->next;
        }
        i++;
    }

}

template<class T>
void LinkedList<T>::removeAllNodes() 
{
    /* TODO */
    this->~LinkedList();
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) 
{
    /* TODO */
    
    int length=size;int art=k;
    
    if(k<2||k>size)
    {
        return ;
    }
    
    if(k==size)
    {
        removeNode(getLastNode());
    }
    else
    {
        k=k-1;
        
        while(k<length)
        {
            Node<T> *del=getNodeAtIndex(k);
            removeNode(del);k=k+art-1;
        }
    
    
    }
    
    
    
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) 
{
    /* TODO */
    Node<T> *prev1,*prev2,*aft1,*aft2;prev1=NULL;prev2=NULL;aft1=NULL;aft2=NULL;
    if(head==NULL||size==1||!contains(node1)||!contains(node2))
    {
        return ;
    }
    if(node1==node2)
    {
        return ;
    }
    if(size==2)
    {
        prev1=getLastNode();
        prev1->next=head;head->prev=prev1;head->next=prev1;prev1->prev=head;
        head=prev1;
    }
   
    
    /*one of them head the other is tail*/
    if((node1==head && node2==head->prev) || (node1==head->prev && node2==head)) 
    {
        if((node1==head && node2==head->prev))
        {
            aft1=node1->next; prev2=node2->prev;
            
            prev2->next=node1;node1->prev=prev2;
            
            
            aft1->prev=node2;node2->next=aft1;

            
            
            node2->prev=node1;node1->next=node2;
            head=node2;
            
        }
        
        else
        {
            aft1=node2->next; prev2=node1->prev;
            
            prev2->next=node2;node2->prev=prev2;
            
            
            aft1->prev=node1;node1->next=aft1;

            
            
            node1->prev=node2;node2->next=node1;
            head=node1;
 
        }
   
    }
    else if((node1==head&&node2!=node1->next)|| (node2==head&&node1!=node2->next) )
    {
        if((node1==head&&node2!=node1->next))
        {
            aft1=node2->next;prev1=node2->prev;
            aft2=head->prev; prev2=node1->next;
            
            aft2->next=node2;node2->prev=aft2; node2->next=prev2;prev2->prev=node2;
            
            prev1->next=node1;node1->prev=prev1;node1->next=aft1;aft1->prev=node1;
            
            head=node2;
        }
        
        else
        {
            aft1=node1->next;prev1=node1->prev;
            aft2=head->prev; prev2=node2->next;
            
            aft2->next=node1;node1->prev=aft2; node1->next=prev2;prev2->prev=node1;
            
            prev1->next=node2;node2->prev=prev1;node2->next=aft1;aft1->prev=node2;
            
            head=node1;
        }
        
    }
    
    /*they're next to each other*/
    else if(node1->next==node2 || node2->next==node1)
    {
        /*one of them is head and they are next to each other*/
        if(node1==head||node2==head)
        {
            if(node1==head)
            {
                prev1=getLastNode();
                node1->next=node2->next;node2->next->prev=node1;
                prev1->next=node2;node2->prev=prev1; 
                node2->next=node1;node1->prev=node2;
                head=node2;
            }
            
            else
            {
                prev1=getLastNode();
                node2->next=node1->next;node1->next->prev=node2;
                prev1->next=node1;node1->prev=prev1; 
                node1->next=node2;node2->prev=node1;head=node1;
            }
        }
        /*they are next to each other and one of them is tail*/
        else if(node1==head->prev||node2==head->prev)
        {
            
            if(node1==head->prev)
            {
                prev2=node2->prev;node2->next=head;head->prev=node2;
                prev2->next=node1;node1->prev=prev2;
                node1->next=node2;node2->prev=node1;
                
                
            }
            else
            {
                prev2=node1->prev;node1->next=head;head->prev=node1;
                prev2->next=node2;node2->prev=prev2;
                node2->next=node1;node1->prev=node2;
            }
            
        }
        /*they're just next to each other*/
        else
        {
            if(node1->next==node2)
            {
                prev1=node1->prev; aft2=node2->next;
                
                prev1->next=node2; aft2->prev=node1; node2->prev=prev1; node1->next=aft2;
                
                node2->next=node1;node1->prev=node2;
            }
            else
            {
                prev1=node2->prev; aft2=node1->next;
                
                prev1->next=node1; aft2->prev=node2; node1->prev=prev1; node2->next=aft2;
                
                node1->next=node2;node2->prev=node1;
            }
        }
        
    }
    
    /*random positions*/
    else
    {
        aft1=node1->next;aft2=node2->next;prev1=node1->prev;prev2=node2->prev;
        
        prev1->next=node2;node2->prev=prev1; node2->next=aft1;aft1->prev=node2;
        prev2->next=node1;node1->prev=prev2; node1->next=aft2;aft2->prev=node1;
    }
    
    
}

template<class T>
void LinkedList<T>::shuffle(int seed) 
{
        /* TODO */
        
    int i,k;

    for(i=0;i<=size-1;i++)
    {
        k= (i*i+seed)%size;
        Node <T> *s1,*s2;
        s1=getNodeAtIndex(i);s2=getNodeAtIndex(k);
        swap(s1,s2);
    }
    //swap( getNodeAtIndex(0), getNodeAtIndex(2));
    //swap( getNodeAtIndex(1), getNodeAtIndex(3));
    //swap( getNodeAtIndex(2), getNodeAtIndex(1));
    //swap( getNodeAtIndex(3), getNodeAtIndex(1));
    //swap( getNodeAtIndex(4), getNodeAtIndex(3));
    
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) 
{
    /* TODO */
    
    if(rhs.getFirstNode()==NULL)
    {
        head=NULL;
    }
    else
    {
    if (this != &rhs) 
    {
        
        this-> ~LinkedList();
        
        head = new Node<T>(rhs.getFirstNode()->data);
        Node<T> *curr = head;
        Node<T> *tmp = head;
        Node<T> *rhs_curr = rhs.getFirstNode();
    
        while(rhs_curr->next != rhs.getFirstNode())
        {
          curr->next = new Node<T>(rhs_curr->next->data);
          rhs_curr = rhs_curr->next;
          curr = curr->next;
          curr->prev = tmp;
          tmp = tmp->next;
        }
        
        curr->next = head;
        head->prev = curr;
    }
    }
    size=rhs.getSize();
    return *this;
}

#endif //LINKEDLIST_H

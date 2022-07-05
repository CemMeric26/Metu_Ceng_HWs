#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void make_copy(BSTNode<T> *&node1, BSTNode<T> *node2) ;
    bool contains(BSTNode<T> *r, BSTNode<T> *node) const;
    void removeAllNodes(BSTNode<T> *&r);
    BSTNode<T> *search(BSTNode<T> *r,const T &data) const ;
    void insert(BSTNode<T> *&r,const T &data);
    BSTNode<T> *min_value(BSTNode<T> *r) const;
    void remove(BSTNode<T> *&r, const T &data);
    void parent_find(BSTNode<T> *r,BSTNode<T> *node, BSTNode<T>*&n)const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    /* TODO */
    root=NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {

    
    if(obj.getRoot() == NULL)
        root = NULL;
    else
        make_copy(root, obj.getRoot());
    
    
}

//helper function for making the deep copy of the bst
template<class T>
void BST<T>::make_copy(BSTNode<T> *&node1, BSTNode<T> *node2) 
{
    if(node2 != NULL) 
    {
        node1 = new BSTNode<T>(node2->data,NULL,NULL);
        make_copy(node1->left, node2->left);
        make_copy(node1->right, node2->right);
    }
    else
        node1 = NULL;

}

template<class T>
BST<T>::~BST() {
    /* TODO*/
    if(root==NULL)
    {
       ;
        
    }
    else
    {
        removeAllNodes();
        
    }
    root=NULL;
     
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    /* TODO */
    
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    /* TODO */
    if(root==NULL)
    {
        return true;
    }
    
    return false;
}


//helper function for contains
template<class T>
bool BST<T>::contains(BSTNode<T> *r, BSTNode<T> *node) const
{
    if(r != NULL)
    {
    
        if(r==node)
        {
            return true;
        }
        else
        {
            contains(r->left,node);
            contains(r->right,node);
        }
    }
    return false;
}


template<class T>
bool BST<T>::contains(BSTNode<T> *node) const 
{
    /* TODO */
    
    return contains(this->root,node);
    
}

//helper function for insert
template<class T>
void BST<T>::insert(BSTNode<T> *&r,const T &data) 
{
    /* TODO */
    if(r==NULL)
    {
        r = new BSTNode<T>(data,NULL,NULL);
    }
    else if(data > r->data)
    {
        insert(r->right,data);
    }
    else 
    {
        insert(r->left,data);
    }
    
    
    
}

template<class T>
void BST<T>::insert(const T &data) 
{
    /* TODO */
    if(root==NULL)
    {
        root=new BSTNode<T>(data,NULL,NULL);
    }
    
    else
    {
        insert(root,data);
    }
    
    
    
}



//helper function for finding minimum value node
template<class T>
BSTNode<T> *BST<T>::min_value(BSTNode<T> *r)const 
{
    /* TODO */
    BSTNode<T>* current = r;
 
   
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
  
}

template<class T>
void BST<T>::remove(BSTNode<T> *&r ,const T &data) 
{
    /* TODO */

     if (r == NULL)
     {
         return;
     }
             
    else if (r->data > data)
    {
        remove(r->left, data);
    }
        
    else if (r->data < data)
    {
        remove(r->right , data);
    }
        
    else
    {
        if (r->left !=NULL && r->right != NULL) 
        {
               
            r->data = min_value(r->right)->data;
            remove(r->right, r->data);
        }
        else 
        {
            BSTNode<T> * oldNode =r;  
            r = (r->left != NULL)? r->left : r->right;
            delete oldNode;
        }
    }
        
  
    
}


template<class T>
void BST<T>::remove(const T &data) 
{
    /* TODO  */
    
    if(root==NULL)
    {
        return ;
    }
    else
    {
        remove(root,data);
    }
    
   
    
}


//helper function for removing all nodes
template<class T>
void BST<T>::removeAllNodes(BSTNode<T> *&r) 
{
    /* TODO */
    
    if (r)
    {
        removeAllNodes(r->left);
        removeAllNodes(r->right);
        delete r; r=NULL;
    }
    
    


    
}


template<class T>
void BST<T>::removeAllNodes() 
{
    /* TODO */
    if(root==NULL)
    {
        ;
    }
    else
    {
        removeAllNodes(root);
        
    }
    root=NULL;
}

//helper function for search
template<class T>
BSTNode<T> *BST<T>::search(BSTNode<T> *r,const T &data) const 
{
    /* TODO */
    
    if (r == NULL || r->data == data)
       return r;
    
    
    if (r->data < data)
    {
       return search(r->right, data);
    }
    else
    {
        return search(r->left, data);
    }
    
}


template<class T>
BSTNode<T> *BST<T>::search(const T &data) const 
{
    /* TODO */
    BSTNode<T> *s=search(root,data);
    
    return s;
    
}

//helper for finding parent of the given node
template<class T>
void BST<T>::parent_find(BSTNode<T> *r,BSTNode<T> *node,BSTNode<T>*&n) const
{
   
    if(r==NULL)
    {
        return ;
    }
    else if(node==root)
    {
        n=NULL;
        
    }
    
    else if(r->left==node || r->right==node)
    {
        n=r;
    }
    
    parent_find(r->left,node,n);
    parent_find(r->right,node,n);
    
}


template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {

    if (tp == inorder) 
    {
        /* TODO */
        if( node->right != NULL ) 
            return min_value(node->right); 
  
        BSTNode<T> *succ = NULL; BSTNode<T> *r=root;
      
        
        while (r != NULL) 
        { 
            if (node->data < r->data) 
            { 
                succ = r; 
                r = r->left; 
            } 
            else if (node->data > r->data) 
                r = r->right; 
            else
               break; 
        } 
      
        return succ;
        
    } 
    
    else if (tp == preorder) 
    {
        

    if (!node)
    {
        return NULL;
    }

    if (node->left)
        return node->left;
 
    else if (node->right)
        return node->right;
 
    else
    {
   
       BSTNode<T> *parent,*n ;
       if(root==node)
        {
            parent=NULL;
        }
        else
        {
            parent_find(root,node,n);parent=n;
        }
        
        while (parent)
        {
            if (node->data < parent->data && parent->right)
                break;
                 
        
            parent_find(root,parent,n); parent=n;
        }
        
        
        
        if (parent == NULL)
            return NULL;
 
        return parent->right;
    }
   
    }
    
    
    else if (tp == postorder) 
    {
        /* TODO */
        
        if (node == root)
            return NULL;

        BSTNode<T>* parent,*n;
        parent_find(root,node,n);
        
        parent=n;
        
        if (parent->right == NULL || parent->right == node)
            return parent;
      
        
        BSTNode<T>* curr = parent->right;
        while (curr->left != NULL || curr->right !=NULL)
        {
            curr = curr->left;
            if(curr->left==NULL)
            {
                curr=curr->right;
            }
        }
            
      
        return curr;
        
        //alternative sol
        /*if (node->right)
            return node->right;
 
    
        BSTNode<T> *curr = node; BSTNode<T> *n;
        BSTNode<T> *parent; parent_find(root,curr,n);
        while (parent != NULL && parent->left == curr) 
        {
            parent_find(root,curr,n);
            curr = n;
            
            parent_find(root,parent,n);
            parent = n;
        }
     
       
        if (parent == NULL)
            return NULL;
     
        return parent->left;

    }*/
}
}
template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) 
    {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } 
    
    
    else if (tp == preorder) 
    {
        /* TODO */
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
        
        
    } 
    else if (tp == postorder) 
    {
        /* TODO */
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
        
        
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) 
{
    /* TODO */
    if(rhs.getRoot()==NULL)
    {
        root=NULL;
    }
    else
    {
        if(this != &rhs)
        {
            this-> ~BST();
            make_copy(root, rhs.getRoot());
        }
    }
    
    return *this;
    
    
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    
    else if (tp == preorder) 
    {
        /* TODO */
        
        std::cout << "\t" << node->data;

        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        
        if (node->right) 
        {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        
        
        
    } 
    
    else if (tp == postorder) 
    {
        /* TODO */
        
        
        // first, output left subtree and comma (if needed).
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }


        // finally, output comma (if needed) and the right subtree.
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        
        
        // then, output the node.
        std::cout << "\t" << node->data;
        
    }
}

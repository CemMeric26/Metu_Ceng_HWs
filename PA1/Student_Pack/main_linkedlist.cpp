#include <iostream>

#include "LinkedList.h"


using namespace std;

template <class T>
void test_getNode(const T  &data, const LinkedList<T> &llist)
{
    std::cout << "Seeking for Node "<< data << std::endl;
    Node<int> *catched_node = llist.getNode(data);
    if (catched_node)
    {
        std::cout << "Found at address: " << catched_node << std::endl;
    } else {std::cout << "Not found." << std::endl;}
}

template<class T>
Node<T> * test_getNodeAtIndex(int index, const LinkedList<T> &llist)
{
    Node<T> *return_val;

    std::cout << "Trying to find the node at index: " << index << std::endl;

    return_val = llist.getNodeAtIndex(index);

    if (return_val)
    {
        std::cout << "data(Node): " << return_val->data << " at address: " << return_val << std::endl;
        return return_val;
    }
    else {std::cout << "Node couldn't found at index "<< index <<" : IndexOutOfBoundary" << std::endl;}
    return NULL;
}


int main() {
    LinkedList<int> llist;
    Node<int> *node, *node2;
    cout<< "size: " <<llist.getSize()<<endl;
    llist.insertAtTheFront(3);
    llist.insertAtTheFront(2);
    llist.insertAtTheFront(15);
    llist.insertAtTheEnd(4);
    llist.print(false);
    cout<< "size: " <<llist.getSize()<<endl;
    if (llist.contains(llist.getFirstNode()))
    {
        std::cout << "The linked list contains " << (llist.getFirstNode())->data << std::endl;
    }

    std::cout << "Creating the copy of the current list: " << std::endl;

    {
        LinkedList<int> copy_llist(llist);
        std::cout << "Printing the results of the copy of the original object : " << std::endl;
        copy_llist.print(false);
        cout<< "size of copy: " <<copy_llist.getSize()<<endl;
    }
    cout<< "size: " <<llist.getSize()<<endl;
    test_getNode(4, llist);
    test_getNode(3, llist);
    test_getNode(1, llist);
    test_getNode(25, llist);


    test_getNodeAtIndex(0,llist);
    test_getNodeAtIndex(2,llist);
    node  = test_getNodeAtIndex(3, llist);
    test_getNodeAtIndex(4,llist);
    cout << node->data << endl;
    llist.insertAfterNode(15, node);
    node = test_getNodeAtIndex(0, llist);
    llist.insertAfterNode(15, node);
    node = test_getNodeAtIndex(3, llist);
    llist.insertAfterNode(15, node);
    llist.print();
    cout<< "size: " <<llist.getSize()<<endl;
    test_getNodeAtIndex(-5, llist);

    llist.insertAsEveryKthNode(200,2);
    llist.print();
    llist.insertAsEveryKthNode(300,3);
    llist.print();
    cout<< "size: " <<llist.getSize()<<endl;
    {
        node = test_getNodeAtIndex(0, llist);
        llist.removeNode(node);
    }


    llist.removeNode(200);
    llist.removeNode(300);
    llist.removeNode(15);
    llist.removeAllNodes();
    llist.print();
    cout<< "size: " <<llist.getSize()<<endl;
    for (int i = 5; i > 0; i-- ) llist.insertAtTheFront(i);
    llist.print();

    llist.removeEveryKthNode(3);

    llist.print();

    node = test_getNodeAtIndex(1, llist);
    node2 = test_getNodeAtIndex(2, llist);


    


    return 0;
}

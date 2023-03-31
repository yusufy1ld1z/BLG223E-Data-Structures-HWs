//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Yusuf YILDIZ
//---Student Number: 150210006
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue()
{
    this->head = nullptr; // Assign head to nullptr.
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node *newnode)
{
    if (this->head == nullptr)
    {
        this->head = newnode; // Control if PriorityQueue is empty, and if so, assign head to newnode and return.
        return;
    }

    Node *current = this->head;
    if (current->token.val > newnode->token.val)
    {                            // Control if the priority of newnode higher than the head,
        newnode->next = current; // if so, assign newnode as a head and next of it to previous root.
        this->head = newnode;
        return;
    }

    while (newnode->token.val >= current->token.val) // Traverse until the value of newnode lower than the current node.
    {
        if (current->next == nullptr)
        {                            // Control if is reached to end of the PriorityQueue,
            current->next = newnode; // and if so, set the end node as newnode and return.
            return;
        }

        if (current->next->token.val > newnode->token.val)
        {
            newnode->next = current->next; // Control if the value of the next node higher than newnode,
            current->next = newnode;       // and if so, that means we are in the proper position.
            return;                        // Add newnode between two nodes.
        }

        else
            current = current->next; // If none of the above conditions are satisfied,
    }                                // that means we need to go further, then set current to the next.
};

//-------------Remove Node From Priority Queue-------------//
Node *PriorityQueue::dequeue()
{
    if (this->head == nullptr) // Control if the PriorityQueue is empty, if so, return nullptr.
        return nullptr;
    Node *temp = this->head;
    this->head = this->head->next; // Assign head to it's next using temp variable.
    temp->next = nullptr;          // Assign next of the temp to nullptr to prevent memory dangling.
    return temp;                   // Return dequeued node.
};

//-------------Initialize Tree-------------//
Tree::Tree()
{
    this->root = nullptr; // Assign the root of the tree to nullptr.
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree()
{
    deleteTree(this->root); // Call the recursive destructor passing the root of the tree.
    this->root = nullptr;   // Assign root to nullptr to prevent memory dangling.
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node *node)
{
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    Node *temp = node;
    if (temp != nullptr) // Terminal condition for recursion.
    {
        deleteTree(temp->left);
        deleteTree(temp->right);
        delete temp; // Delete all nodes properly by using postorder traversal.
    }
}

//-------------Merges Two Node Into One-------------//
Node *Tree::mergeNodes(Node *temp1, Node *temp2)
{
    Node *newNode = new Node(); // Create new node.

    newNode->token.symbol = temp1->token.symbol + temp2->token.symbol; // Concatenate symbol values of the two child node.
    newNode->token.val = temp1->token.val + temp2->token.val;          // Add values of the two child node together and assign to new node's value.

    newNode->left = temp1;
    newNode->right = temp2; // Assign the children of new node properly.

    return newNode; // Return constructed tree.
};

void Tree::printTree(Node *traverse, int level)
{
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t";

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if (traverse->left)
        printTree(traverse->left, level + 1);
    if (traverse->right)
        printTree(traverse->right, level + 1);
};
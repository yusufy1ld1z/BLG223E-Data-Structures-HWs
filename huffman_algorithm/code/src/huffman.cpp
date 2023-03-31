//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Yusuf YILDIZ
//---Student Number: 150210006
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char *argv)
{
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if (readKeyFile.is_open())
    {
        while (!readKeyFile.eof())
        {
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey()
{
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency()
{
    // DO NOT CHANGE THIS
    sortKey();
    // DO NOT CHANGE THIS
    // const int arrSize = 96; Uncomment this line if every possible input consist of only uppercase characters.
    const int arrSize = 128;  // ASCII table has 128 character so create an array of 128 int.
    int myArr[arrSize] = {0}; // Initialize with zeros.

    for (auto i : this->sortedKey)
        myArr[(int)i]++; // Convert characters in sortedKey to their int correspondings in ASCII table.
                         // And increment the value in myArr.
    for (int i = 0; i < arrSize; i++)
    {
        if (myArr[i] != 0) // Control statement to know if there is not such a char in sortedKey.
        {
            Node *temp = new Node();
            temp->token.val = myArr[i];        // Create new Node and fill it's attributes with appropriate values.
            temp->token.symbol = string(1, i); // Convert int to it's char corresponding.
            this->queue.enque(temp);           // Enqueue new Node to PriorityQueue.
        }
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree()
{
    findFrequency();                          // First construct our PriorityQueue.
    while (this->queue.head->next != nullptr) // Iterate until there is just one Node consist of all other nodes in PrioritQueue.
    {
        Node *temp1 = this->queue.dequeue(); // Dequeue from front which has lowest frequency value.
        Node *temp2 = this->queue.dequeue();
        this->queue.enque(this->huffmanTree.mergeNodes(temp1, temp2)); // Merge this two lowest nodes and queue as a one Node to the PriorityQueue.
    }
    this->huffmanTree.root = this->queue.head; // Link the HuffmanTree's head to the last node in PriorityQueue.
};                                             // So our tree is constructed properly.
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree()
{
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node *traverse, string tokenBinary)
{
    string as_string(1, tokenChar);             // Convert tokenChar to string for comparing properly.
    while (traverse->token.symbol != as_string) // Iterate traverse until reach the tokenChar.
    {
        if (traverse->left->token.symbol.find(as_string) != string::npos)
        {
            tokenBinary += "0";        // Control if left side of traverse contains tokenChar,
            traverse = traverse->left; // If it contains add '0' to tokenBinary indicating we went to left.
        }
        else if (traverse->right->token.symbol.find(as_string) != string::npos)
        {
            tokenBinary += "1";         // Control if right side of traverse contains tokenChar,
            traverse = traverse->right; // If it contains add '1' to tokenBinary indicating we went to right.
        }
    }

    return tokenBinary; // Return tokenBinary corresponding path of tokenChar in HuffmanTree.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password)
{
    for (int i = 0; i < (int)password.length(); i++) // Iterate in password.
    {
        string temp = "";
        temp = this->getTokenBinary(password[i], this->huffmanTree.root, temp); // Get a binary token of char in password.
        this->encodedBinaryPassword += temp;                                    // Concatenate private variable encodedBinaryPassword with our temp.
        this->encodedValPassword += to_string(temp.length());                   // Concatenate encodedValPassword with lenght of our temp variable,
    }                                                                           // which corresponds the height of that Node.
};
//-----------------------------------------------------//

//--------------------------------------------------)---//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword()
{
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword)
{
    int index = 0; // Assign index to 0 at first to start from beginning.
    string subStr;
    for (auto i : encodedValPassword)
    {
        int bound = i - '0';                                 // Convert char to int.
        subStr = encodedBinaryPassword.substr(index, bound); // Get a proper part of encodedBinaryPassword.
        decodeToken(subStr);                                 // Decode this part of binary password.
        index += bound;                                      // Increment the index to the last read part of string.
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken)
{
    Node *temp = this->huffmanTree.root; // Assign temp to the root to traverse in tree.
    for (int i = 0; i < (int)encodedToken.length(); i++)
    {
        if (encodedToken[i] == '0')
        {
            temp = temp->left;
        }
        else if (encodedToken[i] == '1') // Proceed properly according to the encodedToken to reach the expected Node.
        {                                // Left for '0' and right for '1'.
            temp = temp->right;
        }
    }
    this->decodedPassword += temp->token.symbol; // Concatenate decodedPassword and symbol value of temp Node.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword()
{
    cout << "Decoded Password: " << decodedPassword << endl;
};